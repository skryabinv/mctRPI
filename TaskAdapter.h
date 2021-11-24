#pragma once

#include <QObject>
#include "core/RtTask.h"

class TaskAdapter :
        public QObject,
        public core::RtTask
{
    Q_OBJECT
public:
    explicit TaskAdapter(core::RtTaskSharedPtr task, QObject *parent = nullptr);

signals:
    void taskStarted();
    void taskFinished(bool canceled);


    // QObject interface
public:
    bool event(QEvent *event) override;
private:
    core::RtTaskSharedPtr mTask{};

    // RtTask interface
private:
    bool runImpl() override;
    void cancelImpl() override;
};

inline std::shared_ptr<TaskAdapter> createTaskAdapter(core::RtTaskSharedPtr task) {
    return std::make_shared<TaskAdapter>(std::move(task), nullptr);
}
