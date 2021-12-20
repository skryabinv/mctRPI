#pragma once

#include <cstdint>
#include "RtTask.h"

namespace core {

class OutputPort;
class RtTaskProcess;

// Corona treater: settings and task generation
class CoronaTreater
{
public:    

    CoronaTreater();
    void setInitialPosX(double value) noexcept {
        mInitalPosX = value;
    }
    void setInitialPosY(double value) noexcept {
        mInitalPosY = value;
    }
    void setHeight(double value) noexcept {
        mHeight = value;
    }
    void setCoronaWidth(double value) noexcept {
        mCoronaWidth = value;
    }    
    void setSpeedFractionX(double value) noexcept;
    void setSpeedFractionZ(double value) noexcept;
    void setPortDelayMs(u_int32_t value) noexcept;

    double getInitalPosX() const noexcept {
        return mInitalPosX;
    }
    double getInitalPosY() const noexcept {
        return mInitalPosY;
    }
    double getWorkingHeight() const noexcept {
        return mHeight;
    }
    double getCoronaWidth() const noexcept {
        return mCoronaWidth;
    }
    double getSpeedFractionX() const noexcept {
        return mSpeedFractionX;
    }
    double getSpeedFractionZ() const noexcept{
        return mSpeedfractionZ;
    }
    uint32_t getPortDelayMs() const noexcept {
        return mPortDelayMs;
    }
    int getStripesCount(double xRange) const noexcept;

    RtTaskSharedPtr createTaskMoveToInitialPos() const;
    std::shared_ptr<RtTaskProcess> createTaskProcess(double xRange,
                                      double yRange,
                                      double height,
                                      int repeats, double speedFactor) const;

    // Two port treaters control: enable with delay, disable with delay

    uint32_t getEnableTreaterPin() noexcept;

    uint32_t getDisableTreaterPin() noexcept;

    void setEnableTreaterPin(uint32_t value) noexcept;

    void setDisableTreaterPin(uint32_t value) noexcept;

    // RtTaskSharedPtr createTaskEnableTreater();
    // RtTaskSharedPtr createTaskDisableTreater();

private:
    double mInitalPosX;
    double mInitalPosY;
    double mHeight;
    double mCoronaWidth;
    double mSpeedFractionX = 0.5;
    double mSpeedfractionZ = 0.5;

    // Ports for enables/disables

    uint32_t mPortDelayMs{100};
    std::unique_ptr<OutputPort> mCoronaEnablePort{};
    std::unique_ptr<OutputPort> mCoronaDisablePort{};
};

} // namespace core

