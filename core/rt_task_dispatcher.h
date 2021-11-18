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
class rt_task_dispatcher {
public:
    // Запланированное действие
    using task_t = std::function<bool()>;
    rt_task_dispatcher();
    ~rt_task_dispatcher();
    // Добавить задачу в очередь задач
    void schedule_task(task_t task);
    // Запустить поток исполнения задач
    bool exec();
    // Блокировать вызывающий поток, пока цикл не завершиться 
    void wait();
    // Спланировать задачу и ждать ее завершения
    void wait_for_task(task_t task);
    // Закончить работу
    void schedule_end_task();
private:
    // Непосредственно цикл обработки задач
    void exec_impl();
    // Очередь для хранения задач
    std::queue<task_t> queue_;
    // Условная переменная для оповещения
    std::condition_variable cond_;
    // Мьютекс очереди задач
    std::mutex mutex_;
    // Фьючер цикла обработки комманд
    std::future<void> thread_;
};

}