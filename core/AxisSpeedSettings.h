#pragma once

#include <cmath>

namespace core {

enum class SpeedUnits {
    MM_PER_MIN,
    MM_PER_SEC
};

// Настройки движения по оси
class AxisSpeedSettings {
public:

    AxisSpeedSettings() = default;

    // Конструктор
    // speed - скорость (мм / мин)
    // acc - ускорение (мм / сек / сек)
    // dec - замедление (мм / сек / сек)
    AxisSpeedSettings(double speed,
                      double acc,
                      double dec,
                      double speedHomeFwd,
                      double speedHomeBack) noexcept:
        mSpeed{speed},
        mAcc{acc},
        mDec{dec},
        mSpeedHomeFwd{speedHomeFwd},
        mSpeedHomeBack{speedHomeBack}
    {}

    // Установить скорость и ускорения
    void setValues(double speed_mm_per_min,
                    double acc_mm_per_sec2,
                    double dec_mm_per_sec2) noexcept {
        mSpeed = speed_mm_per_min;
        mAcc = acc_mm_per_sec2;
        mDec = dec_mm_per_sec2;
    }

    // Установить скорость и ускорения временем набора значения
    void setSpeedAndTime(double  speed_mm_per_min,
                        double target_time_acc_ms,
                        double target_time_dec_ms) noexcept {
        mSpeed = speed_mm_per_min;
        mAcc = (1000.0 / 60.0) * speed_mm_per_min / target_time_acc_ms;
        mDec = (1000.0 / 60.0) * speed_mm_per_min / target_time_dec_ms;
    }

    // Ограничение скорости
    auto limitSpeed(double speed_mm_per_sec) const noexcept {
        if(std::abs(speed_mm_per_sec) > mSpeed) {
            return speed_mm_per_sec < 0 ? -mSpeed : mSpeed;
        }
        return speed_mm_per_sec;
    }

    // Время до набора целевой скорости
    double getSpeedTimeAcc() const noexcept {
        return 1000.0 * mSpeed / 60.0 / mAcc;
    }

    // Время до остановки от целевой скорости
    double getSpeedTimeDec() const noexcept {
        return 1000.0 * mSpeed / 60.0 / mDec;
    }

    auto getAcceleration() const noexcept {
        return mAcc;
    }
    auto getDeceleration() const noexcept {
        return mDec;
    }

    void setSpeed(double value) noexcept {
        setSpeedAndTime(value,
                        getSpeedTimeAcc(),
                        getSpeedTimeDec());
    }

    void setSpeedNomeBack(double value) noexcept {
        mSpeedHomeBack = value;
    }

    void setSpeedHomeFwd(double value) noexcept {
        mSpeedHomeFwd = value;
    }

    void setSpeedTime(double value) {
        setSpeedAndTime(mSpeed,
                        value,
                        value);
    }

    template<SpeedUnits unit>
    auto getSpeed() const noexcept {
        return selectSpeedUnits<unit>(mSpeed);
    }

    template<SpeedUnits unit>
    auto getSpeedHomeFwd() const noexcept {
        return selectSpeedUnits<unit>(mSpeedHomeFwd);
    }

    template<SpeedUnits unit>
    auto getSpeedHomeBack() const noexcept {
        return selectSpeedUnits<unit>(mSpeedHomeBack);
    }

private:

    template<SpeedUnits unit>
    static double selectSpeedUnits(double value) {
        if constexpr (unit == SpeedUnits::MM_PER_MIN) {
            return value;
        } else {
            return value / 60.0;
        }
    }

    // Скорость мм/мин
    double mSpeed = 1500.0;
    // Ускорение мм/сек/сек
    double mAcc = 100.0;
    // Замедление мм/сек/сек
    double mDec = 100.0;
    // Прямая скорость поиска концевика, мм/мин
    double mSpeedHomeFwd = 100.0;
    // Обратная скорость поиска концевика, мм/мин
    double mSpeedHomeBack = 10.0;
};

}
