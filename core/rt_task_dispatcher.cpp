#include "rt_task_dispatcher.h"
#include <pthread.h>
#include <sched.h>
#include <iostream>

// Сконфигурировать вызывающий поток как реал-тайм
static bool configure_realtime(pthread_t thread_id) {
    sched_param sch = {1};
    if (pthread_setschedparam(thread_id, SCHED_FIFO, &sch)) {
        return false;
    }
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(3, &cpu_set);
    if (pthread_setaffinity_np(thread_id, sizeof(cpu_set), &cpu_set)) {
        return false;
    }
    return true;
}

using namespace std::literals::chrono_literals;

namespace core {

rt_task_dispatcher::rt_task_dispatcher() {
    // Огранииваем частоту ядра минимальной частотой
     system("sudo echo -1 >/proc/sys/kernel/sched_rt_runtime_us");
     system("sudo cp /sys/devices/system/cpu/cpu3/cpufreq/scaling_min_freq "
            "/sys/devices/system/cpu/cpu3/cpufreq/scaling_max_freq");
}

rt_task_dispatcher::~rt_task_dispatcher() {
    thread_.wait();
    // Снимаем ограничение на частоту ядра
     system("sudo cp /sys/devices/system/cpu/cpu3/cpufreq/cpuinfo_max_freq "
            "/sys/devices/system/cpu/cpu3/cpufreq/scaling_max_freq");
}

void rt_task_dispatcher::schedule_task(task_t task) {
    {
        std::lock_guard<std::mutex> lock{mutex_};
        queue_.push(std::move(task));
    }
    cond_.notify_one();
}

bool rt_task_dispatcher::exec() {
    enum class status_t { init, done, error };
    std::atomic<status_t> status{status_t::init};
    thread_ = std::async(std::launch::async, [this, &status](){
        if(!configure_realtime(pthread_self())) {
            std::cout << "Can't setup realtime thread" << std::endl;
            status = status_t::error;
        } else {
            status = status_t::done;
            exec_impl();
        }
    });
    // Ждем пока инициализируется поток обработки
    while (status == status_t::init) {
        std::this_thread::sleep_for(10ms);
    }
    return status == status_t::done;
}

void rt_task_dispatcher::wait() {
    thread_.wait();
}

void rt_task_dispatcher::exec_impl() {
    std::unique_lock<std::mutex> lock{mutex_};
    while(true) {                
        cond_.wait_for(lock, 100ms);
        if(queue_.empty()) continue;        
        auto task = std::move(queue_.front());
        queue_.pop();
        lock.unlock();
        if(!task()) break;
        lock.lock();
    }
}

void rt_task_dispatcher::wait_for_task(task_t task) {
    std::atomic_bool done{false};
    task_t func = [task{std::move(task)}, &done](){
        try {
            auto result = task();
            done = true;
            return result;
        } catch (std::exception&) {
            done = true;
            throw;
        }
    };
    schedule_task(std::move(func));
    while (!done) {
        std::this_thread::sleep_for(10ms);
    }
}

void rt_task_dispatcher::schedule_end_task() {
    schedule_task([]{ return false; });
}

}
