#include "SettingsModeController.h"
#include <QJsonDocument>
#include <QVariantMap>
#include <QStringLiteral>

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

QVariantList SettingsModeController::getPortStep(const QString& axisName) const
{
    return {1, 2, 3};
}

QVariantList SettingsModeController::getPortDir(const QString& axisName) const
{
    return {4, 5, 6};
}

QVariantList SettingsModeController::getPortHome(const QString& axisName) const
{
    return {7, 8, 9};
}

double SettingsModeController::getSpeed(const QString& axisName) const
{
    return 400.0;
}

double SettingsModeController::getTimeToSpeed(const QString& axisName) const
{
    return 412.0;
}

double SettingsModeController::getSpeedHomingForward(const QString& axisName) const
{
    return 0.1;
}

double SettingsModeController::getSpeedHomingBackward(const QString& axisName) const
{
    return -0.1;
}

void SettingsModeController::setLimitLow(const QString& axisName, double value)
{

}

void SettingsModeController::setLimitHigh(const QString& axisName, double value)
{

}

void SettingsModeController::setDistForSteps(const QString& axisName, double value)
{

}

void SettingsModeController::setStepsForDist(const QString& axisName, double value)
{

}

void SettingsModeController::setSpeed(const QString& axisName, double value)
{

}

void SettingsModeController::setTimeToSpeed(const QString& axisName, double value)
{

}

void SettingsModeController::setPortStep(const QString& axisName, const QVariantList& values)
{

}

void SettingsModeController::setPortHome(const QString& axisName, const QVariantList& values)
{

}

void SettingsModeController::setPortDir(const QString& axisName, const QVariantList& values)
{

}

void SettingsModeController::setSpeedHomingForward(const QString& axisName, double value)
{

}

void SettingsModeController::setSpeedHomingBackward(const QString& axisName, double value)
{

}

QVariant SettingsModeController::getAxisSettings(const QString& axisName) const
{
    QVariantMap axisSettings;
    axisSettings["limit_low"] = getLimitLow(axisName);
    axisSettings["limit_high"] = getLimitHigh(axisName);
    axisSettings["dist_for_steps"] = getDistForSteps(axisName);
    axisSettings["steps_for_dist"] = getStepsForDist(axisName);
    axisSettings["port_step"] = getPortStep(axisName);
    axisSettings["port_dir"] = getPortDir(axisName);
    axisSettings["port_home"] = getPortHome(axisName);
    axisSettings["speed"] = getSpeed(axisName);
    axisSettings["time_to_speed"] = getTimeToSpeed(axisName);
    axisSettings["speed_homing_forward"] = getSpeedHomingForward(axisName);
    axisSettings["speed_homing_backward"] = getSpeedHomingBackward(axisName);
    return axisSettings;
}

void SettingsModeController::setAxisSettings(const QString& axisName, const QVariantMap& axisSettings)
{
    qDebug() << __FUNCTION__ << axisSettings;
    setLimitLow(axisName, axisSettings["limit_low"].toDouble());
    setLimitHigh(axisName, axisSettings["limit_high"].toDouble());
    setDistForSteps(axisName, axisSettings["dist_for_steps"].toDouble());
    setStepsForDist(axisName, axisSettings["steps_for_dist"].toDouble());
    setPortStep(axisName, axisSettings["port_step"].toList());
    setPortDir(axisName, axisSettings["port_dir"].toList());
    setPortHome(axisName, axisSettings["port_home"].toList());
    setSpeed(axisName, axisSettings["speed"].toDouble());
    setTimeToSpeed(axisName, axisSettings["time_to_speed"].toDouble());
    setSpeedHomingForward(axisName, axisSettings["speed_homing_forward"].toDouble());
    setSpeedHomingBackward(axisName, axisSettings["speed_homing_backward"].toDouble());
}

void SettingsModeController::save() const
{
    qDebug() << __FUNCTION__;
}

QVariant SettingsModeController::toQVariant() const
{
    QVariantMap result;
    // Сохранение настроек осей
    QString axisNames[] = { "X", "Y", "Z" };
    for(auto axisName: axisNames) {
        result[axisName] = getAxisSettings(axisName);
    }
    // Сохранить настройки платы
    return result;
}

void SettingsModeController::fromQVariat(const QVariant& variant)
{
    QVariantMap map = variant.toMap();
    // Считывание настроек осей
    QString axisNames[] = { "X", "Y", "Z" };
    for(auto axisName: axisNames) {
        QVariantMap axisSettings = map[axisName].toMap();
        setAxisSettings(axisName, axisSettings);
    }
    // Считывание настроек платы
}

