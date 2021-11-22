#pragma once
#include "RtTask.h"

namespace core {

class RtTaskMulti : RtTask
{
public:
    RtTaskMulti();

    // RtTask interface
private:
    bool runImpl();
};

} // namespace core

