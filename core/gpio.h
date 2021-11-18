#pragma once

#include <cstdint>
#include <initializer_list>
#include <algorithm>
#include <cassert>

namespace core::gpio {

// Инициализировать систему портов ввода-вывода
bool initialize();

namespace pins {
// Соответствие пинов по подключению пинам в регистре
enum : uint32_t {
    P3 = 2, P5 = 3, P7 = 4, P8 = 14,
    P10 = 15, P11 = 17, P12 = 18, P13 = 27,
    P15 = 22, P16 = 23, P18 = 24, P19 = 10,
    P21 = 9,  P22 = 25, P23 = 11, P24 = 8,
    P26 = 7,  P27 = 0,  P28 = 1,  P29 = 5,
    P31 = 6,  P32 = 12, P33 = 13, P35 = 19,
    P36 = 16, P37 = 26, P38 = 20, P40 = 21,
};
}

// Смещение регистра установки
constexpr uint32_t ADR_SET0 = 0x1C;

// Смещение регистра очистки
constexpr uint32_t ADR_CLR0 = 0x28;

// Смещения регистра уровня
constexpr uint32_t ADR_LEV0 = 0x34;

// Указатель на область виртуальной памяти соответствующая регистрам gpio
extern volatile uint32_t * gpio_base;

// Порт для чтения
class port32_in {
public:
    template<typename It>
    port32_in(It begin, It end) noexcept {
        std::for_each(begin, end, [this](uint32_t pin) {
            mask_ |= 1 << pin;
            init(pin);
        });
    }
    uint32_t read() const noexcept {
        return read_impl(mask_);
    }
    uint32_t read(uint32_t mask) const noexcept {
        return read_impl(mask_ & mask);
    }
private:
    inline static void init(uint32_t pin) noexcept {
        *(gpio_base +  pin / 10) &= ~(7 << (3 * (pin % 10)));
    }
    inline static uint32_t read_impl(uint32_t mask) noexcept {
        __sync_synchronize();
        return *(gpio_base + (ADR_LEV0 >> 2)) & mask;
    }
    uint32_t mask_{0};

};

// Порт для вывода
// Может соответсвовать нескольким портам,
// определяемым маской регистра
class port32_out {
public:
    // Конструктор
    template<typename It>
    port32_out(It begin, It end) noexcept {
        std::for_each(begin, end, [this](uint32_t pin){
            mask_ |= (1 << pin);
            init(pin);
        });

    }
    // Установить значение порта в 1
    void set() const noexcept {
        set_impl(mask_);
    }
    // Установить значения порта в 0
    void clr() const noexcept {
        clr_impl(mask_);
    }
    // Установить с применение дополнительной маски
    void set(uint32_t mask) const noexcept {
        set_impl(mask & mask_);
    }
    // Очистить с применение дополнительной маски
    void clr(uint32_t mask) const noexcept {
        clr_impl(mask & mask_);
    }
private:
    inline static void set_impl(uint32_t mask) noexcept {
        __sync_synchronize();
        *(gpio_base + (ADR_SET0 / 4)) = mask;
    }
    inline static void clr_impl(uint32_t mask) noexcept {
        __sync_synchronize();
        *(gpio_base + (ADR_CLR0 / 4)) = mask;
    }
    inline static void init(uint32_t pin) noexcept {
        *(gpio_base +  pin / 10) &= ~(7 << (3 * (pin % 10)));
        *(gpio_base +  pin / 10) |= 1 << (3 * (pin % 10));
    }
    // Маска соответствующая портам вывода
    uint32_t mask_{0u};
};

}
