#pragma once

#include <cstdint>

namespace core {

// Настройки движения по оси
class axis_speed_settings {
public:
    axis_speed_settings() = default;
    // Конструктор
    // speed - скорость (мм / мин)
    // acc - ускорение (мм / сек / сек)
    // dec - замедление (мм / сек / сек)
    axis_speed_settings(double speed,
        double acc,
        double dec) noexcept:
        speed_{speed}, acc_{acc}, dec_{dec} {}
    // Установить скорость и ускорения
    void set_values(double speed_mm_per_min,
                    double acc_mm_per_sec2,
                    double dec_mm_per_sec2) noexcept {
        speed_ = speed_mm_per_min;
        acc_ = acc_mm_per_sec2;
        dec_ = dec_mm_per_sec2;
    }
    // Установить скорость и ускорения временем набора значения
    void set_speed_time(double  speed_mm_per_min,
                        double target_time_acc_ms,
                        double target_time_dec_ms) noexcept {
        speed_ = speed_mm_per_min;
        acc_ = (1000.0 / 60.0) * speed_mm_per_min / target_time_acc_ms;
        dec_ = (1000.0 / 60.0) * speed_mm_per_min / target_time_dec_ms;
    }
    // Ограничение скорости
    auto limit_speed(double speed_mm_per_sec) const noexcept {
        if(std::abs(speed_mm_per_sec) > speed_) {
            return speed_mm_per_sec < 0 ? -speed_ : speed_;
        }
        return speed_mm_per_sec;
    }
    // Время до набора целевой скорости
    double get_speed_time_acc_ms() const noexcept {
        return speed_ / 60.0 / acc_ / 1000.0;
    }
    // Время до остановки от целевой скорости
    double get_speed_time_dec_ms() const noexcept {
        return speed_ / 60.0 / dec_ / 1000.0;
    }
    auto speed_mm_per_min() const noexcept {
        return speed_;
    }
    auto speed_mm_per_sec() const noexcept {
        return speed_ / 60.0;
    }
    auto acc_mm_per_sec2() const noexcept {
        return acc_;
    }
    auto dec_mm_per_sec2() const noexcept {
        return dec_;
    }
    auto speed_home_fwd() const noexcept {
        return speed_home_fwd_;
    }
    auto speed_home_back() const noexcept {
        return speed_home_back_;
    }
private:
    // Скорость мм/мин
    double speed_ = 1500.0;
    // Ускорение мм/сек/сек
    double acc_ = 100.0;
    // Замедление мм/сек/сек
    double dec_ = 100.0;
    // Прямая скорость поиска концевика
    double speed_home_fwd_ = 100.0;
    // Обратная скорость поиска концевика
    double speed_home_back_ = 10.0;
};

}