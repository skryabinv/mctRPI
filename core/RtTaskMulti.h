#pragma once
#include "RtTask.h"
#include <initializer_list>
#include <vector>

namespace core {

class RtTaskMulti : public RtTask
{
public:    
    RtTaskMulti(std::initializer_list<RtTaskSharedPtr> tasks)
        : mTasks{tasks} {}
    // RtTask interface
private:
    bool runImpl() override;
    void cancelImpl() override;
private:
    std::vector<RtTaskSharedPtr> mTasks;
};

} // namespace core

