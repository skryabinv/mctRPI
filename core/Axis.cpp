#include "Axis.h"
#include "RtTaskGeneric.h"
#include "AccDecPulseGenerator.h"
#include "Delay.h"
#include <exception>
#include <QDebug>

namespace core {

double Axis::getCurrentPos() const
{
    return mPosInSteps * gearRatio.getMmsPerStep();
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
    auto acc = speedSettings.getAcceleration();
    auto dec = speedSettings.getDeceleration();
    auto dpp = gearRatio.getMmsPerStep();   
    if(distance == 0.0) {
        // Moving continuously
        distance = speed < 0 ? getCurrentPos() - limits.getLow() : limits.getHigh() - getCurrentPos();
    } else {
        // Moving by steps
        auto nextPos = getCurrentPos() + (speed > 0 ? distance : -distance);
        distance = std::abs(limits.clamp(nextPos) - getCurrentPos());
    }
    qDebug() << __FUNCTION__ << distance << dpp << speed << acc << dec;
    auto func = [outDir, outStep, speed, acc, dec, dpp, distance, this](RtTask& self) {
        if(distance == 0.0) return true;
        AccDecPulseGenerator gen{ distance, dpp, std::abs(speed), acc, dec };
        outDir.setValue(speed > 0);
        int inc = speed > 0 ? 1 : -1;
        while (!self.isCanceled() && gen) {
           auto delay = gen.getDelayFuncUs<delay::ProxyDelay>();
           outStep.set();
           delay();
           outStep.clr();
           delay();
           ++gen;           
           mPosInSteps += inc;
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
    // Декодер битов
    auto step_decoder = ports.getInToStepDecoder<2>();
    auto dpp = gearRatio.getMmsPerStep();
    auto speed_fwd = speedSettings.getSpeedHomeFwd<SpeedUnits::MM_PER_SEC>();
    auto speed_back = speedSettings.getSpeedHomeBack<SpeedUnits::MM_PER_SEC>();
    auto acc = speedSettings.getAcceleration();
    auto func = [=](RtTask& self) {
        // Едем вперед, пока концевики замкнуты
        AccDecPulseGenerator gen_fwd{ dpp, speed_fwd, acc };
        out_dir.set();
        while (true) {
            if(self.isCanceled()) return true;
            auto sw_mask = in_switch.read();
            if(!sw_mask) break; // Концевик размокнут
            // Перекаодируем в маску степов
            auto mask = step_decoder.decodeLeftToRight(sw_mask);
            // Устанавливаем степы с перекаодированной маской
            auto delay_func = gen_fwd.getDelayFuncUs<delay::ProxyDelay>();
            out_step.set(mask);
            delay_func();
            out_step.clr(mask);
            delay_func();
            ++gen_fwd;
            --mPosInSteps;
        }
        // Едем назад пока концевики разомкнуты
        out_dir.clr();
        AccDecPulseGenerator gen_back{dpp, speed_back, acc};
        while (true) {
            if(self.isCanceled()) return true;
            auto sw_mask = in_switch.read();
            if(sw_mask) break; // Концевик размокнут
            // Перекаодируем в маску степов
            auto mask = step_decoder.decodeLeftToRight(sw_mask);
            auto delay_func = gen_back.getDelayFuncUs<delay::ProxyDelay>();
            out_step.set(~mask);
            delay_func();
            out_step.clr(~mask);
            delay_func();
            ++gen_back;
            ++mPosInSteps;
        }        
        mPosInSteps = 0;
        mHomingDone = true;
        // Move in positive direction
        // AccDecPulseGenerator gen_pos{dpp, speed_back, acc};

        return true;
    };
    return makeSharedGenericTask(std::move(func), "TaskAxisHoming");
}

RtTaskSharedPtr Axis::createTaskMoveTo(double speedFraction, double position)
{
    checkHome();
    auto out_dir = ports.getPortDir();
    auto out_step = ports.getPortStep();
    // Расстояние, которое нужно проехать
    auto dist = limits.clamp(position) - getCurrentPos();
    auto speed = speedSettings.getSpeed<SpeedUnits::MM_PER_SEC>(speedFraction);
    auto dpp = gearRatio.getMmsPerStep();
    auto acc = speedSettings.getAcceleration();
    auto func = [=](RtTask& self) {
        AccDecPulseGenerator gen{dist, dpp, std::abs(speed), acc, acc };
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

void Axis::checkHome()
{
    if(mHomingDone) {
        throw std::logic_error("Axis didn't homing");
    }
}


} // namespace core
