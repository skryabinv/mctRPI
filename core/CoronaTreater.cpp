#include "CoronaTreater.h"
#include "Board.h"
#include "Axis.h"
#include "OutputPort.h"
#include "Delay.h"
#include "RtTaskMulti.h"
#include "RtTaskGeneric.h"
#include "RtTaskProcess.h"
#include <iostream>
#include <thread>
#include <QDebug>

namespace core {

CoronaTreater::CoronaTreater()
{
    mPortCoronaOn = std::make_unique<OutputPort>();
    mPortCoronaOff = std::make_unique<OutputPort>();
}

CoronaTreater::~CoronaTreater()
{
    releaseCoronaState();
}

void CoronaTreater::setSpeedFractionX(double value) noexcept {
    assert(0.0 < value && value <= 1.0);
    mSpeedFractionX = value;
}

void CoronaTreater::setSpeedFractionZ(double value) noexcept{
    assert(0.0 < value && value <= 1.0);
    mSpeedfractionZ = value;
}

void CoronaTreater::setPortDelayMs(u_int32_t value) noexcept
{
    assert(value < 100000);
    mPortDelayMs = value;
}

int CoronaTreater::getStripesCount(double rangeX) const noexcept
{
    return static_cast<int>(std::ceil(rangeX / getCoronaWidth())) + 1;
}

RtTaskSharedPtr CoronaTreater::createTaskMoveToInitialPos()
{
    auto taskX = Board::getInstance()
            .getAxis("X")
            .createTaskMoveTo(mSpeedFractionX, getInitalPosX(), true);
    auto taskY = Board::getInstance()
            .getAxis("Y")
            .createTaskMoveTo(mSpeedFractionX, getInitalPosY(), true);
    return std::make_shared<RtTaskMulti>(
        std::initializer_list<RtTaskSharedPtr>{taskX,
                                               taskY}
    );
}

std::shared_ptr<RtTaskProcess> CoronaTreater::createTaskProcess(double rangeX,
                                                                double rangeY,
                                                                double height,
                                                                int repeats,
                                                                double speedFraction)
{

    return std::make_shared<RtTaskProcess>(*this, rangeX, rangeY, height,
                                           repeats, speedFraction);
}

RtTaskSharedPtr CoronaTreater::createTaskOn()
{
    return createPortTask(true, getPortDelayMs());
}

RtTaskSharedPtr CoronaTreater::createTaskOff()
{
    return createPortTask(false, getPortDelayMs());
}

RtTaskSharedPtr CoronaTreater::createTaskOnOff(bool state)
{
    return state ? createTaskOn() : createTaskOff();
}

uint32_t CoronaTreater::getPinOn() noexcept
{
    return mPortCoronaOn->getPin();
}

uint32_t CoronaTreater::getPinOff() noexcept
{
    return mPortCoronaOff->getPin();
}

void CoronaTreater::setPinOn(uint32_t value) noexcept
{
    mPortCoronaOn->setPin(value);
}

void CoronaTreater::setPinOff(uint32_t value) noexcept
{
    mPortCoronaOff->setPin(value);
}

RtTaskSharedPtr CoronaTreater::createPortTask(bool state, int delayMs)
{
    auto port = state ? mPortCoronaOn->getPort() : mPortCoronaOff->getPort();    
    return makeSharedGenericTask([=](RtTask&) {
        delay::ProxyDelay delay(1000 * delayMs);
        port.set();
        delay();
        port.clr();
        setCoronaState(state);
        return true;
    });
}

void CoronaTreater::releaseCoronaState()
{
    mPortCoronaOff->getPort().set();
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
    mPortCoronaOff->getPort().clr();
}

void CoronaTreater::setCoronaState(bool value)
{
    if(mCoronaState != value) {
        mCoronaState = value;
        if(mCoronaStateChangedListener) {
            mCoronaStateChangedListener(value);
        }
    }
}


} // namespace core
