#include "Board.h"
#include "Axis.h"
#include "OutputPort.h"
#include "RtTaskMulti.h"
#include "CoronaTreater.h"
#include <stdexcept>
#include <utility>
#include <initializer_list>

namespace core {

namespace keys {
    static constexpr int X = 0;
    static constexpr int Y = 1;
    static constexpr int Z = 2;
}

Board::~Board() = default;

Board::Board() {
    mAxisMap[keys::X] = std::make_unique<Axis>();
    mAxisMap[keys::Y] = std::make_unique<Axis>();
    mAxisMap[keys::Z] = std::make_unique<Axis>();
    mCoronaTreater = std::make_unique<CoronaTreater>();
}

RtTaskSharedPtr Board::createTaskHomeAll() const
{
    auto result = std::make_shared<RtTaskMulti>(
                std::initializer_list<RtTaskSharedPtr>{
                    getAxis(Z).createTaskFindHome(),
                    getAxis(X).createTaskFindHome(),
                    getAxis(Y).createTaskFindHome()
                });
    return result;
}

Axis& Board::getAxis(const std::string &name) const
{
    if(name == X) return *mAxisMap[keys::X];
    if(name == Y) return *mAxisMap[keys::Y];
    if(name == Z) return *mAxisMap[keys::Z];
    throw std::invalid_argument("Wrong axis name");
}

CoronaTreater& Board::getCoronaTreater() const
{
    return *mCoronaTreater;
}

bool Board::isHomingAllDone() const
{
    for(const auto& axis : mAxisMap) {
        if(!axis->isHomingDone()) return false;
    }
    return true;
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
