#pragma once

#include <cmath>

namespace core {

// Математические ограничения оси
class AxisLimits {
public:
    AxisLimits() = default;
    // Конструктор
    constexpr AxisLimits(double low, double high) noexcept
        : mLow{low}, mHigh{high} {
    }    
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
    auto clamp(double pos) const noexcept {
        if(pos < mLow) return mLow;
        if(pos > mHigh) return mHigh;
        return pos;
    }

    double clamp(double currentPos, double dist, double speed) {
        return clamp(currentPos + (speed > 0 ? dist : -dist));
    }

    double clampDistance(double currentPos, double dist, double speed) {
        return std::abs(currentPos - clamp(currentPos, dist, speed));
    }

    // Max distance to move with specified speed
    double getMaxDist(double currentPos, double speed) {
        if(speed < 0) return currentPos - mLow;
        if(speed > 0) return mHigh - currentPos;
        return 0.0;
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
