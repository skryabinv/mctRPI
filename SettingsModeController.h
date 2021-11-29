#pragma once

#include <QObject>
#include <QVariant>

// Режим настроек
class SettingsModeController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString descritpion MEMBER mDescription CONSTANT)
public:
    enum HomeDirection {
        HomeDirection_Negative,
        HomeDirection_Positive
    };
public:
    explicit SettingsModeController(QObject *parent = nullptr);

    Q_INVOKABLE double getLimitLow(const QString& axisName) const;
    Q_INVOKABLE double getLimitHigh(const QString& axisName) const;
    Q_INVOKABLE double getDistForSteps(const QString& axisName) const;
    Q_INVOKABLE double getStepsForDist(const QString& axisName) const;
    Q_INVOKABLE QVariantList getPortStep(const QString& axisName) const;
    Q_INVOKABLE QVariantList getPortDir(const QString& axisName) const;
    Q_INVOKABLE QVariantList getPortHome(const QString& axisName) const;
    Q_INVOKABLE double getSpeed(const QString& axisName) const;
    Q_INVOKABLE double getTimeToSpeed(const QString& axisName) const;
    Q_INVOKABLE double getSpeedHomingForward(const QString& axisName) const;
    Q_INVOKABLE double getSpeedHomingBackward(const QString& axisName) const;
    Q_INVOKABLE HomeDirection getHomeDirection(const QString& axisName) const;


    Q_INVOKABLE void setLimitLow(const QString& axisName, double value);
    Q_INVOKABLE void setLimitHigh(const QString& axisName, double value);
    Q_INVOKABLE void setDistForSteps(const QString& axisName, double value);
    Q_INVOKABLE void setStepsForDist(const QString& axisName, double value);
    Q_INVOKABLE void setSpeed(const QString& axisName, double value);
    Q_INVOKABLE void setTimeToSpeed(const QString& axisName, double value);
    Q_INVOKABLE void setPortStep(const QString& axisName, const QVariantList& values);
    Q_INVOKABLE void setPortHome(const QString& axisName, const QVariantList& values);
    Q_INVOKABLE void setPortDir(const QString& axisName, const QVariantList& values);
    Q_INVOKABLE void setSpeedHomingForward(const QString& axisName, double value);
    Q_INVOKABLE void setSpeedHomingBackward(const QString& axisName, double value);
    Q_INVOKABLE void setHomeDirection(const QString& axisName, HomeDirection value);


    Q_INVOKABLE QVariant getAxisSettings(const QString& axisName) const;
    Q_INVOKABLE void setAxisSettings(const QString& axisName, const QVariantMap& axisSettings);

    Q_INVOKABLE void save() const;
    Q_INVOKABLE void load();

    // Преобразование настроек в таблицу QVariant
    QVariant toVariant() const;
    void fromVariant(const QVariant& variant);

signals:    
private:
    void saveToFile(const QString& path) const;
    void loadFromFile(const QString& path);
    const QString mDescription = tr("Настройки");
};

