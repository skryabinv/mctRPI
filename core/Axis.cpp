#include "Axis.h"
#include "RtTaskGeneric.h"
#include "RtTaskMulti.h"
#include "AccDecPulseGenerator.h"
#include "Delay.h"
#include <exception>
#include <initializer_list>
#include <iostream>
#include <QDebug>

namespace core {

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
    // Make copy to avoid data race
    auto gear = gearRatio;
    auto sspeed = speedSettings;
    if(distance == 0.0) distance = limits.getMaxDist(getCurrentPos(), speed);
    else distance = limits.clampDistance(getCurrentPos(), distance, speed);
    auto func = [outDir, outStep, sspeed, gear, distance, speed, this](RtTask& self) {
        if(distance == 0.0) return true;
        AccDecPulseGenerator gen{ distance,
                    gear.getMmsPerStep(),
                    std::abs(speed),
                    sspeed.getAcceleration(),
                    sspeed.getDeceleration()
        };
        outDir.setValue(speed > 0);
        int inc = speed > 0 ? 1 : -1;
        while (!self.isCanceled() && gen) {
           auto delay = gen.getDelayFuncUs<delay::ProxyDelay>();
           outStep.clr();
           delay();
           outStep.set();
           delay();
           ++gen;           
           mPosInSteps += inc;
        }
        if(self.isCanceled() && gen) {
            // Deceleration
            gen.startDec();
            while (gen) {
               auto delay = gen.getDelayFuncUs<delay::ProxyDelay>();
               outStep.clr();
               delay();
               outStep.set();
               delay();
               ++gen;
               mPosInSteps += inc;
            }
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

    auto func = [=](RtTask& self) {
        // Forward moving
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
            auto delay_func = gen_fwd.getDelayFuncUs<delay::ProxyDelay>();
            out_step.set(mask);
            delay_func();
            out_step.clr(mask);
            delay_func();
            ++gen_fwd;
            mPosInSteps += inc;
        }
        // Backward moving
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
            auto delay_func = gen_back.getDelayFuncUs<delay::ProxyDelay>();
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


//    return makeSharedGenericTask(std::move(func), "TaskAxisHoming");
}

RtTaskSharedPtr Axis::createTaskMoveTo(double speedFraction, double position, bool checkLimits)
{    
    auto out_dir = ports.getPortDir();
    auto out_step = ports.getPortStep();
    // Расстояние, которое нужно проехать        

    auto sspeed = speedSettings;
    auto gratio = gearRatio;

    auto func = [=](RtTask& self) {
        if(!mHomingDone) return true;
        auto dist = (checkLimits ? limits.clamp(position) : position) - getCurrentPos();
        qDebug() << "Moving:" << position << getCurrentPos() << dist;
        AccDecPulseGenerator gen{ std::abs(dist),
                    gratio.getMmsPerStep(),
                    sspeed.getSpeed<SpeedUnits::MM_PER_SEC>(speedFraction),
                    sspeed.getAcceleration(),
                    sspeed.getDeceleration() };
        out_dir.setValue(dist > 0);
        while (!self.isCanceled() && gen) {
            auto delay_func = gen.getDelayFuncUs<delay::ProxyDelay, 2>();
            out_step.set();
            delay_func();
            out_step.clr();
            delay_func();
            ++gen;
            ++mPosInSteps;
        }
        return true;
    };
    return makeSharedGenericTask(std::move(func), "TaskAxisMoveTo");
}

} // namespace core
