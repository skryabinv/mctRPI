#pragma once

#include <memory>
#include <vector>
#include <atomic>
#include "AxisLimits.h"
#include "AxisGearRatio.h"
#include "AxisSpeedSettings.h"
#include "AxisPorts.h"
#include "RtTask.h"

namespace core {

// Абстракция оси
class Axis
{
public:    
    // Параметры оси
    AxisSpeedSettings speedSettings;
    AxisLimits limits;
    AxisGearRatio gearRatio;
    AxisPorts ports;
    double getCurrentPos() const;
    bool isHomingDone() const;

    // speed - number between 0.0 and 1.0
    // distance - ditance value in mm or 0.0 for continuous jog
    RtTaskSharedPtr createTaskJog(double speedFraction, double distance);

    // Task homing (speed settings from speedSettings)
    RtTaskSharedPtr createTaskFindHome();

    // speed - number between 0.0 and 1.0
    // position - pos in mm from home
    RtTaskSharedPtr createTaskMoveTo(double speedFraction, double position, bool checkLimits = true);

private:
    void checkHome();
    // Атомарная позиция в шагах двигателя
    std::atomic_int64_t mPosInSteps{0};
    // Find home flag
    std::atomic_bool mHomingDone{false};

};

} // namespace core

