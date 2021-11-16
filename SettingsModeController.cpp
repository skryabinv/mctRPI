#include "SettingsModeController.h"

SettingsModeController::SettingsModeController(QObject *parent) : QObject(parent)
{

}

void SettingsModeController::saveToFile(const QString& path) const
{

}

void SettingsModeController::loadFromFile(const QString& path)
{

}

double SettingsModeController::getLimitLow(const QString& axisName) const
{
    return 0.123;
}

double SettingsModeController::getLimitHigh(const QString& axisName) const
{
    return 0.234;
}

double SettingsModeController::getDistForSteps(const QString& axisName) const
{
    return 1222;
}

double SettingsModeController::getStepsForDist(const QString& axisName) const
{
    return 2221;
}

QList<int> SettingsModeController::getPortStep(const QString& axisName) const
{
    return {};
}

QList<int> SettingsModeController::getPortDir(const QString& axisName) const
{
    return {};
}

QList<int> SettingsModeController::getPortHome(const QString& axisName) const
{
    return {};
}

double SettingsModeController::getSpeed(const QString& axisName) const
{
    return 400.0;
}

double SettingsModeController::getTimeToSpeed(const QString& axisName) const
{
    return 412.0;
}

void SettingsModeController::setLimitLow(const QString& axisName, double value)
{

}

void SettingsModeController::setLimitHigh(const QString& axisName, double value)
{

}

void SettingsModeController::setSpeed(const QString& axisName, double value)
{

}

void SettingsModeController::setTimeToSpeed(const QString& axisName, double value)
{

}

void SettingsModeController::setPortStep(const QString& axisName, const QList<int>& values)
{

}

void SettingsModeController::setPortHome(const QString& axisName, const QList<int>& values)
{

}

void SettingsModeController::setPortDir(const QString& axisName, const QList<int>& values)
{

}

