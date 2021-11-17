#include "ManualModeController.h"
#include <QDebug>

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
