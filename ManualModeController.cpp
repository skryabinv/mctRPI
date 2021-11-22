#include "ManualModeController.h"
#include <QDebug>
#include "core/Board.h"
#include "core/Axis.h"

ManualModeController::ManualModeController(QObject *parent) : QObject(parent)
{

}

QString ManualModeController::getSelectedAxis() const
{
    return mSelectedAxis;
}

void ManualModeController::setSelectedAxis(const QString& axis)
{
    qDebug() << __FUNCTION__ << axis;
    if(mSelectedAxis != axis) {
        mSelectedAxis = axis;
        emit selectedAxisChanged(mSelectedAxis);
    }
}

double ManualModeController::getAxisPos(const QString &axis) const
{
    return core::Board::instance()
            .getAxis(axis.toStdString())
            .getCurrentPos();
}

double ManualModeController::getSelectedAxisPos() const
{
    return core::Board::instance()
            .getAxis(mSelectedAxis.toStdString())
            .getCurrentPos();
}

bool ManualModeController::homeSelectedAxis()
{
    qDebug() << __FUNCTION__ << getSelectedAxis();
    return false;
}

bool ManualModeController::homeAllAxes()
{
    qDebug() << __FUNCTION__ << getSelectedAxis();
    return false;
}

bool ManualModeController::jogStart(double speedFactor, double distance)
{
    qDebug() << __FUNCTION__ << speedFactor << distance;
    return false;
}

bool ManualModeController::jogStop()
{
    qDebug() << __FUNCTION__;
    return false;
}

void ManualModeController::cancel()
{

}
