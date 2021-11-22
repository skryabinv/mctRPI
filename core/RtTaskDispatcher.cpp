#include "RtTaskDispatcher.h"
#include "RtTaskGeneric.h"
#include <pthread.h>
#include <sched.h>
#include <iostream>
#include <thread>

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

RtTaskDispatcher::RtTaskDispatcher() {
    // Огранииваем частоту ядра минимальной частотой
     system("sudo echo -1 >/proc/sys/kernel/sched_rt_runtime_us");
     system("sudo cp /sys/devices/system/cpu/cpu3/cpufreq/scaling_min_freq "
            "/sys/devices/system/cpu/cpu3/cpufreq/scaling_max_freq");
}

RtTaskDispatcher::~RtTaskDispatcher() {
    mThread.wait();
    // Снимаем ограничение на частоту ядра
     system("sudo cp /sys/devices/system/cpu/cpu3/cpufreq/cpuinfo_max_freq "
            "/sys/devices/system/cpu/cpu3/cpufreq/scaling_max_freq");
}

void RtTaskDispatcher::scheduleTask(RtTaskSharedPtr task) {
    {
        std::lock_guard<std::mutex> lock{mMutex};
        mQueue.push(std::move(task));
    }
    mCondition.notify_one();
}

bool RtTaskDispatcher::exec() {
    enum class status_t { init, done, error };
    std::atomic<status_t> status{status_t::init};
    mThread = std::async(std::launch::async, [this, &status](){
        if(!configure_realtime(pthread_self())) {
            std::cout << "Can't setup realtime thread" << std::endl;
            status = status_t::error;
        } else {
            status = status_t::done;
            execImpl();
        }
    });
    // Ждем пока инициализируется поток обработки
    while (status == status_t::init) {
        std::this_thread::sleep_for(10ms);
    }
    return status == status_t::done;
}

void RtTaskDispatcher::wait() {
    mThread.wait();
}

void RtTaskDispatcher::execImpl() {
    std::unique_lock<std::mutex> lock{mMutex};
    while(true) {
        mCondition.wait_for(lock, 100ms);
        if(mQueue.empty()) continue;
        auto task = std::move(mQueue.front());
        mQueue.pop();
        lock.unlock();
        if(!task->run()) break;
        lock.lock();
    }
}

void RtTaskDispatcher::waitForTask(RtTaskSharedPtr task) {
    std::atomic_bool done{false};
    auto func = makeSharedGenericTask(
            [task{std::move(task)}, &done](auto&){
        try {
            auto result = task->run();
            done = true;
            return result;
        } catch (std::exception&) {
            done = true;
            throw;
        }
    }
    );
    scheduleTask(std::move(func));
    while (!done) {
        std::this_thread::sleep_for(10ms);
    }
}

void RtTaskDispatcher::scheduleEndTask() {
    scheduleTask(makeSharedGenericTask([](auto&){
        std::cout << "EndTask" << std::endl;
        return false;
    }));
}

RtTaskDispatcher &RtTaskDispatcher::getInstance()
{
    static RtTaskDispatcher instance;
    return instance;
}

} // namespace core
