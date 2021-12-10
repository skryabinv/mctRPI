#include "SettingsModeController.h"
#include <QJsonDocument>
#include <QVariantMap>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QStringLiteral>
#include "core/Board.h"
#include "core/Axis.h"
#include "core/CoronaTreater.h"

namespace HomeDirection {
static constexpr const char* Positive{"positive"};
static constexpr const char* Negative{"negative"};
}



template <typename ResType, typename HoldType = double>
static std::vector<ResType> toStdVector(const QVariantList& variantList) {
    std::vector<ResType> result;
    for(const auto& val: variantList) {
        result.push_back(ResType(val.value<HoldType>()));
    }
    return result;
}

static constexpr const char* FilePath = ".config";

SettingsModeController::SettingsModeController(QObject *parent) : QObject(parent)
{
     load();
}

void SettingsModeController::saveToFile(const QString& path) const
{
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)) {
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
    return core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .limits
            .getLow();
}

double SettingsModeController::getLimitHigh(const QString& axisName) const
{
    return core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .limits
            .getHigh();
}

double SettingsModeController::getDistForSteps(const QString& axisName) const
{
    return core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .gearRatio
            .getDist();
}

double SettingsModeController::getStepsForDist(const QString& axisName) const
{
    return core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .gearRatio
            .getSteps();
}

