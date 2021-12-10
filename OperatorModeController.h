#pragma once

#include <QObject>
#include <QVariantMap>

// Режим работы оператора
class OperatorModeController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString description MEMBER mDescription CONSTANT)
public:
    explicit OperatorModeController(QObject *parent = nullptr);
    ~OperatorModeController() override;
    Q_INVOKABLE bool findHome();
    Q_INVOKABLE bool moveToInitialPos();
    Q_INVOKABLE bool moveToHomePos();
    Q_INVOKABLE bool setProcessParameters(double xRange,
                                          double yRange,
                                          double height,
                                          int repeatsCount,
                                          double speedFactor);

    Q_INVOKABLE bool startTreater();

signals:
private:    
    void saveParameters(const QString& path);
    void loadParameters(const QString& path);
    void updateProcessParameters(const QVariantMap& processParameters);
    const QString mDescription = tr("Режим оператора");
    QVariantMap mProcessParameters;
};

