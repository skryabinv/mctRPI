#pragma once

#include "RtTask.h"
#include <memory>
#include <unordered_map>
#include <string>

namespace core {

class Axis;
class OutputPort;
class CoronaTreater;

class Board {
public:
    inline static const std::string X{"X"};
    inline static const std::string Y{"Y"};
    inline static const std::string Z{"Z"};
    ~Board();
    RtTaskSharedPtr createTaskHomeAll() const;    
    Axis& getAxis(const std::string& name) const;        
    CoronaTreater& getCoronaTreater() const;    
    bool isHomingAllDone() const;
    static void initInstance();
    // Ссылка на объект платы
    static Board& getInstance();
private:
    Board();    
    using board_ptr_t = std::unique_ptr<Board>;
    using axis_ptr_t = std::unique_ptr<Axis>;    
    inline static board_ptr_t sInstance;
    std::array<axis_ptr_t, 3> mAxisMap;
    std::unique_ptr<CoronaTreater> mCoronaTreater;
};

} // namespace core

