#pragma once

#include <memory>
#include <unordered_map>
#include <string>

namespace core {

class Axis;

// Абстракция платы
class Board {
public:
    // Дестркутор
    ~Board();
    // Получить ось по имени
    // Если такой оси не существует бросается исключение std::invalid_argument
    Axis& getAxis(const std::string& name) const;
    static void initInstance();
    // Ссылка на объект платы
    static Board& instance();
private:
    Board();
    using board_ptr_t = std::unique_ptr<Board>;
    using axis_ptr_t = std::unique_ptr<Axis>;
    // Указатель на единственный экземпляр платы
    inline static board_ptr_t sInstance;
    // Таблица осей
    // Название, например, "X" : указатель на ось
    std::unordered_map<std::string, axis_ptr_t> mAxisMap;
    // Порт с выходами (для реле например)
};

} // namespace core

