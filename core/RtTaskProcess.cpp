#include "RtTaskProcess.h"
#include "CoronaTreater.h"
#include "RtTaskGeneric.h"
#include "RtTaskMulti.h"
#include "RtTaskRepeated.h"
#include "Board.h"
#include "Axis.h"
#include "OutputPort.h"


namespace core {

RtTaskProcess::RtTaskProcess(CoronaTreater& treater,
                             double rangeX,
                             double rangeY,
                             double height,
                             int repeats,
                             double speedFraction)
{
    mRangeX = rangeX;
    mRangeY = rangeY;
    mSpeedY = speedFraction;
    mRepeatsCount = repeats;
    mHeight = height;
    mStripesCount = treater.getStripesCount(rangeX);
    mInitialPosY = treater.getInitalPosY();
    mInitialPosX = treater.getInitalPosX();
    mOneRepeatPath = mRangeY * treater.getStripesCount(rangeX);
    mTask = createTask(treater, repeats);
}

double RtTaskProcess::getProgress() const
{
    if(!mTask || mTask->isDone()) {
        return -1.0;
    } else {
        double result = mTask->getCurrentRepeat() * mOneRepeatPath;
        auto pos = Board::getInstance()
                .getAxis("Y")
                .getCurrentPos();
        double path = mCurrentStripe * mRangeY;
        if(mCurrentStripe != mStripesCount) {
            if((mCurrentStripe & 1) == 0) {
                path += std::max(0.0, pos - mInitialPosY);
            } else {
                path += std::max(0.0, mInitialPosY + mRangeY - pos);
            }
        }
        result += path;
        return result / mRepeatsCount / mOneRepeatPath;
    }
}

std::shared_ptr<RtTaskRepeated> RtTaskProcess::createTask(CoronaTreater &treater,
                                                          int repeats)
{
    std::vector<RtTaskSharedPtr> tasks;
    tasks.push_back(treater.createTaskMoveToInitialPos());
    // Moving along Z
    tasks.push_back(
                Board::getInstance()
                .getAxis("Z")
                .createTaskMoveTo(treater.getSpeedFractionZ(),
                                  mHeight + treater.getWorkingHeight()));
    // Clear Stripes Counter
    tasks.push_back(makeSharedGenericTask(getCurrentStripeClearFunc()));
    // Enable corona pin
    tasks.push_back(treater.createTaskOn());

    for(int i = 0; i < mStripesCount; ++i) {
        auto dir = (i % 2 == 0) ? 1.0 : -1.0;
        // Process along X
        tasks.push_back(Board::getInstance()
                        .getAxis("Y")
                        .createTaskJog(dir * mSpeedY, mRangeY));
        // Increment Stripes Counter
        tasks.push_back(makeSharedGenericTask(getCurrentStripeIncFunc()));
        // Moving along Y
        if( i != mStripesCount - 1) {
            tasks.push_back(
                        Board::getInstance()
                        .getAxis("X")
                        .createTaskJog(treater.getSpeedFractionX(),
                                       treater.getCoronaWidth()));
        }
    }
    tasks.push_back(treater.createTaskOff());
    tasks.push_back(treater.createTaskMoveToInitialPos());
    auto taskMulti = std::make_shared<RtTaskMulti>(std::move(tasks));
    return std::make_shared<RtTaskRepeated>(std::move(taskMulti), repeats);
}

bool RtTaskProcess::runImpl()
{
    mTask->run();
    return true;
}

void RtTaskProcess::cancelImpl()
{
    if(mTask) mTask->cancel();
}

} // namespace core
