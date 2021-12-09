#pragma once

#include <cstdint>
#include <atomic>
#include "GPIO.h"
#include "RtTaskGeneric.h"

namespace core {

class OuputPort
{
    static constexpr int InvalidPin = 0xFF;
public:
    explicit OuputPort(uint32_t pin = InvalidPin)
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
        return makeSharedGenericTask([port{getPort()}](RtTask&) { port.set(); });
    }

//    RtTaskSharedPtr createTaskPortClear() {
//        return makeSharedGenericTask([port{getPort()}](RtTask&) { port.clr(); });
//    }

private:
    uint32_t mPin;    
};

}

