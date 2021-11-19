#include "Board.h"
#include "Axis.h"
#include <stdexcept>
#include <utility>

namespace core {

Board::~Board() = default;

Board::Board() {
    mAxisMap["X"] = std::make_unique<Axis>();
    mAxisMap["Y"] = std::make_unique<Axis>();
    mAxisMap["Z"] = std::make_unique<Axis>();
}

Axis& Board::getAxis(const std::string& name) const
{
    auto it = mAxisMap.find(name);
    if(it == mAxisMap.end()) {
        throw std::invalid_argument("Wrong axis name");
    }
    return *it->second;
}

void Board::initInstance()
{
    sInstance.reset(new Board());
}

Board& Board::instance()
{
    if(!sInstance)
        throw std::logic_error("Instance of board object need to be initialized");
    return *sInstance;
}

} // namespace core
