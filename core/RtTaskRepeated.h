#pragma once

#include "RtTask.h"

namespace core {

class RtTaskRepeated : public RtTask
{
public:
    RtTaskRepeated(RtTaskSharedPtr task, int repeatsCount = 1);
    int getRepeatsCount() const noexcept {
        return mRepeatsCount;
    }
    int getCurrentRepeat() const noexcept {
        return mCurrentRepeat;
    }
private:
    int mRepeatsCount{};
    std::atomic_int mCurrentRepeat{0};
    RtTaskSharedPtr mTask;

    // RtTask interface
private:
    bool runImpl();
    void cancelImpl();    
};

} // namespace core

