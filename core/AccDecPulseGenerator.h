#pragma once

#include <cassert>
#include <cmath>
#include <iostream>

namespace core {

// Генератор длительностей импульсов для заданных параметров движения
// Выступает как итератор:
// Далее по запросу выдает длительности следующего интервала
// в микросекундах
class AccDecPulseGenerator {
public:
    // Инициализация по параметрам движения
    AccDecPulseGenerator(double total_dist,    // целевое перемещение (мм)
                         double dist_per_pulse, // перемещение на имульс (мм)
                         double speed,          // скорость (мм/s)
                         double acc,            // ускорение (мм/сек/сек)
                         double dec             // замедление (мм/сек/сек)
                         ) {
        assert(dist_per_pulse > 0.0);
        assert(total_dist > 0.0);
        assert(speed > 0.0);
        assert(acc > 0.0);
        assert(dec > 0.0);
        pulses_ = total_dist / dist_per_pulse;
        acc_ = acc;
        dec_ = dec;
        speed_ = speed;
        dist_per_pulse_ = dist_per_pulse;
        acc_scale_ = std::sqrt(2.0 * dist_per_pulse / acc_);
        dec_scale_ = std::sqrt(2.0 * dist_per_pulse / dec_);
        target_delay_ = dist_per_pulse_ / speed_;
        calc_stops();
    }
    // Todo: Рассмотреть блок ускорения замедления без ограничения
    AccDecPulseGenerator(double dist_per_pulse, double speed, double acc) {
        assert(dist_per_pulse > 0.0);
        assert(speed > 0.0);
        assert(acc > 0.0);
        pulses_ = std::numeric_limits<uint32_t>::max(); // Ставим максимально возможное число импульсов
        acc_ = acc;
        dec_ = acc; // Переписать класс
        speed_ = speed;
        dist_per_pulse_ = dist_per_pulse;
        acc_scale_ = std::sqrt(2.0 * dist_per_pulse / acc_);
        dec_scale_ = std::sqrt(2.0 * dist_per_pulse / dec_);
        target_delay_ = dist_per_pulse_ / speed_;
        calc_stops();
    }
    operator bool() const noexcept {
        return pulse_counter_ < pulses_;
    }
    // Переход к следующему импульсу
    AccDecPulseGenerator& operator++() noexcept {
        ++pulse_counter_;
        current_delay_ = get_delay();
        return *this;
    }
    // Длительность следующего импульса в микросекундах
    template<typename DelayType = double, uint32_t divider = 1>
    DelayType getDelayFuncUs() const noexcept {
        return DelayType(1.e6 * (current_delay_ / divider));
    }
    // Длительность следующего импульса в микросекундах
    double operator*() const noexcept {
        return getDelayFuncUs();
    }
private:
    // Вычислить длительность для следующего шага
    double get_delay() const noexcept {
        if(pulse_counter_ < stop1_) return get_delay_acc_mode();
        if(pulse_counter_ > stop2_) return get_delay_dec_mode();
        return get_delay_run_mode();
    }
    // Функция расчета длительности в режиме ускорения
    double get_delay_acc_mode() const noexcept {
        return acc_scale_ * (std::sqrt(pulse_counter_) - std::sqrt(pulse_counter_ - 1));
    }
    // Функция расчета длительности в нормальном режиме
    double get_delay_run_mode() const noexcept {
        return target_delay_;
    }
    // Функция расчета длительности в режиме замедления
    double get_delay_dec_mode() const noexcept {
        return dec_scale_ * (std::sqrt(pulses_ - pulse_counter_ + 1) - std::sqrt(pulses_ - pulse_counter_));
    }
    // Расчитать стоповые интервалы
    void calc_stops() noexcept {
        double s1 = 0.5 * speed_ * speed_ / acc_ / dist_per_pulse_;
        double s2 = 0.5 * speed_ * speed_ / dec_ / dist_per_pulse_;
        std::cout << __FUNCTION__ << " " << s1 << " " << s2 << std::endl;
        if(s1 + s2 >= pulses_) {
            // Скорость не будет достигнута с заданными параметрами
            stop1_ = static_cast<uint32_t>(dec_ * pulses_ / (dec_ + acc_));
            stop2_ = pulses_ - stop1_;
        } else {
            // Скорость будет достигнута
            stop1_ = static_cast<uint32_t>(s1);
            stop2_ = pulses_ - static_cast<uint32_t>(s2);
        }
        std::cout << __FUNCTION__ << " : " << stop1_ << " " << stop2_ << std::endl;
    }
    // Счетчик импульсов
    uint32_t pulse_counter_{0};
    // Общее количество импульсов
    uint32_t pulses_;
    // Расстояние за шаг (мм)
    double dist_per_pulse_;
    // Ускорении мм/сек/сек
    double acc_{0.0};
    // Замедление мм/сек/сек
    double dec_{0.0};
    // Скорость мм/сек
    double speed_{0.0};
    // Множитель для расчета интервала в режиме ускорения
    double acc_scale_;
    // Множитель для расчета интервала в режиме замедления
    double dec_scale_;
    // Текущее значение задержки в секундах
    double current_delay_{0.0};
    // Целевая задержка между импульсами в секундах
    double target_delay_{0.0};
    // Точка окончания ускорения в шагах
    uint32_t stop1_;
    // Точка начала замедления в шагах
    uint32_t stop2_;
};

}
