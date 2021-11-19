#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include "GPIO.h"
#include "BitsDecoder.h"

namespace core {

// Порты оси
class AxisPorts {
public:
    AxisPorts() = default;
    // Установить порты оси
    void setPorts(std::vector<uint32_t> in,
                  std::vector<uint32_t> step,
                  std::vector<uint32_t> dir) {
        mPortsHome = std::move(in);
        mPortsStep = std::move(step);
        mPortsDir = std::move(dir);
    }
    // Загрузить номера портов из строк, содержащих
    // разделенные запятыми номера портов
    void setPortsFromStr(std::string in, std::string step, std::string dir) {
        setPorts(fromStr(std::move(in)),
                 fromStr(std::move(step)),
                 fromStr(std::move(dir)));
    }

    void setPortsHome(std::vector<uint32_t> ports) noexcept {
        mPortsHome = std::move(ports);
    }

    void setPortsDir(std::vector<uint32_t> ports) noexcept {
        mPortsDir = std::move(ports);
    }

    void setPortsStep(std::vector<uint32_t> ports) noexcept {
        mPortsStep = std::move(ports);
    }

    // Декодер позволяет маскировать? порты
    template <size_t n>
    BitsDecoder<n> getInToStepDecoder() const noexcept {
        return BitsDecoder<n>{
            mPortsHome.cbegin(), mPortsHome.cend(),
            mPortsStep.cbegin()
        };
    }
    template <size_t n>
    BitsDecoder<n> getInToDirDecoder() const noexcept {
        return BitsDecoder<n>{
            mPortsHome.cbegin(), mPortsHome.cend(),
            mPortsDir.cbegin()
        };
    }
    // Создать объект портов концевика
    auto getPortHome() const noexcept {
        return gpio::PortIn{
            mPortsHome.cbegin(),
            mPortsHome.cend()
        };
    }
    // Создать объект портов STEP
    auto getPortStep() const noexcept {
        return gpio::PortOut{
            mPortsStep.cbegin(),
            mPortsStep.cend()
        };
    }
    // Создать объект портов направления
    auto getPortDir() const noexcept {
        return gpio::PortOut{
            mPortsDir.cbegin(),
            mPortsDir.cend()
        };
    }
    const auto& getPortsHome() const noexcept {
        return mPortsHome;
    }
    const auto& getPortsStep() const noexcept {
        return mPortsStep;
    }
    const auto& getPortsDir() const noexcept {
        return mPortsDir;
    }
    std::string portsHomeToStr() const {
        return toStr(mPortsHome);
    }
    std::string portStepToStr() const {
        return toStr(mPortsStep);
    }
    std::string portsDirStepToStr() const {
        return toStr(mPortsDir);
    }
private:
    static std::vector<uint32_t> fromStr(std::string str) {
        std::vector<uint32_t> result;
        std::stringstream ss{str};
        std::copy(std::istream_iterator<uint32_t>{ss},
                  std::istream_iterator<uint32_t>{},
                  std::back_inserter(result));
        return result;
    }
    static std::string toStr(const std::vector<uint32_t>& ports) {
        std::stringstream ss;
        std::copy(ports.cbegin(), ports.cend(),
            std::ostream_iterator<uint32_t>{ss, " "});
        return ss.str();
    }
    std::vector<uint32_t> mPortsHome = { gpio::pins::P12, gpio::pins::P13  };
    std::vector<uint32_t> mPortsStep = { gpio::pins::P3, gpio::pins::P7 };
    std::vector<uint32_t> mPortsDir =  { gpio::pins::P5, gpio::pins::P8 };
};

}
