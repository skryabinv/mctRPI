#include "tasks.h"
#include <iostream>

namespace {

class done_flag_handler {
public:
    explicit done_flag_handler(std::atomic_bool& flag) : flag_{flag} {
        flag_ = false;
    }
    ~done_flag_handler() {
        flag_ = true;
    }
private:
    std::atomic_bool& flag_;
};

}

namespace core {
namespace tasks {

bool task_base::run() {
    done_flag_handler handler(done_);
    bool result = run_impl();
    return result;
}

std::function<bool()> task_base::to_std_function() {
    // Захватываем умный указатель, чтобы задача не удалилась раньше времени
    return [self{shared_from_this()}] {
        return self->run();
    };
}

task_base::task_base() {

}

task_base::~task_base() {
    std::cout << __FUNCTION__ << std::endl;
}


}
}
