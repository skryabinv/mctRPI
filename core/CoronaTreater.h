#pragma once

#include <cstdint>
#include <functional>
#include "RtTask.h"

namespace core {

class OutputPort;
class RtTaskProcess;

// Corona treater: settings and task generation
class CoronaTreater
{
public:    
    CoronaTreater();
    ~CoronaTreater();
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
    bool getCoronaState() const noexcept {
        return mCoronaState;
    }
    int getStripesCount(double rangeX) const noexcept;

    RtTaskSharedPtr createTaskMoveToInitialPos();
    std::shared_ptr<RtTaskProcess> createTaskProcess(double rangeX,
                                                     double rangeY,
                                                     double height,
                                                     int repeats,
                                                     double speedFactor);
    RtTaskSharedPtr createTaskOn();
    RtTaskSharedPtr createTaskOff();
    RtTaskSharedPtr createTaskOnOff(bool state);

    uint32_t getPinOn() noexcept;
    uint32_t getPinOff() noexcept;

    void setPinOn(uint32_t value) noexcept;
    void setPinOff(uint32_t value) noexcept;

    template<typename F>
    void setCoronaStateChangedListener(F func) {
        mCoronaStateChangedListener = std::move(func);
    }

private:
    RtTaskSharedPtr createPortTask(bool state, int delayMs);
    void releaseCoronaState();
    void setCoronaState(bool value);

    double mInitalPosX;
    double mInitalPosY;
    double mHeight;
    double mCoronaWidth;
    double mSpeedFractionX = 0.5;
    double mSpeedfractionZ = 0.5;

    // Ports for enables/disables

    uint32_t mPortDelayMs{100};
    std::unique_ptr<OutputPort> mPortCoronaOn{};
    std::unique_ptr<OutputPort> mPortCoronaOff{};
    std::atomic_bool mCoronaState{};
    // Calls from different threads
    std::function<void(bool)> mCoronaStateChangedListener{};
    // Add progress (atomic variable) from ProcessStateClass
};

} // namespace core

