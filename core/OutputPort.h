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
        auto ports = { mPin };
        return gpio::PortOut { ports.begin(), ports.end() };
    }

    RtTaskSharedPtr createTaskPortSet() {
        if(!isValid()) {
            throw std::logic_error("External output port should initialized first!");
        }
        return makeSharedGenericTask([port{getPort()}](auto&) {
            port.set();
            return true;
        });
    }

    RtTaskSharedPtr createTaskPortClear() {
        if(!isValid()) {
            throw std::logic_error("External output port should initialized first!");
        }
        return makeSharedGenericTask([port{getPort()}](auto&) {
            port.clr();
            return true;
        });
    }

private:
    uint32_t mPin;    
};

}

