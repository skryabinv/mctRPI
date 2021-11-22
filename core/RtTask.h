#pragma once

#include <atomic>
#include <memory>
#include <string>

namespace core {

// Base class for real-time task
class RtTask
{
public:
    RtTask(std::string description = {})
        : mDescription{std::move(description)} {}
    bool run();
    bool isCanceled() const noexcept { return mCanceled; }
    bool isDone() const noexcept { return mDone; }
    void cancel() noexcept { mCanceled = true; }
    bool canceled() const noexcept { return mCanceled; }
    const auto& getDescription() const noexcept { return mDescription; }
private:
    std::string mDescription;
    virtual bool runImpl() = 0;
    std::atomic_bool mDone{false};
    std::atomic_bool mCanceled{false};
};

using RtTaskSharedPtr = std::shared_ptr<RtTask>;

} // namespace core

