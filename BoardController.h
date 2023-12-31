#pragma once

#include <QObject>
#include "core/RtTask.h"

class QTimer;

struct ProcessData {
    double rangeX;
    double rangeY;
    double height;
    int repeats;
    double speedFactor;
};

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
    Q_INVOKABLE bool isHomingAllDone() const;
    Q_INVOKABLE bool isHomingDone(const QString& axis) const;
    Q_INVOKABLE bool isBusy() const;
    Q_INVOKABLE bool isReady() const;
    Q_INVOKABLE bool getOutputState() const;
    Q_INVOKABLE bool startProcess(const ProcessData& data,
                                  // notify by signal with this timer
                                  int progressIntervalMs = 0);
    // axes ("XYZ", "XY", etc)
    Q_INVOKABLE bool moveToZeroPos(const QString& axes, double speedFraction);
    Q_INVOKABLE bool moveToInitialPos();
    Q_INVOKABLE bool setTreaterEnabled(bool value);    
    static BoardController& getInstance();
signals:    
    void taskStarted();
    void taskFinished(bool canceled);    
    // QString "XY", "XYZ", "X", etc
    void axesHomingDone(const QString& axes);
    void processProgressChanged(double progress);
    void coronaStateChanged(bool value);
private:
    core::RtTaskSharedPtr wrapTask(core::RtTaskSharedPtr task);
    core::RtTaskSharedPtr wrapHomingTask(core::RtTaskSharedPtr task,
                                         const QString& axes);
    core::RtTaskSharedPtr mCurrentTask{};
    QTimer* mProcessTimer;

    // QObject interface
public:
    bool event(QEvent *event);
};

