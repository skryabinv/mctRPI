#pragma once

#include <QObject>
#include "core/RtTask.h"


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
    Q_INVOKABLE double getAxisPos(const QString& axis) const;
    Q_INVOKABLE double getSelectedAxisPos() const;
    Q_INVOKABLE bool homeSelectedAxis();
    Q_INVOKABLE bool homeAllAxes();  
    Q_INVOKABLE bool jogStart(double speedFactor, double distance);    
    Q_INVOKABLE bool jogStop();
    Q_INVOKABLE void cancel();
signals:
    void selectedAxisChanged(const QString axis);
    void taskCanceled();
private:
    const QString mDescription = tr("Режим ручного управления");
    QString mSelectedAxis{"X"};
    core::RtTaskSharedPtr mCurrentTask{};
};

