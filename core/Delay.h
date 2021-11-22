#pragma once

#include <cstdint>
#include <functional>
#include "RtTask.h"

namespace core {
namespace delay {

// Создать задачу калибровки таймер
// для выполнения в потоке задач
RtTaskSharedPtr createCalibrationTask(bool value_to_return = true);

// Задержка простым циклом ожидания
void busyLoop(uint32_t us);

// Вспомогательный-callable класс, инициализируемый
// значением busy-задержки в мкс
class ProxyDelay {
public:
    template<typename DelayType>
    explicit ProxyDelay(DelayType us) noexcept
        : mUs(us) {}
    void operator()() const noexcept { busyLoop(mUs); }
private:
    const uint32_t mUs;
};

}
} // namespace core


