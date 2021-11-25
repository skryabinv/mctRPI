#include "BoardController.h"
#include "core/Board.h"
#include "core/Axis.h"
#include "core/RtTaskDispatcher.h"
#include "core/ExternalOut.h"
#include "TaskAdapter.h"

BoardController::BoardController(QObject *parent) : QObject(parent)
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
    if(mCurrentTask->isDone()) {
        mCurrentTask = wrapTask(
                core::Board::getInstance()
                .getAxis(axis.toStdString())
                .createTaskFindHome()
                );
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool BoardController::homeAllAxis()
{
    if(mCurrentTask->isDone()) {
        mCurrentTask = wrapTask(
                    core::Board::getInstance()
                    .createHomeAllTask()
                    );
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool BoardController::jogStart(const QString& axis, double speedFactor, double distance)
{
    if(mCurrentTask->isDone()) {
        mCurrentTask = wrapTask(
                    core::Board::getInstance()
                    .getAxis(axis.toStdString())
                    .createTaskJog(speedFactor, distance)
                                );
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

bool BoardController::setOutEnabled(bool value)
{
    Q_UNUSED(value)
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
