#include "OperatorModeController.h"
#include "BoardController.h"
#include <stdexcept>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QDir>
#include <QCoreApplication>

namespace keys {

constexpr const char* x_range = "x_range";
constexpr const char* y_range = "y_range";
constexpr const char* height = "height";
constexpr const char* repeats_count = "repeats_count";
constexpr const char* speed_factor = "speed_factor";

}

static inline QString getParamsPath() {
    return QDir(QCoreApplication::applicationDirPath())
            .filePath(".treater_parameters");
}

OperatorModeController::OperatorModeController(QObject *parent) : QObject(parent)
{
    loadParameters(getParamsPath());
}

OperatorModeController::~OperatorModeController()
{
    saveParameters(getParamsPath());
}

bool OperatorModeController::findHome()
{
    return BoardController::getInstance()
            .homeAllAxis();
}

bool OperatorModeController::moveToInitialPos()
{
    return BoardController::getInstance()
            .moveToInitialPos();
}

bool OperatorModeController::moveToZeroPos()
{
    double speed = mProcessParameters[keys::speed_factor].toDouble() / 100.0;
    return BoardController::getInstance()
            .moveToZeroPos("XY", speed);
}

bool OperatorModeController::setProcessParameters(double xRange, double yRange,
                                                  double height, int repeatsCount,
                                                  double speedFactor)
{
    mProcessParameters[keys::x_range] = xRange;
    mProcessParameters[keys::y_range] = yRange;
    mProcessParameters[keys::height] = height;
    mProcessParameters[keys::repeats_count] = repeatsCount;
    mProcessParameters[keys::speed_factor] = speedFactor;    
    return true;
}

bool OperatorModeController::startTreater()
{
    return BoardController::getInstance()
            .startTreater(
                mProcessParameters[keys::x_range].toDouble(),
                mProcessParameters[keys::y_range].toDouble(),
                mProcessParameters[keys::height].toDouble(),
                mProcessParameters[keys::repeats_count].toInt(),
                mProcessParameters[keys::speed_factor].toDouble() / 100.0, // Percent to factor
                100
            );
}

QVariant OperatorModeController::getProcessParameters()
{
    return mProcessParameters;
}

bool OperatorModeController::setProcessParameters(const QVariant& parameters)
{
    auto map = parameters.toMap();
    std::array<bool, 5> correct{};
    setProcessParameters(map[keys::x_range].toDouble(&correct[0]),
            map[keys::y_range].toDouble(&correct[1]),
            map[keys::height].toDouble(&correct[2]),
            map[keys::repeats_count].toDouble(&correct[3]),
            map[keys::speed_factor].toDouble(&correct[4]));
    auto result = std::accumulate(correct.cbegin(), correct.cend(), true, std::logical_and{});
    return result;
}

void OperatorModeController::cancel()
{
    BoardController::getInstance()
            .cancel();
}

void OperatorModeController::saveParameters(const QString& path)
{
    QFile file{path};
    if(file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument::fromVariant(mProcessParameters).toJson());
        file.close();        
    }
}

void OperatorModeController::loadParameters(const QString& path)
{
    QFile file{path};
    if(file.open(QIODevice::ReadOnly)) {
        auto doc = QJsonDocument::fromJson(file.readAll());
        mProcessParameters = doc.toVariant().toMap();
        file.close();
    }
}

void OperatorModeController::loadDefaultParameters()
{
    setProcessParameters(200.0, 200.0, 50.0, 1, 0.5);
}


