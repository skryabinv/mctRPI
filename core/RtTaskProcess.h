#pragma once

#include "RtTask.h"
#include <vector>

namespace core {

class CoronaTreater;
class RtTaskRepeated;

class RtTaskProcess : public RtTask
{
public:    

    RtTaskProcess(const CoronaTreater& treater,
                  double xRange, double yRange,
                  double height, int repeats,
                  double speedFraction);

    double getProgress() const;

private:
    std::atomic_int mCurrentStripe{0};
    int mStripesCount{0};
    int mRepeatsCount{0};
    double mOneRepeatPath{0.0};
    double mInitialPosY{};
    double mInitialPosX{};
    double mRangeX{};
    double mRangeY{};
    double mHeight{};
    double mSpeedY;
    std::shared_ptr<RtTaskRepeated> mTask{};
    std::shared_ptr<RtTaskRepeated> createTask(const CoronaTreater& treater, int repeats);
    auto getCurrentStripeIncFunc() { return [this](RtTask&) {
            mCurrentStripe++;
            return true;
        }; }
    auto getCurrentStripeClearFunc() { return [this](RtTask&) {
            mCurrentStripe = 0;
            return true;
        }; }
    // RtTask interface
private:
    bool runImpl();
    void cancelImpl();
};

} // namespace core

