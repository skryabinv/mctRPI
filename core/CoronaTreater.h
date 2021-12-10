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
    void setCoronaPin(uint32_t pin) noexcept;

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
    uint32_t getCoronaPin() const noexcept;    
    RtTaskSharedPtr createTaskMoveToInitialPos() const noexcept;    
    RtTaskSharedPtr createTaskProcess(double xRange,
                                      double yRange,
                                      double height,
                                      int repeats, double speedFactor) const noexcept;
private:
    double mInitalPosX;
    double mInitalPosY;
    double mHeight;
    double mCoronaWidth;
    std::unique_ptr<OutputPort> mCoronaOutputPort{};
};

} // namespace core

