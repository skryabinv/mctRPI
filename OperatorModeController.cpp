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

bool OperatorModeController::moveToHomePos()
{
    return BoardController::getInstance()
            .moveToHomePos();
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
    assert(mProcessParameters.contains(keys::x_range));
    assert(mProcessParameters.contains(keys::y_range));
    assert(mProcessParameters.contains(keys::height));
    assert(mProcessParameters.contains(keys::repeats_count));
    assert(mProcessParameters.contains(keys::speed_factor));
    return BoardController::getInstance()
            .startTreater(
                mProcessParameters[keys::x_range].toDouble(),
                mProcessParameters[keys::y_range].toDouble(),
                mProcessParameters[keys::height].toDouble(),
                mProcessParameters[keys::repeats_count].toInt(),
                mProcessParameters[keys::speed_factor].toDouble()
            );
}

QVariant OperatorModeController::getProcessParameters()
{
    return mProcessParameters;
}

bool OperatorModeController::setProcessParameters(const QVariant& parameters)
{
    mProcessParameters = parameters.toMap();
    qDebug() << __FUNCTION__ << mProcessParameters;
    return true;
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


