#include "RtTaskRepeated.h"

namespace core {

RtTaskRepeated::RtTaskRepeated(RtTaskSharedPtr task, int repeatsCount)
    : mRepeatsCount{repeatsCount},
      mTask{ std::move(task) }
{}

bool RtTaskRepeated::runImpl()
{
    for(int i = 0; i < mRepeatsCount && !isCanceled(); ++i) {
        bool result = mTask->run();
        if(!result) return false;
    }
    return true;
}

void RtTaskRepeated::cancelImpl()
{
    mTask->cancel();
}



} // namespace core
