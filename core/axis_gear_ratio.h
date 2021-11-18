#pragma once

namespace core {

// Коэфициент передачи оси (шаги на мм)
class axis_gear_ratio {
public:
    axis_gear_ratio() = default;
    axis_gear_ratio(uint32_t steps, uint32_t dist) 
        : steps_{steps}, dist_{dist} {}
    // Установить значения
    void set_values(uint32_t steps, uint32_t dist) noexcept {
        steps_ = steps;
        dist_ = dist;
    }
    // Количество шагов
    auto steps() const noexcept {
        return steps_;
    }    
    // Расстояние
    auto dist() const noexcept {
        return dist_;
    }
    // Шагов на мм
    auto steps_per_mm() const noexcept {
        return static_cast<double>(steps()) / dist();
    }
    // Мм на шаг
    auto mm_per_step() const noexcept {
        return 1.0 / steps_per_mm();
    }
private:
    // Количество импульсов
    uint32_t steps_ = 1600;
    // Соответствующее расстояние
    uint32_t dist_ = 1.0;
};


}