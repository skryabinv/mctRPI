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
{
    mCoronaEnablePort = std::make_unique<OutputPort>();
    mCoronaDisablePort = std::make_unique<OutputPort>();
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

uint32_t CoronaTreater::getEnableTreaterPin() noexcept
{
    return mCoronaEnablePort->getPin();
}

uint32_t CoronaTreater::getDisableTreaterPin() noexcept
{
    return mCoronaDisablePort->getPin();
}

void CoronaTreater::setEnableTreaterPin(uint32_t value) noexcept
{
    mCoronaEnablePort->setPin(value);
}

void CoronaTreater::setDisableTreaterPin(uint32_t value) noexcept
{
    mCoronaDisablePort->setPin(value);
}

} // namespace core
