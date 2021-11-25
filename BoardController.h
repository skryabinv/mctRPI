#pragma once

#include <QObject>
#include "core/RtTask.h"

class BoardController : public QObject
{
    Q_OBJECT    
public:
    explicit BoardController(QObject *parent = nullptr);
    Q_INVOKABLE double getAxisPos(const QString& axis) const;
    Q_INVOKABLE bool homeAxis(const QString& axis);
    Q_INVOKABLE bool homeAllAxis();
    Q_INVOKABLE bool jogStart(const QString &axis, double speedFactor, double distance);
    Q_INVOKABLE void cancel();
    Q_INVOKABLE bool isHomingDone(const QString& axis) const;
    Q_INVOKABLE bool setOutEnabled(bool value);
    static BoardController& getInstance();
signals:
    void taskStarted();
    void taskFinished(bool canceled);
private:
    core::RtTaskSharedPtr wrapTask(core::RtTaskSharedPtr task);
    core::RtTaskSharedPtr mCurrentTask{};
};

