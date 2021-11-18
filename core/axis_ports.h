#pragma once

#include <vector>
#include <string>
#include "gpio.h"
#include "bits_decoder.h"
#include <algorithm>
#include <iterator>
#include <sstream>

namespace core {

// Порты оси
class axis_ports {
public:
    axis_ports() = default;
    // Установить порты оси
    void set_ports(std::vector<uint32_t> in,
                   std::vector<uint32_t> step,
                   std::vector<uint32_t> dir) {
        ports_in_ = std::move(in);
        ports_step_ = std::move(step);
        ports_dir_ = std::move(dir);
    }
    // Загрузить номера портов из строк, содержащих
    // разделенные запятыми номера портов
    void set_ports_from_str(std::string in, std::string step, std::string dir) {
        set_ports(ports_from_str(std::move(in)),
                  ports_from_str(std::move(step)),
                  ports_from_str(std::move(dir)));
    }
    template <size_t n>
    bits_decoder<n> get_in_to_step_decoder() const noexcept {
        return bits_decoder<n>{
            ports_in_.cbegin(), ports_in_.cend(),
            ports_step_.cbegin()
        };
    } 
    template <size_t n>
    bits_decoder<n> get_in_to_dir_decoder() const noexcept {
        return bits_decoder<n>{
            ports_in_.cbegin(), ports_in_.cend(),
            ports_dir_.cbegin()
        };
    } 
    auto get_port_in() const noexcept {
        return gpio::port32_in{
            ports_in_.cbegin(),
            ports_in_.cend()
        };
    }
    auto get_port_step() const noexcept {
        return gpio::port32_out{
            ports_step_.cbegin(),
            ports_step_.cend()
        };
    }
    auto get_port_dir() const noexcept {
        return gpio::port32_out{
            ports_dir_.cbegin(),
            ports_dir_.cend()
        };
    }
    const auto ports_in() const noexcept {
        return ports_in_;
    }
    const auto ports_step() const noexcept {
        return ports_in_;
    }
    const auto ports_dir() const noexcept {
        return ports_in_;
    }
    std::string ports_in_to_str() const {
        return str_ports_impl(ports_in_);
    }
    std::string ports_step_to_str() const {
        return str_ports_impl(ports_step_);
    }
    std::string ports_dir_to_str() const {
        return str_ports_impl(ports_dir_);
    }
private:
    static std::vector<uint32_t> ports_from_str(std::string str) {
        std::vector<uint32_t> result;
        std::stringstream ss{str};
        std::copy(std::istream_iterator<uint32_t>{ss},
                  std::istream_iterator<uint32_t>{},
                  std::back_inserter(result));
        return result;
    }
    static std::string str_ports_impl(const std::vector<uint32_t>& ports) {        
        std::stringstream ss;
        std::copy(ports.cbegin(), ports.cend(),
            std::ostream_iterator<uint32_t>{ss, " "});
        return ss.str();
    }
    std::vector<uint32_t> ports_in_ = {  gpio::pins::P12, gpio::pins::P13  };
    std::vector<uint32_t> ports_step_ = { gpio::pins::P3, gpio::pins::P7 };
    std::vector<uint32_t> ports_dir_ =  { gpio::pins::P5, gpio::pins::P8 };
};

}