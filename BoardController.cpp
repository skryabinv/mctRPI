#include "BoardController.h"
#include "core/Board.h"
#include "core/Axis.h"
#include "core/RtTaskDispatcher.h"
#include "core/OuputPort.h"
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
    if(mCurrentTask->isDone()) {
        mCurrentTask = wrapHomingTask(
                    core::Board::getInstance()
                    .getAxis(axis.toStdString())
                    .createTaskFindHome(),
                    axis
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
        mCurrentTask = wrapHomingTask(
                    core::Board::getInstance()
                    .createHomeAllTask(),
                    QStringLiteral("XYZ")
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

bool BoardController::setOutputEnabled(bool value)
{
    qDebug() << __FUNCTION__ << value;
    Q_UNUSED(value)
    emit outputStateChanged(value);
    return true;
}

bool BoardController::isBusy() const
{
    return !mCurrentTask->isDone();
}

bool BoardController::getOutputState() const
{
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
