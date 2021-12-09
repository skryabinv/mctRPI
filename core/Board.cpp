#include "Board.h"
#include "Axis.h"
#include "OuputPort.h"
#include "RtTaskMulti.h"
#include <stdexcept>
#include <utility>
#include <initializer_list>

namespace core {

Board::~Board() = default;

Board::Board() {
    mAxisMap["X"] = std::make_unique<Axis>();
    mAxisMap["Y"] = std::make_unique<Axis>();
    mAxisMap["Z"] = std::make_unique<Axis>();

    mOuts["flash"] = std::make_unique<OuputPort>(0);

}

RtTaskSharedPtr Board::createHomeAllTask() const
{
    auto result = std::make_shared<RtTaskMulti>(
                std::initializer_list<RtTaskSharedPtr>{
                    getAxis("Z").createTaskFindHome(),
                    getAxis("X").createTaskFindHome(),
                    getAxis("Y").createTaskFindHome()
                });
    return result;
}

Axis& Board::getAxis(const std::string& name) const
{
    auto it = mAxisMap.find(name);
    if(it == mAxisMap.end()) {
        throw std::invalid_argument("Wrong axis name");
    }
    return *it->second;
}

OuputPort &Board::getExternalOut(const std::string& name) const
{
    auto it = mOuts.find(name);
    if(it == mOuts.end()) {
        throw std::invalid_argument("Wrong axis name");
    }
    return *it->second;
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
