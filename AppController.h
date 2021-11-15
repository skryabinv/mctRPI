#pragma once

#include <QObject>

class SettingsModeController;
class ManualModeController;
class OperatorModeController;

// Основной контроллер приложения: осуществляет навигацию и управление режимами
// Отвечает за создание и уничтожение контроллеров режима
class AppController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SettingsModeController* settingsModeController MEMBER mSettingsController CONSTANT)
    Q_PROPERTY(ManualModeController* manualModeController MEMBER mManualModeController CONSTANT)
    Q_PROPERTY(OperatorModeController* operatorModeController MEMBER mOperatorModeController CONSTANT)
public:
    explicit AppController(QObject *parent = nullptr);
    Q_INVOKABLE bool goOperatorMode();
    Q_INVOKABLE bool goSettingsMode();
    Q_INVOKABLE bool goManualMode();
    Q_INVOKABLE bool resetMode();
signals:
    void modeManualActivated();
    void modeOperatorActivated();
    void modeSettingsActivated();
    void modeReseted();
private:
    SettingsModeController* mSettingsController{};
    ManualModeController* mManualModeController{};
    OperatorModeController* mOperatorModeController{};
};

