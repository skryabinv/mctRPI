#pragma once

#include "RtTask.h"

namespace core {

class RtTaskRepeated : public RtTask
{
public:
    RtTaskRepeated(RtTaskSharedPtr task, int repeatsCount = 1);

private:
    int mRepeatsCount{};
    RtTaskSharedPtr mTask;

    // RtTask interface
private:
    bool runImpl();
    void cancelImpl();
};

} // namespace core

