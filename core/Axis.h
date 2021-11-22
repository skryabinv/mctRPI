#pragma once

#include <memory>
#include <vector>
#include <atomic>
#include "AxisLimits.h"
#include "AxisGearRatio.h"
#include "AxisSpeedSettings.h"
#include "AxisPorts.h"

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
private:
    // Атомарная позиция в шагах двигателя
    std::atomic_int64_t mPosInSteps{0};
    // Find home flag
    std::atomic_bool mHomingDone{false};

};

} // namespace core

