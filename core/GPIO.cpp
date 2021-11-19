#include "GPIO.h"
//#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <memory>
#include <system_error>
#include <iostream>

namespace {

constexpr uint32_t GPIO_BASE = 0x3f200000; // Для RPI 2,3

struct mem_file_handle {
    int fd{};
//    mem_file_handle() {
//        fd = open("/dev/mem", O_RDWR | O_SYNC);
//    }
//    uint32_t* map() {
//        if(fd < 0) throw std::system_error(errno, std::system_category());
//        auto res = static_cast<uint32_t*>(mmap(
//                0, getpagesize(),
//                PROT_READ | PROT_WRITE, MAP_SHARED,
//                fd, GPIO_BASE));
//        if(reinterpret_cast<int32_t>(res) < 0) {
//            throw std::system_error(errno, std::system_category());
//        }
//        return res;
//    }
//    ~mem_file_handle() {
//        close(fd);
//    }
};
}

namespace core {
namespace gpio {

volatile uint32_t * gpio_base{};

bool initialize() {
    try {
        mem_file_handle file;
//        gpio_base = file.map();
    }
    catch (const std::system_error& err) {
        return false;
    }
    return true;
}

}
}

