#pragma once

#include <cstdint>
#include "RtTask.h"

namespace core {

class OutputPort;

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

    double getInitalPosX() const noexcept {
        return mInitalPosX;
    }
    double getInitalPosY() const noexcept {
        return mInitalPosY;
    }
    double getHeight() const noexcept {
        return mHeight;
    }
    double getCoronaWidth() const noexcept {
        return mCoronaWidth;
    }

    RtTaskSharedPtr createTaskMoveToInitialPos() const;
    RtTaskSharedPtr createTaskProcess(double xRange,
                                      double yRange,
                                      double height,
                                      int repeats, double speedFactor) const;

    // Two port treaters control: enable with delay, disable with delay

    uint32_t getEnableTreaterPin() noexcept;

    uint32_t getDisableTreaterPin() noexcept;

    void setEnableTreaterPin(uint32_t value) noexcept;

    void setDisableTreaterPin(uint32_t value) noexcept;

    void setPortDelayMs(double value) noexcept {
        mPortDelayMs = value;
    }

    double getPortDelayMs() const noexcept {
        return mPortDelayMs;
    }

    // RtTaskSharedPtr createTaskEnableTreater();
    // RtTaskSharedPtr createTaskDisableTreater();

private:
    double mInitalPosX;
    double mInitalPosY;
    double mHeight;
    double mCoronaWidth;
    double mSpeed = 0.5;

    // Ports for enables/disables

    double mPortDelayMs{100.0};
    std::unique_ptr<OutputPort> mCoronaEnablePort{};
    std::unique_ptr<OutputPort> mCoronaDisablePort{};
};

} // namespace core

