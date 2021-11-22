#pragma once

#include "RtTask.h"
#include <functional>

namespace core {

// generic task with lambda- initialization
class RtTaskGeneric : public RtTask {
public:
    template<typename Func>
    RtTaskGeneric(Func func, std::string description = {})
        : RtTask{std::move(description)},
          mTask{std::move(func)} {
    }
private:
    std::function<bool(RtTask&)> mTask;

    // RtTask interface
private:
    bool runImpl();
};

template <typename Func>
auto makeSharedGenericTask(Func func, std::string description = {}) {
    return std::make_shared<RtTaskGeneric>(std::move(func), std::move(description));
}

}
