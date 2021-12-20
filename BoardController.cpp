#include "BoardController.h"
#include "core/Board.h"
#include "core/Axis.h"
#include "core/RtTaskDispatcher.h"
#include "core/RtTaskMulti.h"
#include "core/RtTaskProcess.h"
#include "core/OutputPort.h"
#include "core/CoronaTreater.h"
#include "TaskAdapter.h"
#include <QDebug>
#include <QTimer>
#include <QStringLiteral>
#include <QEvent>
#include <QCoreApplication>

namespace Events {
static constexpr QEvent::Type CoronaStateChanged = static_cast<QEvent::Type>(QEvent::Type::User + 3);
}

BoardController::BoardController(QObject *parent)
    : QObject(parent),
    mCurrentTask{std::make_shared<core::RtTask>("TaskEmpty", true)},
    mProcessTimer{new QTimer(this)}
{
    // Stop timer if any task finished
    connect(this, &BoardController::taskFinished,
            mProcessTimer, &QTimer::stop);
    core::Board::getInstance()
            .getCoronaTreater()
            .setCoronaStateChangedListener([this](bool){
        QCoreApplication::postEvent(this, new QEvent(Events::CoronaStateChanged));        
    });
}

double BoardController::getAxisPos(const QString &axis) const
{
    return core::Board::getInstance()
            .getAxis(axis.toStdString())
            .getCurrentPos();
}

bool BoardController::homeAxis(const QString &axis)
{
    if(isReady()) {
        mCurrentTask = wrapHomingTask(
                    core::Board::getInstance()
                    .getAxis(axis.toStdString())
                    .createTaskFindHome(),
                    axis);
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool BoardController::homeAllAxis()
{    
    if(isReady()) {
        mCurrentTask = wrapHomingTask(
                    core::Board::getInstance()
                    .createTaskHomeAll(),
                    QStringLiteral("XYZ"));
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool BoardController::jogStart(const QString& axis, double speedFactor, double distance)
{    
    if(isReady()) {
        mCurrentTask = wrapTask(
                    core::Board::getInstance()
                    .getAxis(axis.toStdString())
                    .createTaskJog(speedFactor, distance));
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

void BoardController::cancel()
{    
    mCurrentTask->cancel();
}

bool BoardController::isHomingDone(const QString &axis) const
{
    return core::Board::getInstance()
            .getAxis(axis.toStdString())
            .isHomingDone();
}

bool BoardController::isBusy() const
{
    return !mCurrentTask->isDone();
}

bool BoardController::isReady() const
{
    return mCurrentTask->isDone();
}

bool BoardController::getOutputState() const
{
    return false;
}

bool BoardController::startProcess(const ProcessData& data,
                                   int progressIntervalMs)
{       
    if(isReady()) {
        auto task = core::Board::getInstance()
                .getCoronaTreater()
                .createTaskProcess(data.rangeX, data.rangeY,
                                   data.height, data.repeats,
                                   data.speedFactor);
        if(progressIntervalMs != 0) {
            mProcessTimer->disconnect();
            mProcessTimer->start(progressIntervalMs);
            connect(mProcessTimer, &QTimer::timeout, this, [task, this](){
                emit processProgressChanged(task->getProgress());
            });
        }
        mCurrentTask = wrapTask(std::move(task));
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool BoardController::moveToZeroPos(const QString &axes, double speedFraction)
{
    if(isReady()) {
        std::vector<core::RtTaskSharedPtr> tasksList;
        std::array<QString, 3> axisNames = {
            QStringLiteral("X"),
            QStringLiteral("Y"),
            QStringLiteral("Z")
        };
        for(const auto& axis: axisNames) {
            if(axes.contains(axis)) {
                auto task = core::Board::getInstance()
                        .getAxis(axis.toStdString())
                        .createTaskMoveTo(speedFraction, 0.0);
                tasksList.push_back(std::move(task));
            }
        }
        auto task = std::make_shared<core::RtTaskMulti>(std::move(tasksList));
        mCurrentTask = wrapTask(std::move(task));
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool BoardController::moveToInitialPos()
{    
    if(isReady()) {
        auto task = core::Board::getInstance()
                .getCoronaTreater()
                .createTaskMoveToInitialPos();
        mCurrentTask = wrapTask(std::move(task));
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
        return true;
    }
    return false;
}

bool BoardController::setTreaterEnabled(bool value)
{    
    if(isReady()) {
        auto task = core::Board::getInstance()
                .getCoronaTreater()
                .createTaskOnOff(value);
        mCurrentTask = wrapTask(task);
        core::RtTaskDispatcher::getInstance()
                .scheduleTask(mCurrentTask);
    }
    return true;
}

BoardController &BoardController::getInstance()
{
    static BoardController instance;
    return instance;
}

core::RtTaskSharedPtr BoardController::wrapTask(core::RtTaskSharedPtr task)
{
    auto result = createTaskAdapter(std::move(task));
    connect(result.get(), &TaskAdapter::taskStarted,
            this, &BoardController::taskStarted);
    connect(result.get(), &TaskAdapter::taskFinished,
            this, &BoardController::taskFinished);
    return result;
}

core::RtTaskSharedPtr BoardController::wrapHomingTask(core::RtTaskSharedPtr task,
                                                      const QString &axes)
{
    auto result = createTaskAdapter(std::move(task));
    connect(result.get(), &TaskAdapter::taskStarted,
            this, &BoardController::taskStarted);
    connect(result.get(), &TaskAdapter::taskFinished,
            this, [axes, this](bool canceled){
        if(!canceled) {
            emit axesHomingDone(axes);
        }
        emit taskFinished(canceled);
    });
    return result;
}

bool BoardController::event(QEvent *event)
{
    if(event->type() == Events::CoronaStateChanged) {
        emit coronaStateChanged(core::Board::getInstance()
                                .getCoronaTreater()
                                .getCoronaState());
        return true;
    }
    return false;
}
