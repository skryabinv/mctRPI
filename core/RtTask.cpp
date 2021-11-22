#include "RtTask.h"

namespace core {

bool RtTask::run()
{
    mDone = false;
    bool result = runImpl();
    mDone = true;
    return result;
}

} // namespace core
