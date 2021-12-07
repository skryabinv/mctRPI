#include "ManualModeController.h"
#include <QDebug>
#include "core/Board.h"
#include "core/Axis.h"
#include "core/RtTaskDispatcher.h"
#include "TaskAdapter.h"
#include "BoardController.h"

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
    return BoardController::getInstance()
            .getAxisPos(axis);
}

double ManualModeController::getSelectedAxisPos() const
{
    return BoardController::getInstance()
            .getAxisPos(mSelectedAxis);
}

bool ManualModeController::homeSelectedAxis()
{    
    return BoardController::getInstance()
            .homeAxis(mSelectedAxis);
}

bool ManualModeController::homeAllAxes()
{
    return BoardController::getInstance()
            .homeAllAxis();
}

bool ManualModeController::jogStart(double speedFactor, double distance)
{    
    mJogStarted = BoardController::getInstance()
            .jogStart(getSelectedAxis(), speedFactor, distance);
    return mJogStarted;
}

bool ManualModeController::jogStop()
{    
    if(mJogStarted) {
        BoardController::getInstance()
                .cancel();
    }
    return true;
}

void ManualModeController::cancel()
{
    BoardController::getInstance()
            .cancel();
}

