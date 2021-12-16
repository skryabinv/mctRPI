#include "SettingsModeController.h"
#include <QJsonDocument>
#include <QVariantMap>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QStringLiteral>
#include <array>
#include "core/Board.h"
#include "core/Axis.h"
#include "core/CoronaTreater.h"
#include "core/OutputPort.h"

namespace HomeDirection {
static constexpr const char* Positive{"positive"};
static constexpr const char* Negative{"negative"};
}

namespace keys {

// Axis settings keys

static constexpr const char* limit_low = "limit_low";
static constexpr const char* limit_high = "limit_high";
static constexpr const char* dist_for_steps = "dist_for_steps";
static constexpr const char* steps_for_dist = "steps_for_dist";
static constexpr const char* port_step = "port_step";
static constexpr const char* port_dir = "port_dir";
static constexpr const char* port_home = "port_home";
static constexpr const char* speed = "speed";
static constexpr const char* time_to_speed = "time_to_speed";
static constexpr const char* speed_homing_forward = "speed_homing_forward";
static constexpr const char* speed_homing_backward = "speed_homing_backward";
static constexpr const char* home_direction = "home_direction";
static constexpr const char* pos_home = "pos_home";
static constexpr const char* pos_safe = "pos_safe";

// Treater keys

static constexpr const char* corona_width = "corona_width";
static constexpr const char* initial_pos_x = "initial_pos_x";
static constexpr const char* initial_pos_y = "initial_pos_y";
static constexpr const char* height = "height";

static constexpr const char* corona_enable_pin = "corona_enable_pin";
static constexpr const char* corona_disable_pin = "corona_disable_pin";
static constexpr const char* corona_ports_delay_ms = "corona_ports_delay_ms";

static constexpr const char* corona_speed_x = "corona_speed_x";
static constexpr const char* corona_speed_z = "corona_speed_z";

}

static inline QString getSettingsPath() {
    return QDir(QCoreApplication::applicationDirPath())
            .filePath(QStringLiteral(".config"));
}


