#include "RtTaskMulti.h"

namespace core {

bool RtTaskMulti::runImpl()
{
    for(auto& task: mTasks) {
        if(isCanceled()) break;
        task->run();
    }
    return true;
}

void RtTaskMulti::cancelImpl()
{
    for(auto& task: mTasks) {
        task->cancel();
    }
}

} // namespace core
