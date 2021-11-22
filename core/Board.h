#pragma once

#include <memory>
#include <unordered_map>
#include <string>

namespace core {

class Axis;
class ExternalOut;

class Board {
public:
    ~Board();

    Axis& getAxis(const std::string& name) const;
    ExternalOut& getExternalOut() const;
    static void initInstance();
    // Ссылка на объект платы
    static Board& instance();
private:
    Board();
    using board_ptr_t = std::unique_ptr<Board>;
    using axis_ptr_t = std::unique_ptr<Axis>;
    inline static board_ptr_t sInstance;
    std::unordered_map<std::string, axis_ptr_t> mAxisMap;
    std::unique_ptr<ExternalOut> mOut;
};

} // namespace core

