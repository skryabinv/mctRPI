#include "RtTask.h"

namespace core {

bool RtTask::run()
{
    mDone = false;
    bool result = runImpl();
    mDone = true;
    return result;
}

void RtTask::cancel()
{
    mCanceled = true;
    cancelImpl();
}

bool RtTask::runImpl()
{
    return false;
}

void RtTask::cancelImpl()
{
    // For overriding
}

} // namespace core
