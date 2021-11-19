#pragma once

#include <future>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

namespace core {

// Диспетчер задач, которые должны выполняться в "реальном-времени"
// Запускается в отдельном потоке, на отдельном изолированном ядре
// Как оповестить об ошибке ?
class RtTaskDispatcher {
public:
    // Запланированное действие
    using task_t = std::function<bool()>;
    RtTaskDispatcher();
    ~RtTaskDispatcher();
    // Добавить задачу в очередь задач
    void scheduleTask(task_t task);
    // Запустить поток исполнения задач
    bool exec();
    // Блокировать вызывающий поток, пока цикл не завершиться
    void wait();
    // Спланировать задачу и ждать ее завершения
    void waitForTask(task_t task);
    // Закончить работу
    void scheduleEndTask();
private:
    // Непосредственно цикл обработки задач
    void execImpl();
    // Очередь для хранения задач
    std::queue<task_t> mQueue;
    // Условная переменная для оповещения
    std::condition_variable mCondition;
    // Мьютекс очереди задач
    std::mutex mMutex;
    // Фьючер цикла обработки комманд
    std::future<void> mThread;
};

} // namespace core

