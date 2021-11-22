#include "AppController.h"
#include "ManualModeController.h"
#include "OperatorModeController.h"
#include "SettingsModeController.h"


AppController::AppController(QObject *parent) : QObject(parent)
{
    mManualModeController = new ManualModeController(this);
    mSettingsController = new SettingsModeController(this);
    mOperatorModeController = new OperatorModeController(this);
}

bool AppController::goOperatorMode()
{
    emit modeOperatorActivated();
    return true;
}

bool AppController::goSettingsMode()
{
    emit modeSettingsActivated();
    return true;
}

bool AppController::goManualMode()
{
    emit modeManualActivated();
    return true;
}

bool AppController::resetMode()
{
    emit modeReseted();
    return true;
}

