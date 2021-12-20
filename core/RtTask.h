#pragma once

#include <atomic>
#include <memory>
#include <string>

namespace core {

// Base class for real-time task
class RtTask
{
public:
    RtTask(std::string description = {}, bool done = false)
        : mDescription{std::move(description)}, mDone{done} {}
    virtual ~RtTask() = default;
    bool run();
    bool isCanceled() const noexcept { return mCanceled; }
    bool isDone() const noexcept { return mDone; }
    void cancel();
    const auto& getDescription() const noexcept { return mDescription; }
private:    
    virtual bool runImpl();
    virtual void cancelImpl();
    std::string mDescription{};
    std::atomic_bool mDone{false};
    std::atomic_bool mCanceled{false};
};

using RtTaskSharedPtr = std::shared_ptr<RtTask>;

} // namespace core

