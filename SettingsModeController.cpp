#include "SettingsModeController.h"
#include <QJsonDocument>
#include <QVariantMap>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include "core/Board.h"
#include "core/Axis.h"

template <typename ResType, typename HoldType = double>
static std::vector<ResType> toStdVector(const QVariantList& variantList) {
    std::vector<ResType> result;
    for(auto val: variantList) {
        result.push_back(ResType(val.value<HoldType>()));
    }
    return result;
}


SettingsModeController::SettingsModeController(QObject *parent) : QObject(parent)
{
     load();
}

void SettingsModeController::saveToFile(const QString& path) const
{
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)) {
//        qDebug() << toVariant();
        file.write(QJsonDocument::fromVariant(toVariant()).toJson());
        file.close();
    }
}

void SettingsModeController::loadFromFile(const QString& path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)) {
        auto doc = QJsonDocument::fromJson(file.readAll());
        fromVariant(doc.toVariant());
        file.close();
    }
}

double SettingsModeController::getLimitLow(const QString& axisName) const
{
    return core::Board::instance()
            .getAxis(axisName.toStdString())
            .limits
            .getLow();
}

double SettingsModeController::getLimitHigh(const QString& axisName) const
{
    return core::Board::instance()
            .getAxis(axisName.toStdString())
            .limits
            .getHigh();
}

double SettingsModeController::getDistForSteps(const QString& axisName) const
{
    return core::Board::instance()
            .getAxis(axisName.toStdString())
            .gearRatio
            .getDist();
}

double SettingsModeController::getStepsForDist(const QString& axisName) const
{
    return core::Board::instance()
            .getAxis(axisName.toStdString())
            .gearRatio
            .getSteps();
}

QVariantList SettingsModeController::getPortStep(const QString& axisName) const
{    
    QVariantList result;
    for(auto port: core::Board::instance()
        .getAxis(axisName.toStdString())
        .ports
        .getPortsStep()) {
        result << port;
    }
    return result;
}

QVariantList SettingsModeController::getPortDir(const QString& axisName) const
{
    QVariantList result;
    for(auto port: core::Board::instance()
        .getAxis(axisName.toStdString())
        .ports
        .getPortsDir()) {
        result << port;
    }
    return result;
}

QVariantList SettingsModeController::getPortHome(const QString& axisName) const
{
    QVariantList result;
    for(auto port: core::Board::instance()
        .getAxis(axisName.toStdString())
        .ports
        .getPortsHome()) {
        result << port;
    }
    return result;
}

double SettingsModeController::getSpeed(const QString& axisName) const
{
    return core::Board::instance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .getSpeed<core::SpeedUnits::MM_PER_MIN>();
}

double SettingsModeController::getTimeToSpeed(const QString& axisName) const
{
    return core::Board::instance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .getSpeedTimeAcc();
}

double SettingsModeController::getSpeedHomingForward(const QString& axisName) const
{
    return core::Board::instance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .getSpeedHomeFwd<core::SpeedUnits::MM_PER_MIN>();
}

double SettingsModeController::getSpeedHomingBackward(const QString& axisName) const
{
    return core::Board::instance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .getSpeedHomeBack<core::SpeedUnits::MM_PER_MIN>();
}

void SettingsModeController::setLimitLow(const QString& axisName, double value)
{
    core::Board::instance()
            .getAxis(axisName.toStdString())
            .limits
            .setLow(value);
}

void SettingsModeController::setLimitHigh(const QString& axisName, double value)
{
    core::Board::instance()
            .getAxis(axisName.toStdString())
            .limits
            .setHigh(value);
}

void SettingsModeController::setDistForSteps(const QString& axisName, double value)
{
    core::Board::instance()
            .getAxis(axisName.toStdString())
            .gearRatio
            .setDist(value);
}

void SettingsModeController::setStepsForDist(const QString& axisName, double value)
{
    core::Board::instance()
            .getAxis(axisName.toStdString())
            .gearRatio
            .setSteps(value);
}

void SettingsModeController::setSpeed(const QString& axisName, double value)
{
    core::Board::instance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .setSpeed(value);
}

void SettingsModeController::setTimeToSpeed(const QString& axisName, double value)
{
    core::Board::instance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .setSpeedTime(value);
}

void SettingsModeController::setPortStep(const QString& axisName, const QVariantList& values)
{    
    qDebug() << __FUNCTION__;
    qDebug() << values;
    core::Board::instance()
            .getAxis(axisName.toStdString())
            .ports
            .setPortsStep(toStdVector<uint32_t>(values));
}

void SettingsModeController::setPortHome(const QString& axisName, const QVariantList& values)
{    
    core::Board::instance()
            .getAxis(axisName.toStdString())
            .ports
            .setPortsHome(toStdVector<uint32_t>(values));
}

void SettingsModeController::setPortDir(const QString& axisName, const QVariantList& values)
{
    core::Board::instance()
            .getAxis(axisName.toStdString())
            .ports
            .setPortsDir(toStdVector<uint32_t>(values));
}

void SettingsModeController::setSpeedHomingForward(const QString& axisName, double value)
{
    core::Board::instance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .setSpeedHomeFwd(value);
}

void SettingsModeController::setSpeedHomingBackward(const QString& axisName, double value)
{
    core::Board::instance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .setSpeedNomeBack(value);
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
    auto path = QDir(QCoreApplication::applicationDirPath()).filePath(".config");
    saveToFile(path);
}

void SettingsModeController::load()
{
    auto path = QDir(QCoreApplication::applicationDirPath()).filePath(".config");
    loadFromFile(path);
}

QVariant SettingsModeController::toVariant() const
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

void SettingsModeController::fromVariant(const QVariant& variant)
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

