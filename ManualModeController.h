#pragma once

#include <QObject>

// Ручной режим управления
class ManualModeController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString description MEMBER mDescription CONSTANT)
    Q_PROPERTY(QString selectedAxis MEMBER mSelectedAxis READ getSelectedAxis WRITE setSelectedAxis NOTIFY selectedAxisChanged)
public:
    explicit ManualModeController(QObject *parent = nullptr);    
    QString getSelectedAxis() const;
    void setSelectedAxis(const QString& axis);
    Q_INVOKABLE bool homeSelectedAxis();
    Q_INVOKABLE bool homeAllAxes();  
    Q_INVOKABLE bool jogStart(double speedFactor, double distance);    
    Q_INVOKABLE bool jogStop();
signals:
    void selectedAxisChanged(const QString axis);
private:
    const QString mDescription = tr("Режим ручного управления");
    QString mSelectedAxis{"X"};
};

