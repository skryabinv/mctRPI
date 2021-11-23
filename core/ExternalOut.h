#pragma once

#include <cstdint>
#include <atomic>

namespace core {

class ExternalOut
{
public:
    ExternalOut(uint32_t pin)
        : mPin{pin} {
    }
    void setPin(uint32_t pin) { mPin = pin; }
    uint32_t getPin() const { return mPin; }
    bool isHigh() const noexcept { return mLevel; }
    bool isLow() const noexcept { return !mLevel; }        
private:
    uint32_t mPin;
    std::atomic_bool mLevel{false};
};

}

