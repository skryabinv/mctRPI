//
// Created by VLADIMIR on 08.09.2021.
//

#ifndef MOTIONPI_DELAY_H
#define MOTIONPI_DELAY_H

#include <functional>

namespace core {
namespace delay {

using task_t = std::function<bool()>;

// Создать задачу калибровки таймер
// для выполнения в потоке задач
task_t create_calibration_task(bool value_to_return = true);

// Задержка простым циклом ожидания
void busy_loop(uint32_t us);

// Вспомогательный-callable класс, инициализируемый
// значением busy-задержки в мкс
class proxy_delay {
public:
    template<typename DelayType>
    explicit proxy_delay(DelayType us) noexcept
        : us_(us) {}
    void operator()() const noexcept { busy_loop(us_); }
private:
    const uint32_t us_;
};

}
}

#endif //MOTIONPI_DELAY_H
