#include "CoronaTreater.h"
#include "Board.h"
#include "Axis.h"
#include "OutputPort.h"
#include "RtTaskMulti.h"
#include "RtTaskGeneric.h"
#include "RtTaskRepeated.h"
#include <iostream>
#include <QDebug>

namespace core {

CoronaTreater::CoronaTreater()
{
    mCoronaEnablePort = std::make_unique<OutputPort>();
    mCoronaDisablePort = std::make_unique<OutputPort>();
}

void CoronaTreater::setSpeedFractionX(double value) noexcept {
//    assert(0.0 < value && value <= 1.0);
    mSpeedFractionX = value;
}

void CoronaTreater::setSpeedFractionZ(double value) noexcept{
//    assert(0.0 < value && value <= 1.0);
    mSpeedfractionZ = value;
}

void CoronaTreater::setPortDelayMs(u_int32_t value) noexcept
{
    assert(value < 100000);
    mPortDelayMs = value;
}

RtTaskSharedPtr CoronaTreater::createTaskMoveToInitialPos() const
{
    auto xTask = Board::getInstance()
            .getAxis("X")
            .createTaskMoveTo(mSpeedFractionX, getInitalPosX(), true);
    auto yTask = Board::getInstance()
            .getAxis("Y")
            .createTaskMoveTo(mSpeedFractionX, getInitalPosY(), true);
    return std::make_shared<RtTaskMulti>(
        std::initializer_list<RtTaskSharedPtr>{xTask,
                                               yTask}
    );
}

RtTaskSharedPtr CoronaTreater::createTaskProcess(double xRange, double yRange,
                                                 double height,
                                                 int repeats, double speedFraction) const
{
    qDebug() << __FUNCTION__;
    // Просчитать количество переездов
    // Создать список

    // MoveTo InitialPos
    // Enable Corona

    // repeat xRange / width + 1
        // JogY(yRange)
        // JogX(Width)

    // Disable Corona
    // MoveToInitalPos

    std::vector<RtTaskSharedPtr> tasksList;
    auto stripesCount = xRange / getCoronaWidth();

    qDebug() << __FUNCTION__
             << "Stripes:" << stripesCount
             << "x_range:" << xRange
             << "y_range:" << yRange;


    // GoTo initial pos
    tasksList.push_back(createTaskMoveToInitialPos());
    // GoTo Height
    tasksList.push_back(
                Board::getInstance()
                .getAxis("Z")
                .createTaskMoveTo(getSpeedFractionZ(),
                                  height + getWorkingHeight()));
    // Tasks for all stripes
    for(int i = 0; i < stripesCount; ++i) {
        auto dir = (i % 2 == 0) ? 1 : -1;
        // move
        tasksList.push_back(
                    Board::getInstance()
                    .getAxis("Y")
                    .createTaskJog(dir * speedFraction, yRange)
                    );
        tasksList.push_back(
                    Board::getInstance()
                    .getAxis("X")
                    .createTaskJog(getSpeedFractionX(),
                                   getCoronaWidth())
                    );
    }
    tasksList.push_back(createTaskMoveToInitialPos());
    auto taskMulti = std::make_shared<RtTaskMulti>(std::move(tasksList));
    return std::make_shared<RtTaskRepeated>(std::move(taskMulti), repeats);
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
