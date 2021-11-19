#pragma once

#include <cstdint>

namespace core {

// Коэфициент передачи оси (шаги на мм)
class AxisGearRatio {
public:
    AxisGearRatio() = default;
    AxisGearRatio(uint32_t steps, uint32_t dist)
        : mSteps{steps}, mDistMm{dist} {}
    // Установить значения
    void setValues(uint32_t steps, uint32_t dist) noexcept {
        mSteps = steps;
        mDistMm = dist;
    }
    void setSteps(double value) noexcept {
        mSteps = value;
    }
    void setDist(double value) noexcept {
        mDistMm = value;
    }

    // Количество шагов
    auto getSteps() const noexcept {
        return mSteps;
    }
    // Расстояние
    auto getDist() const noexcept {
        return mDistMm;
    }
    // Шагов на мм
    auto getStepsPerMm() const noexcept {
        return static_cast<double>(getSteps()) / getDist();
    }
    // Мм на шаг
    auto getMmsPerStep() const noexcept {
        return 1.0 / getStepsPerMm();
    }
private:
    // Количество импульсов
    uint32_t mSteps = 1600;
    // Соответствующее расстояние (мм)
    uint32_t mDistMm = 1.0;
};


}
