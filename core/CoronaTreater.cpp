#include "CoronaTreater.h"
#include "Board.h"
#include "Axis.h"
#include "OutputPort.h"
#include "RtTaskMulti.h"
#include "RtTaskGeneric.h"
#include <iostream>
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

RtTaskSharedPtr CoronaTreater::createTaskMoveToInitialPos() const
{
    auto xTask = Board::getInstance()
            .getAxis("X")
            .createTaskMoveTo(mSpeed, getInitalPosX(), true);
    auto yTask = Board::getInstance()
            .getAxis("Y")
            .createTaskMoveTo(mSpeed, getInitalPosY(), true);
    return std::make_shared<RtTaskMulti>(
        std::initializer_list<RtTaskSharedPtr>{xTask, yTask}
    );
}

RtTaskSharedPtr CoronaTreater::createTaskProcess(double xRange, double yRange,
                                                 double height,
                                                 int repeats, double speedFactor) const
{
    qDebug() << __FUNCTION__;
    // Просчитать количество переездов
    // Создать список
    auto task = [=](RtTask&){
        qDebug() << "Process:";
        qDebug() << xRange << yRange;
        qDebug() << height << repeats << speedFactor;
        return true;
    };
    return makeSharedGenericTask(std::move(task));
}

} // namespace core
