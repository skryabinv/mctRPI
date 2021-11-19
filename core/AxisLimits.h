#pragma once

namespace core {

// Математические ограничения оси
class AxisLimits {
public:
    AxisLimits() = default;
    // Конструктор
    constexpr AxisLimits(double low, double high) noexcept
        : mLow{low}, mHigh{high} {
    }
    // Установить значения ограничений
    void setValue(double  low, double  high) noexcept {
        mLow = low;
        mHigh = high;
    }
    void setLow(double value) noexcept {
        mLow = value;
    }
    void setHigh(double value) noexcept {
        mHigh = value;
    }
    // Применить ограничения
    auto clamp(double pos) const noexcept {
        if(pos < mLow) return mLow;
        if(pos > mHigh) return mHigh;
        return pos;
    }
    // Нижнее ограничение координаты
    auto getLow() const noexcept {
        return mLow;
    }
    // Верхнее ограничение
    auto getHigh() const noexcept {
        return mHigh;
    }
    // Расстояние
    auto getExtent() const noexcept {
        return mHigh - mLow;
    }
private:
    // Нижнее ограничение
    double mLow = -10.0;
    // Верхнее ограничение
    double mHigh = 100.0;

};

}
