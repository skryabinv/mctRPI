#pragma once

#include <array>

namespace core {

// Класс для перекодирования одной последовательности
// заданной битовой маской в другую по некоторой таблице соответствия
// с индексами, соответствующих битов
// left_[0] ~ right_[0]  
// ...
// left_[n - 1] ~ right[n - 1]
// Параметр шаблонна n - размер таблицы перекодировки
template <size_t n>
class bits_decoder {
    static_assert(n <= 32 && n > 0);
public:
    template <typename It1, typename It2>
    bits_decoder(It1 left_first, It1 left_last, It2 right_first) {                
        assert(left_last - left_first <= n);
        auto it1 = left_first;
        auto it2 = right_first;
        size_t counter{0};
        while (it1 != left_last) {
            left_[counter] = *it1;
            right_[counter] = *it2;
            ++it1;
            ++it2;
            ++counter;
        }
        
    }    
    uint32_t decode_right_to_left(uint32_t bits) const noexcept {
        return decode_impl<n - 1>(right_, left_, bits);
    }    
    uint32_t decode_left_to_right(uint32_t bits) const noexcept {
        return decode_impl<n - 1>(left_, right_, bits);
    }
private:    
    template <int m, typename ArrayType>
    static uint32_t decode_impl(const ArrayType& left, 
                                const ArrayType& right, 
                                uint32_t bits) noexcept {        
        if constexpr (m < 0) return 0;        
        else {                        
            return  (((bits >> left[m]) & 1) << right[m]) | decode_impl<m - 1>(left, right, bits);        
        }
    }
    // Правая часть таблицы соответствия
    std::array<uint32_t, n> left_{};
    // Левая часть таблицы соответствия
    std::array<uint32_t, n> right_{};
};

}
