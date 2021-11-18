#pragma once

namespace core {

// Математические ограничения оси
class axis_limits {
public:
    axis_limits() = default;
    // Конструктор
    axis_limits(double low, double high) noexcept
        : low_{low}, high_{high} {
    }
    // Установить значения ограничений
    void set_values(double  low, double  high) noexcept {
        low_ = low;
        high_ = high;
    }
    // Применить ограничения
    auto clamp(double pos) const noexcept {
        if(pos < low_) return low_;
        if(pos > high_) return high_;
        return pos;
    }
    // Нижнее ограничение координаты
    auto low() const noexcept {
        return low_;
    }
    // Верхнее ограничение
    auto high() const noexcept {
        return high_;
    }
private:
    // Нижнее ограничение
    double low_ = -10.0;
    // Верхнее ограничение
    double high_ = 100.0;

};

}