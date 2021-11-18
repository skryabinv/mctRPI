#pragma once

#include <unordered_map>
#include <string>
#include <memory>

namespace core {

class axis;

// Абстракция платы
class board {
public:
    using board_ptr_t = std::unique_ptr<board>;
    using axis_ptr_t = std::unique_ptr<axis>;
    // Дестркутор
    ~board();
    // Получить ось по имени
    // Если такой оси не существует бросается исключение std::invalid_argument
    const axis& get_axis(const std::string& name) const;
    // Инициализация платы
    // - создание указателя на объект платы
    // - создание объектов осей и карты портов
    static void init_instance();
    // Ссылка на объект платы
    static board& instance();
    // Загрузка настроек платы
    void load_settings();
private:
    board();
    // Указатель на единственный экземпляр платы
    inline static board_ptr_t instance_;
    // Таблица осей
    // Название, например, "X" : указатель на ось
    std::unordered_map<std::string, axis_ptr_t> axis_map_;
    // Порт с выходами (для реле например)
};

}
