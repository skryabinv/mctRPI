#include "ManualModeController.h"
#include <QDebug>
#include "core/Board.h"
#include "core/Axis.h"
#include "core/RtTaskDispatcher.h"
#include "TaskAdapter.h"

ManualModeController::ManualModeController(QObject *parent) : QObject(parent),
    mCurrentTask{std::make_shared<core::RtTask>("TaskEmpty", true)}
{

}

QString ManualModeController::getSelectedAxis() const
{
    return mSelectedAxis;
}

void ManualModeController::setSelectedAxis(const QString& axis)
{    
    if(mSelectedAxis != axis) {
        mSelectedAxis = axis;
        emit selectedAxisChanged(mSelectedAxis);
    }
}

double ManualModeController::getAxisPos(const QString &axis) const
{
    return core::Board::getInstance()
            .getAxis(axis.toStdString())
            .getCurrentPos();
}

double ManualModeController::getSelectedAxisPos() const
{
    return core::Board::getInstance()
            .getAxis(mSelectedAxis.toStdString())
            .getCurrentPos();
}

bool ManualModeController::homeSelectedAxis()
{    
    if(mCurrentTask->isDone()) {
        mCurrentTask = wrapTask(
                core::Board::getInstance()
                .getAxis(getSelectedAxis().toStdString())
                .createTaskFindHome()
                );
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool ManualModeController::homeAllAxes()
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

bool ManualModeController::jogStart(double speedFactor, double distance)
{    
    if(mCurrentTask->isDone()) {        
        mCurrentTask = wrapTask(
                    core::Board::getInstance()
                    .getAxis(getSelectedAxis().toStdString())
                    .createTaskJog(speedFactor, distance)
                                );
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool ManualModeController::jogStop()
{
    mCurrentTask->cancel();
    return true;
}

void ManualModeController::cancel()
{
    mCurrentTask->cancel();    
}

core::RtTaskSharedPtr ManualModeController::wrapTask(core::RtTaskSharedPtr task)
{
    auto result = createTaskAdapter(std::move(task));
    connect(result.get(), &TaskAdapter::taskStarted,
            this, &ManualModeController::taskStarted);
    connect(result.get(), &TaskAdapter::taskFinished,
            this, &ManualModeController::taskFinished);
    return result;
}
