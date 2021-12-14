#include "BoardController.h"
#include "core/Board.h"
#include "core/Axis.h"
#include "core/RtTaskDispatcher.h"
#include "core/OutputPort.h"
#include "core/CoronaTreater.h"
#include "TaskAdapter.h"
#include <QDebug>

BoardController::BoardController(QObject *parent)
    : QObject(parent),
    mCurrentTask{std::make_shared<core::RtTask>("TaskEmpty", true)}
{

}

double BoardController::getAxisPos(const QString &axis) const
{
    return core::Board::getInstance()
            .getAxis(axis.toStdString())
            .getCurrentPos();
}

bool BoardController::homeAxis(const QString &axis)
{
    if(isReady()) {
        mCurrentTask = wrapHomingTask(
                    core::Board::getInstance()
                    .getAxis(axis.toStdString())
                    .createTaskFindHome(),
                    axis);
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool BoardController::homeAllAxis()
{    
    if(isReady()) {
        mCurrentTask = wrapHomingTask(
                    core::Board::getInstance()
                    .createTaskHomeAll(),
                    QStringLiteral("XYZ"));
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool BoardController::jogStart(const QString& axis, double speedFactor, double distance)
{    
    if(isReady()) {
        mCurrentTask = wrapTask(
                    core::Board::getInstance()
                    .getAxis(axis.toStdString())
                    .createTaskJog(speedFactor, distance));
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

void BoardController::cancel()
{    
    mCurrentTask->cancel();
}

bool BoardController::isHomingDone(const QString &axis) const
{
    return core::Board::getInstance()
            .getAxis(axis.toStdString())
            .isHomingDone();
}

bool BoardController::isBusy() const
{
    return !mCurrentTask->isDone();
}

bool BoardController::isReady() const
{
    return mCurrentTask->isDone();
}

bool BoardController::getOutputState() const
{
    return false;
}

bool BoardController::startTreater(double xRange, double yRange, double height,
                                       int repeatsCount, double speedFactor)
{   
    qDebug() << __FUNCTION__ << xRange << yRange << height << repeatsCount << speedFactor;
    if(isReady()) {
        auto task = core::Board::getInstance()
                .getCoronaTreater()
                .createTaskProcess(xRange, yRange,
                                   height,
                                   repeatsCount,
                                   speedFactor);
        mCurrentTask = wrapTask(std::move(task));
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool BoardController::moveToHomePos()
{    
    if(isReady()) {
        auto task = core::Board::getInstance()
                .createTaskMoveToHome();
        mCurrentTask = wrapTask(std::move(task));
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool BoardController::moveToInitialPos()
{
    qDebug() << __FUNCTION__;
    if(isReady()) {
        auto task = core::Board::getInstance()
                .getCoronaTreater()
                .createTaskMoveToInitialPos();
        mCurrentTask = wrapTask(std::move(task));
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

BoardController &BoardController::getInstance()
{
    static BoardController instance;
    return instance;
}

core::RtTaskSharedPtr BoardController::wrapTask(core::RtTaskSharedPtr task)
{
    auto result = createTaskAdapter(std::move(task));
    connect(result.get(), &TaskAdapter::taskStarted,
            this, &BoardController::taskStarted);
    connect(result.get(), &TaskAdapter::taskFinished,
            this, &BoardController::taskFinished);
    return result;
}

core::RtTaskSharedPtr BoardController::wrapHomingTask(core::RtTaskSharedPtr task,
                                                      const QString &axes)
{
    auto result = createTaskAdapter(std::move(task));
    connect(result.get(), &TaskAdapter::taskStarted,
            this, &BoardController::taskStarted);
    connect(result.get(), &TaskAdapter::taskFinished,
            this, [axes, this](bool canceled){
        if(!canceled) {
            emit axesHomingDone(axes);
        }
        emit taskFinished(canceled);
    });
    return result;
}
