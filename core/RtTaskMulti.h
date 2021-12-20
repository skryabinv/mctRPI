#pragma once
#include "RtTask.h"
#include <initializer_list>
#include <vector>

namespace core {

class RtTaskMulti : public RtTask
{
public:    
    RtTaskMulti(std::initializer_list<RtTaskSharedPtr> tasks, std::string description = {})
        : RtTask(std::move(description)),
          mTasks{tasks} {}
    RtTaskMulti(std::vector<RtTaskSharedPtr>&& tasks)
        : mTasks{std::move(tasks)} {}
    // TODO: Add construction from vector
    // RtTask interface    
private:
    bool runImpl() override;
    void cancelImpl() override;
private:
    const std::vector<RtTaskSharedPtr> mTasks;
};

} // namespace core

