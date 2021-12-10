#include "CoronaTreater.h"
#include "OutputPort.h"
#include <QDebug>

namespace core {

CoronaTreater::CoronaTreater()
    : mCoronaOutputPort{std::make_unique<OutputPort>()}
{

}

void CoronaTreater::setCoronaPin(uint32_t pin) noexcept
{
    assert(mCoronaOutputPort != nullptr);
    mCoronaOutputPort->setPin(pin);
}

uint32_t CoronaTreater::getCoronaPin() const noexcept
{
    assert(mCoronaOutputPort != nullptr);
    return mCoronaOutputPort->getPin();
}

RtTaskSharedPtr CoronaTreater::createTaskMoveToInitialPos() const noexcept
{
    return {};
}

RtTaskSharedPtr CoronaTreater::createTaskProcess(double xRange, double yRange, double height, int repeats, double speedFactor) const noexcept
{
    qDebug() << __FUNCTION__;
    qDebug() << xRange << yRange << height << repeats << speedFactor;
    return {};
}


} // namespace core