template <typename ResType, typename HoldType = double>
static std::vector<ResType> toStdVector(const QVariantList& variantList) {
    std::vector<ResType> result;
    for(const auto& val: variantList) {
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
            .getWorkingHeight();
}

double SettingsModeController::getTreaterCoronaWidth() const
{
    return core::Board::getInstance()
            .getCoronaTreater()
            .getCoronaWidth();
}

uint32_t SettingsModeController::getTreaterEnablePin() const
{
    return core::Board::getInstance()
            .getCoronaTreater()
            .getEnableTreaterPin();
}

uint32_t SettingsModeController::getTreaterDisablePin() const
{
    return core::Board::getInstance()
            .getCoronaTreater()
            .getDisableTreaterPin();
}

int SettingsModeController::getTreaterPortsDelayMs() const
{
    return core::Board::getInstance()
            .getCoronaTreater()
            .getPortDelayMs();
}

double SettingsModeController::getTreaterSpeedFractionX() const
{
    return core::Board::getInstance()
            .getCoronaTreater()
            .getSpeedFractionX();
}

double SettingsModeController::getTreaterSpeedFractionZ() const
{
    return core::Board::getInstance()
            .getCoronaTreater()
            .getSpeedFractionZ();
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

void SettingsModeController::setTreaterEnablePin(uint32_t pin)
{
    core::Board::getInstance()
            .getCoronaTreater()
            .setEnableTreaterPin(pin);

}

void SettingsModeController::setTreaterDisablePin(uint32_t pin)
{
    core::Board::getInstance()
            .getCoronaTreater()
            .setDisableTreaterPin(pin);
}

void SettingsModeController::setTreaterPortsDelayMs(double value)
{
    core::Board::getInstance()
            .getCoronaTreater()
            .setPortDelayMs(value);

}

void SettingsModeController::setTreaterSpeedFractionX(double value)
{
    core::Board::getInstance()
            .getCoronaTreater()
            .setSpeedFractionX(value);
}

void SettingsModeController::setTreaterSpeedFractionZ(double value)
{
    core::Board::getInstance()
            .getCoronaTreater()
            .setSpeedFractionZ(value);
}

QVariant SettingsModeController::getAxisSettings(const QString& axisName) const
{    
    QVariantMap axisSettings;
    axisSettings[keys::limit_low] = getLimitLow(axisName);
    axisSettings[keys::limit_high] = getLimitHigh(axisName);
    axisSettings[keys::dist_for_steps] = getDistForSteps(axisName);
    axisSettings[keys::steps_for_dist] = getStepsForDist(axisName);
    axisSettings[keys::port_step] = getPortStep(axisName);
    axisSettings[keys::port_dir] = getPortDir(axisName);
    axisSettings[keys::port_home] = getPortHome(axisName);
    axisSettings[keys::speed] = getSpeed(axisName);
    axisSettings[keys::time_to_speed] = getTimeToSpeed(axisName);
    axisSettings[keys::speed_homing_forward] = getSpeedHomingForward(axisName);
    axisSettings[keys::speed_homing_backward] = getSpeedHomingBackward(axisName);
    axisSettings[keys::home_direction] = getHomeDirection(axisName);
    axisSettings[keys::pos_home] = getPosHome(axisName);
    axisSettings[keys::pos_safe] = getPosSafe(axisName);
    return axisSettings;
}

void SettingsModeController::setAxisSettings(const QString& axisName, const QVariantMap& axisSettings)
{    
    setLimitLow(axisName, axisSettings[keys::limit_low].toDouble());
    setLimitHigh(axisName, axisSettings[keys::limit_high].toDouble());
    setDistForSteps(axisName, axisSettings[keys::dist_for_steps].toDouble());
    setStepsForDist(axisName, axisSettings[keys::steps_for_dist].toDouble());
    setPortStep(axisName, axisSettings[keys::port_step].toList());
    setPortDir(axisName, axisSettings[keys::port_dir].toList());
    setPortHome(axisName, axisSettings[keys::port_home].toList());
    setSpeed(axisName, axisSettings[keys::speed].toDouble());
    setTimeToSpeed(axisName, axisSettings[keys::time_to_speed].toDouble());
    setSpeedHomingForward(axisName, axisSettings[keys::speed_homing_forward].toDouble());
    setSpeedHomingBackward(axisName, axisSettings[keys::speed_homing_backward].toDouble());
    setHomeDirection(axisName, axisSettings[keys::home_direction].toString());
    setPosHome(axisName, axisSettings[keys::pos_home].toDouble());
    setPosSafe(axisName, axisSettings[keys::pos_safe].toDouble());
}

QVariant SettingsModeController::getTreaterSettings() const
{
    QVariantMap result;
    result[keys::corona_disable_pin] = getTreaterDisablePin();
    result[keys::corona_enable_pin] = getTreaterEnablePin();
    result[keys::corona_ports_delay_ms] = getTreaterPortsDelayMs();
    result[keys::corona_width] = getTreaterCoronaWidth();
    result[keys::initial_pos_x] = getTreaterInitialPosX();
    result[keys::initial_pos_y] = getTreaterInitialPosY();
    result[keys::height] = getTreaterHeight();
    result[keys::corona_speed_x] = getTreaterSpeedFractionX();
    result[keys::corona_speed_z] = getTreaterSpeedFractionZ();
    return result;
}

void SettingsModeController::setTreaterSettings(const QVariantMap& settings)
{    
    setTreaterDisablePin(settings[keys::corona_disable_pin].toUInt());
    setTreaterEnablePin(settings[keys::corona_enable_pin].toUInt());
    setTreaterPortsDelayMs(settings[keys::corona_ports_delay_ms].toDouble());
    setTreaterCoronaWidth(settings[keys::corona_width].toDouble());
    setTreaterInitialPosX(settings[keys::initial_pos_x].toDouble());
    setTreaterInitialPosY(settings[keys::initial_pos_y].toDouble());
    setTreaterHeight(settings[keys::height].toDouble());
    setTreaterSpeedFractionX(settings[keys::corona_speed_x].toDouble());
    setTreaterSpeedFractionZ(settings[keys::corona_speed_z].toDouble());
}

void SettingsModeController::save() const
{
    saveToFile(getSettingsPath());
}

void SettingsModeController::load()
{    
    loadFromFile(getSettingsPath());
}

QVariant SettingsModeController::toVariant() const
{
    QVariantMap result;    
    std::array<QString, 3> axisNames { "X", "Y", "Z" };
    for(const auto& axisName: axisNames) {
        result[axisName] = getAxisSettings(axisName);
    }
    result["treater_settings"] = getTreaterSettings();
    return result;
}

void SettingsModeController::fromVariant(const QVariant& variant)
{
    QVariantMap map = variant.toMap();    
    std::array<QString, 3> axisNames { "X", "Y", "Z" };
    for(const auto& axisName: axisNames) {
        QVariantMap axisSettings = map[axisName].toMap();
        setAxisSettings(axisName, axisSettings);
    }
    setTreaterSettings(map["treater_settings"].toMap());
}