QVariantList SettingsModeController::getPortStep(const QString& axisName) const
{    
    QVariantList result;
    for(auto port: core::Board::getInstance()
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
    for(auto port: core::Board::getInstance()
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
    for(auto port: core::Board::getInstance()
        .getAxis(axisName.toStdString())
        .ports
        .getPortsHome()) {
        result << port;
    }
    return result;
}

double SettingsModeController::getSpeed(const QString& axisName) const
{
    return core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .getSpeed<core::SpeedUnits::MM_PER_MIN>();
}

double SettingsModeController::getTimeToSpeed(const QString& axisName) const
{
    return core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .getSpeedTimeAcc();
}

double SettingsModeController::getSpeedHomingForward(const QString& axisName) const
{
    return core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .getSpeedHomeFwd<core::SpeedUnits::MM_PER_MIN>();
}

double SettingsModeController::getSpeedHomingBackward(const QString& axisName) const
{
    return core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .getSpeedHomeBack<core::SpeedUnits::MM_PER_MIN>();
}

QString SettingsModeController::getHomeDirection(const QString &axisName) const
{
    auto dir = core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .getHomeDirection();
    return dir == core::HomeDirection::Negative ?
                HomeDirection::Negative:
                HomeDirection::Positive;
}

double SettingsModeController::getPosHome(const QString &axisName) const
{
    return core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .getPosHome();
}

double SettingsModeController::getPosSafe(const QString &axisName) const
{
    return core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .getSafePos();
}

void SettingsModeController::setLimitLow(const QString& axisName, double value)
{
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .limits
            .setLow(value);
}

void SettingsModeController::setLimitHigh(const QString& axisName, double value)
{
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .limits
            .setHigh(value);
}

void SettingsModeController::setDistForSteps(const QString& axisName, double value)
{
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .gearRatio
            .setDist(value);
}

void SettingsModeController::setStepsForDist(const QString& axisName, double value)
{
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .gearRatio
            .setSteps(value);
}

void SettingsModeController::setSpeed(const QString& axisName, double value)
{
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .setSpeed(value);
}

void SettingsModeController::setTimeToSpeed(const QString& axisName, double value)
{
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .setSpeedTime(value);
}

void SettingsModeController::setPortStep(const QString& axisName, const QVariantList& values)
{    
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .ports
            .setPortsStep(toStdVector<uint32_t>(values));
}

void SettingsModeController::setPortHome(const QString& axisName, const QVariantList& values)
{    
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .ports
            .setPortsHome(toStdVector<uint32_t>(values));
}

void SettingsModeController::setPortDir(const QString& axisName, const QVariantList& values)
{
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .ports
            .setPortsDir(toStdVector<uint32_t>(values));
}

void SettingsModeController::setSpeedHomingForward(const QString& axisName, double value)
{
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .setSpeedHomeFwd(value);
}

void SettingsModeController::setSpeedHomingBackward(const QString& axisName, double value)
{
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .setSpeedNomeBack(value);
}

void SettingsModeController::setHomeDirection(const QString &axisName, const QString& value)
{
    auto dir = value == HomeDirection::Negative ?
                core::HomeDirection::Negative :
                core::HomeDirection::Positive;
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .setHomeDirection(dir);
}

void SettingsModeController::setPosHome(const QString &axisName, double pos)
{
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .setPosHome(pos);
}

void SettingsModeController::setPosSafe(const QString &axisName, double value)
{
    core::Board::getInstance()
            .getAxis(axisName.toStdString())
            .speedSettings
            .setSafePos(value);
}

int SettingsModeController::getTreaterPin() const
{
    return core::Board::getInstance()
            .getCoronaTreater()
            .getCoronaPin();
}

double SettingsModeController::getTreaterInitialPosX() const
{
    return core::Board::getInstance()
            .getCoronaTreater()
            .getInitalPosX();
}

double SettingsModeController::getTreaterInitialPosY() const
{
    return core::Board::getInstance()
            .getCoronaTreater()
            .getInitalPosY();
}

double SettingsModeController::getTreaterHeight() const
{
    return core::Board::getInstance()
            .getCoronaTreater()
            .getHeight();
}

double SettingsModeController::getTreaterCoronaWidth() const
{
    return core::Board::getInstance()
            .getCoronaTreater()
            .getCoronaWidth();
}

void SettingsModeController::setTreaterPin(uint32_t pin)
{
    core::Board::getInstance()
            .getCoronaTreater()
            .setCoronaPin(pin);
}

void SettingsModeController::setTreaterInitialPosX(double value)
{
    core::Board::getInstance()
            .getCoronaTreater()
            .setInitialPosX(value);
}

void SettingsModeController::setTreaterInitialPosY(double value)
{
    core::Board::getInstance()
            .getCoronaTreater()
            .setInitialPosY(value);
}

void SettingsModeController::setTreaterHeight(double value)
{
    core::Board::getInstance()
            .getCoronaTreater()
            .setHeight(value);
}

void SettingsModeController::setTreaterCoronaWidth(double value)
{
    core::Board::getInstance()
            .getCoronaTreater()
            .setCoronaWidth(value);
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
    axisSettings["home_direction"] = getHomeDirection(axisName);
    axisSettings["pos_home"] = getPosHome(axisName);    
    axisSettings["pos_safe"] = getPosSafe(axisName);
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
    setHomeDirection(axisName, axisSettings["home_direction"].toString());
    setPosHome(axisName, axisSettings["pos_home"].toDouble());
    setPosSafe(axisName, axisSettings["pos_safe"].toDouble());
}

QVariant SettingsModeController::getTreaterSettings() const
{
    QVariantMap result;
    result["corona_pin"] = getTreaterPin();
    result["corona_width"] = getTreaterCoronaWidth();
    result["initial_pos_x"] = getTreaterInitialPosX();
    result["initial_pos_y"] = getTreaterInitialPosY();
    result["height"] = getTreaterHeight();
    return result;
}

void SettingsModeController::setTreaterSettings(const QVariantMap& settings)
{
    setTreaterPin(settings["corona_pin"].toUInt());
    setTreaterCoronaWidth(settings["corona_width"].toDouble());
    setTreaterInitialPosX(settings["initial_pos_x"].toDouble());
    setTreaterInitialPosY(settings["initial_pos_y"].toDouble());
    setTreaterHeight(settings["height"].toDouble());
}

void SettingsModeController::save() const
{    
    auto path = QDir(QCoreApplication::applicationDirPath())
            .filePath(FilePath);
    saveToFile(path);
}

void SettingsModeController::load()
{
    auto path = QDir(QCoreApplication::applicationDirPath())
            .filePath(FilePath);
    if(QFileInfo(path).exists()) {
        qDebug() << "Settings loaded from:" << path;
    } else {
        qDebug() << "Can't find .config file."
                 << "Default settings will be loaded.";
    }
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
    result["treater_settings"] = getTreaterSettings();
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
    setTreaterSettings(map["treater_settings"].toMap());
}

