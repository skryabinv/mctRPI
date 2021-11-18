//
// Created by VLADIMIR on 08.09.2021.
//

#include "delay.h"
#include <time.h>
#include <iostream>

namespace core {
namespace delay {

// Наносекунд на итерацию
static volatile size_t ns_per_iteration{1};
static volatile size_t counter{0};

task_t create_calibration_task(bool value_to_return) {
    return [=] {
        timespec begin_time, end_time;
        clock_gettime(CLOCK_REALTIME, &begin_time);        
        for(counter = 10'000'000L; counter != 0; --counter) {}
        clock_gettime(CLOCK_REALTIME, &end_time);
        ns_per_iteration =
                (1'000'000'000 * (end_time.tv_sec - begin_time.tv_sec) + end_time.tv_nsec - begin_time.tv_nsec) / 10'000'000L;
        std::cout << "Delay calibration: " << ns_per_iteration << std::endl;
        return value_to_return;
    };
}

void busy_loop(uint32_t us) {
    // TODO: проверка на переполнение    
    for(counter = (1000 * us) / ns_per_iteration; counter != 0; --counter) {}
}

}
}

