#pragma once

#include <cstdint>
#include <stdexcept>
#include "GPIO.h"
#include "RtTaskGeneric.h"

namespace core {

class OutputPort
{
    static constexpr int InvalidPin = 0xFF;
public:
    explicit OutputPort(uint32_t pin = InvalidPin)
        : mPin{pin} {}

    bool isValid() const noexcept {
        return mPin != InvalidPin;
    }

    void setPin(uint32_t pin) noexcept {
        mPin = pin;
    }

    uint32_t getPin() const noexcept {
        return mPin;
    }

    auto getPort() const {
        if(isValid()) {
            auto ports = { mPin };
            return gpio::PortOut { ports.begin(), ports.end() };
        } else {
            throw std::logic_error("Pin value is not valid");
        }
    }

private:
    uint32_t mPin;    
};

}

