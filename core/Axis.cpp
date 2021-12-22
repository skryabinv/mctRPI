#include "Axis.h"
#include "RtTaskGeneric.h"
#include "RtTaskMulti.h"
#include "AccDecPulseGenerator.h"
#include "Delay.h"
#include <exception>
#include <initializer_list>
#include <iostream>
#include <thread>
#include <QDebug>

namespace core {

template<typename StopingPredicate, typename PerStepFunc>
static inline void move(AccDecPulseGenerator& gen,
                        const gpio::PortOut& stepPort,
                        StopingPredicate stop,
                        PerStepFunc func) {
    while (!stop() && gen) {
        auto delay = gen.getDelayFuncUs<delay::ProxyDelay, 2>();
        stepPort.clr();
        delay();
        stepPort.set();
        delay();
        ++gen;
        func();
    }
}


double Axis::getCurrentPos() const
{    
    return gearRatio.getMmsForSteps(mPosInSteps);
}

bool Axis::isHomingDone() const
{
    return mHomingDone;
}

RtTaskSharedPtr Axis::createTaskJog(double speedFraction, double distance)
{   
    auto outDir = ports.getPortDir();
    auto outStep = ports.getPortStep();

    auto speed = speedSettings.getSpeed<SpeedUnits::MM_PER_SEC>(speedFraction);
    auto gear = gearRatio;
    auto sspeed = speedSettings;

    auto func = [outDir, outStep, sspeed, gear, distance, speed, this](RtTask& self) {
        double dist = 0.0;
        if(distance == 0.0) dist = limits.getMaxDist(getCurrentPos(), speed);
        else dist = limits.clampDistance(getCurrentPos(), distance, speed);
        if(dist == 0.0) return true;
        AccDecPulseGenerator gen{ dist,
                    gear.getMmsPerStep(),
                    std::abs(speed),
                    sspeed.getAcceleration(),
                    sspeed.getDeceleration()
        };
        auto inc = speed > 0 ? 1 : -1;
        outDir.setValue(speed > 0);        
        move(gen, outStep, [&self](){
            return self.isCanceled();
        }, [this, inc]() {
            return mPosInSteps += inc;
        });



//        while (!self.isCanceled() && gen) {
//           auto delay = gen.getDelayFuncUs<delay::ProxyDelay, 2>();
//           outStep.clr();
//           delay();
//           outStep.set();
//           delay();
//           ++gen;
//           mPosInSteps += inc;
//        }
        if(self.isCanceled() && gen) {
            // Deceleration
            gen.startDec();
            move(gen, outStep, [](){
                return false;
            }, [this, inc]() {
                return mPosInSteps += inc;
            });

//            while (gen) {
//               auto delay = gen.getDelayFuncUs<delay::ProxyDelay, 2>();
//               outStep.clr();
//               delay();
//               outStep.set();
//               delay();
//               ++gen;
//               mPosInSteps += inc;
//            }
        }
        return true;
    };
    return makeSharedGenericTask(std::move(func), "TaskAxisJog");
}

RtTaskSharedPtr Axis::createTaskFindHome()
{
    auto out_dir = ports.getPortDir();
    auto out_step = ports.getPortStep();
    auto in_switch = ports.getPortHome();    
    auto step_decoder = ports.getInToStepDecoder<2>();

    // Make copy to avoid data race
    auto speed = speedSettings;
    auto gear = gearRatio;

    auto func = [speed, gear, out_dir, out_step, in_switch, step_decoder, this](RtTask& self) {
        speed.applyHomeDir(out_dir);
        auto inc = speed.getHomeIncrement();
        AccDecPulseGenerator gen_fwd{ gear.getMmsPerStep(),
                    speed.getSpeedHomeFwd<SpeedUnits::MM_PER_SEC>(),
                    speed.getAcceleration() };
        while (true) {
            if(self.isCanceled()) return true;
            auto sw_mask = in_switch.read();            
            if(!sw_mask) break;
            auto mask = step_decoder.decodeLeftToRight(sw_mask);
            auto delay_func = gen_fwd.getDelayFuncUs<delay::ProxyDelay, 2>();
            out_step.set(mask);
            delay_func();
            out_step.clr(mask);
            delay_func();
            ++gen_fwd;
            mPosInSteps += inc;
        }


        speed.applyHomeDir(out_dir, true);
        inc = speed.getHomeIncrement(true);
        AccDecPulseGenerator gen_back{gear.getMmsPerStep(),
                    speed.getSpeedHomeBack<SpeedUnits::MM_PER_SEC>(),
                    speed.getAcceleration()};
        while (true) {
            if(self.isCanceled()) return true;
            auto sw_mask = in_switch.read();
            if(sw_mask == in_switch.mask()) break;
            auto mask = step_decoder.decodeLeftToRight(sw_mask);
            auto delay_func = gen_back.getDelayFuncUs<delay::ProxyDelay, 2>();
            out_step.set(~mask);
            delay_func();
            out_step.clr(~mask);
            delay_func();
            ++gen_back;
            mPosInSteps += inc;
        }        
        mPosInSteps = speed.getPosHome() * gear.getStepsPerMm();
        mHomingDone = true;           
        return true;
    };
    return std::make_shared<RtTaskMulti>( std::initializer_list<RtTaskSharedPtr>{
                makeSharedGenericTask(std::move(func), "TaskAxisHoming"),
                createTaskJog(0.1 * speedSettings.getHomeIncrement(true), speedSettings.getSafePos())
                } );
}

RtTaskSharedPtr Axis::createTaskMoveTo(double speedFraction,
                                       double targetPosition,
                                       bool checkLimits)
{    
    auto out_dir = ports.getPortDir();
    auto out_step = ports.getPortStep();
    // Расстояние, которое нужно проехать        

    auto sspeed = speedSettings;
    auto gratio = gearRatio;

    auto func = [=](RtTask& self) {
        if(!mHomingDone) return true;
        auto dist = (checkLimits ? limits.clamp(targetPosition) : targetPosition) - getCurrentPos();
        if(dist == 0.0) return true;
        int inc = dist < 0 ? -1 : 1;
        AccDecPulseGenerator gen{ std::abs(dist),
                    gratio.getMmsPerStep(),
                    sspeed.getSpeed<SpeedUnits::MM_PER_SEC>(speedFraction),
                    sspeed.getAcceleration(),
                    sspeed.getDeceleration() };
        out_dir.setValue(dist > 0);
        move(gen, out_step, [&self](){
            return self.isCanceled();
        }, [this, inc]() {
            return mPosInSteps += inc;
        });


//        while (!self.isCanceled() && gen) {
//            auto delay_func = gen.getDelayFuncUs<delay::ProxyDelay, 2>();
//            out_step.set();
//            delay_func();
//            out_step.clr();
//            delay_func();
//            ++gen;
//            mPosInSteps += inc;
//        }
        return true;
    };
    return makeSharedGenericTask(std::move(func), "TaskAxisMoveTo");
}

RtTaskSharedPtr Axis::createTaskMoveToZeroPos(double speedFraction)
{
    return createTaskMoveTo(speedFraction, 0.0);
}

} // namespace core
