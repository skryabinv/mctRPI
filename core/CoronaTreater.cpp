#include "CoronaTreater.h"
#include "Board.h"
#include "Axis.h"
#include "OutputPort.h"
#include "RtTaskMulti.h"
#include "RtTaskGeneric.h"
#include "RtTaskProcess.h"
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

int CoronaTreater::getStripesCount(double xRange) const noexcept
{
    return static_cast<int>(std::ceil(xRange / getCoronaWidth())) + 1;
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

std::shared_ptr<RtTaskProcess> CoronaTreater::createTaskProcess(double xRange, double yRange,
                                                 double height,
                                                 int repeats, double speedFraction) const
{

    return std::make_shared<RtTaskProcess>(*this, xRange, yRange,
                                           height,
                                           repeats,
                                           speedFraction);

//    std::vector<RtTaskSharedPtr> tasksList;
//    auto stripesCount = std::ceil(xRange / getCoronaWidth()) + 1;

//    tasksList.push_back(createTaskMoveToInitialPos());
//    tasksList.push_back(
//                Board::getInstance()
//                .getAxis("Z")
//                .createTaskMoveTo(getSpeedFractionZ(),
//                                  height + getWorkingHeight()));
//    // Enable Port

//    for(int i = 0; i < stripesCount; ++i) {
//        auto dir = (i % 2 == 0) ? 1 : -1;
//        tasksList.push_back(
//                    Board::getInstance()
//                    .getAxis("Y")
//                    .createTaskJog(dir * speedFraction, yRange)
//                    );
//        if(i != stripesCount - 1) {
//            tasksList.push_back(
//                        Board::getInstance()
//                        .getAxis("X")
//                        .createTaskJog(getSpeedFractionX(),
//                                       getCoronaWidth())
//                        );
//        }
//    }

//    // Disable Port

//    tasksList.push_back(createTaskMoveToInitialPos());
//    auto taskMulti = std::make_shared<RtTaskMulti>(std::move(tasksList));

//    return std::make_shared<RtTaskRepeated>(std::move(taskMulti), repeats);
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
