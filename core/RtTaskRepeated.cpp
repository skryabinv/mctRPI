#include "RtTaskRepeated.h"

namespace core {

RtTaskRepeated::RtTaskRepeated(RtTaskSharedPtr task, int repeatsCount)
    : mRepeatsCount{repeatsCount},
      mTask{ std::move(task) }
{}

bool RtTaskRepeated::runImpl()
{
    for(mCurrentRepeat = 0; mCurrentRepeat < mRepeatsCount && !isCanceled(); ++mCurrentRepeat) {
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
