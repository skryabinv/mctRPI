#include "Board.h"
#include "Axis.h"
#include "OutputPort.h"
#include "RtTaskMulti.h"
#include "CoronaTreater.h"
#include <stdexcept>
#include <utility>
#include <initializer_list>

namespace core {

Board::~Board() = default;

Board::Board() {
    mAxisMap["X"] = std::make_unique<Axis>();
    mAxisMap["Y"] = std::make_unique<Axis>();
    mAxisMap["Z"] = std::make_unique<Axis>();

    mCoronaTreater = std::make_unique<CoronaTreater>();
}

RtTaskSharedPtr Board::createTaskHomeAll() const
{
    auto result = std::make_shared<RtTaskMulti>(
                std::initializer_list<RtTaskSharedPtr>{
                    getAxis("Z").createTaskFindHome(),
                    getAxis("X").createTaskFindHome(),
                    getAxis("Y").createTaskFindHome()
                });
    return result;
}

RtTaskSharedPtr Board::createTaskMoveToHome() const
{
    return {};
}

Axis& Board::getAxis(const std::string& name) const
{
    auto it = mAxisMap.find(name);
    if(it == mAxisMap.end()) {
        throw std::invalid_argument("Wrong axis name");
    }
    return *it->second;
}

OutputPort &Board::getExternalOut(const std::string& name) const
{
    auto it = mOuts.find(name);
    if(it == mOuts.end()) {
        throw std::invalid_argument("Wrong axis name");
    }
    return *it->second;
}

CoronaTreater& Board::getCoronaTreater() const
{
    return *mCoronaTreater;
}

void Board::createExternalOut(const std::string& name)
{
    assert(!name.empty());
    mOuts[name] = std::make_unique<OutputPort>();
}

void Board::initInstance()
{
    sInstance.reset(new Board());
}

Board& Board::getInstance()
{
    if(!sInstance)
        throw std::logic_error("Instance of board object need to be initialized");
    return *sInstance;
}

} // namespace core
