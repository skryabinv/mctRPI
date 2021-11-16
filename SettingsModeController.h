#pragma once

#include <QObject>

// Режим настроек
class SettingsModeController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString descritpion MEMBER mDescription CONSTANT)
public:
    explicit SettingsModeController(QObject *parent = nullptr);
    void loadFromFile(const QString& path);

    Q_INVOKABLE double getLimitLow(const QString& axisName) const;
    Q_INVOKABLE double getLimitHigh(const QString& axisName) const;
    Q_INVOKABLE double getDistForSteps(const QString& axisName) const;
    Q_INVOKABLE double getStepsForDist(const QString& axisName) const;
    Q_INVOKABLE QList<int> getPortStep(const QString& axisName) const;
    Q_INVOKABLE QList<int> getPortDir(const QString& axisName) const;
    Q_INVOKABLE QList<int> getPortHome(const QString& axisName) const;
    Q_INVOKABLE double getSpeed(const QString& axisName) const;
    Q_INVOKABLE double getTimeToSpeed(const QString& axisName) const;

    Q_INVOKABLE void setLimitLow(const QString& axisName, double value);
    Q_INVOKABLE void setLimitHigh(const QString& axisName, double value);
    Q_INVOKABLE void setSpeed(const QString& axisName, double value);
    Q_INVOKABLE void setTimeToSpeed(const QString& axisName, double value);
    Q_INVOKABLE void setPortStep(const QString& axisName, const QList<int>& values);
    Q_INVOKABLE void setPortHome(const QString& axisName, const QList<int>& values);
    Q_INVOKABLE void setPortDir(const QString& axisName, const QList<int>& values);

signals:
public slots:
    void saveToFile(const QString& path) const;
private:
    const QString mDescription = tr("Настройки");
};

