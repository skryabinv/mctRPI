#pragma once

#include "RtTask.h"
#include <memory>
#include <unordered_map>
#include <string>

namespace core {

class Axis;
class OuputPort;

class Board {
public:
    ~Board();
    RtTaskSharedPtr createHomeAllTask() const;
    Axis& getAxis(const std::string& name) const;
    OuputPort& getExternalOut(const std::string& name) const;
    static void initInstance();
    // Ссылка на объект платы
    static Board& getInstance();
private:
    Board();
    using board_ptr_t = std::unique_ptr<Board>;
    using axis_ptr_t = std::unique_ptr<Axis>;
    using out_ptr_t = std::unique_ptr<OuputPort>;
    inline static board_ptr_t sInstance;
    std::unordered_map<std::string, axis_ptr_t> mAxisMap;
    std::unordered_map<std::string, out_ptr_t> mOuts;
};

} // namespace core

