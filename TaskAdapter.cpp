#include "TaskAdapter.h"
#include <QEvent>
#include <QCoreApplication>

namespace Events {

const QEvent::Type TaskStarted = static_cast<QEvent::Type>(QEvent::Type::User + 1);
const QEvent::Type TaskFinished = static_cast<QEvent::Type>(QEvent::Type::User + 2);


}

TaskAdapter::TaskAdapter(core::RtTaskSharedPtr task,
                         QObject *parent)
    : QObject(parent),
      mTask{std::move(task)}
{

}

bool TaskAdapter::event(QEvent *event)
{
    if(event->type() == Events::TaskStarted) {
        emit taskStarted();
    } else if(event->type() == Events::TaskFinished) {
        emit taskFinished(mTask->isCanceled());
    }
    return true;
}

bool TaskAdapter::runImpl()
{
    if(mTask) {
        // postEvent Started
        auto startedEvent = new QEvent(Events::TaskStarted);
        QCoreApplication::postEvent(this, startedEvent);
        bool result = mTask->run();
        auto finishedEvent = new QEvent(Events::TaskFinished);
        QCoreApplication::postEvent(this, finishedEvent);
        // postEvent Done
        return result;
    }
    return true;
}

void TaskAdapter::cancelImpl()
{
    mTask->cancel();
}
