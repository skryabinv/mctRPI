#pragma once

#include <array>
#include <cstdint>

namespace core {

// Класс для перекодирования одной последовательности
// заданной битовой маской в другую по некоторой таблице соответствия
// с индексами, соответствующих битов
// left_[0] ~ right_[0]
// ...
// left_[n - 1] ~ right[n - 1]
// Параметр шаблонна n - размер таблицы перекодировки
template <size_t n>
class BitsDecoder {
    static_assert(n <= 32 && n > 0);
public:
    template <typename It1, typename It2>
    BitsDecoder(It1 left_first, It1 left_last, It2 right_first) {
        assert(left_last - left_first <= n);
        auto it1 = left_first;
        auto it2 = right_first;
        size_t counter{0};
        while (it1 != left_last) {
            mLeft[counter] = *it1;
            mRight[counter] = *it2;
            ++it1;
            ++it2;
            ++counter;
        }

    }
    uint32_t decodeRightToLeft(uint32_t bits) const noexcept {
        return decodeImpl<n - 1>(mRight, mLeft, bits);
    }
    uint32_t decodeLeftToRight(uint32_t bits) const noexcept {
        return decodeImpl<n - 1>(mLeft, mRight, bits);
    }
private:
    template <int m, typename ArrayType>
    static uint32_t decodeImpl(const ArrayType& left,
                                const ArrayType& right,
                                uint32_t bits) noexcept {
        if constexpr (m < 0) return 0;
        else {
            return  (((bits >> left[m]) & 1) << right[m]) | decodeImpl<m - 1>(left, right, bits);
        }
    }
    // Правая часть таблицы соответствия
    std::array<uint32_t, n> mLeft{};
    // Левая часть таблицы соответствия
    std::array<uint32_t, n> mRight{};
};

}
