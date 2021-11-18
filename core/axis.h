#pragma  once

#include <memory>
#include <vector>
#include <functional>
#include "axis_limits.h"
#include "axis_gear_ratio.h"
#include "axis_speed_settings.h"
#include "axis_ports.h"

namespace core {

namespace tasks {
class task_base;
}

// Ось
// TODO: Добавить чтение и загрузку настроек
// из файла и формирование задач
class axis {
public:
    using axis_task_t = std::function<bool()>;

    // Сохранить данные оси
    void save() const;

    // Загрузить данные оси
    void load();

    // Ограничения оси
    const auto& limits() const noexcept {
        return limits_;        
    }

    // Настройки скорости
    const auto& speed_settings() const noexcept {
        return speed_settings_;
    }

    // Коэффициент передачи оси
    const auto& gear_ratio() const noexcept {
        return ratio_;
    } 

    // Порты оси
    const auto& ports() const noexcept {
        return ports_;        
    }

    // Создать задачу движения в заданном направлении
    std::shared_ptr<tasks::task_base> task_jog(double speed_mm_per_min) ;

    // Создать задачу поиска нуля
    std::shared_ptr<tasks::task_base> task_find_home() const;

    // Создать задачу езды в заданном направлении
    std::shared_ptr<tasks::task_base> task_move_to(double pos, double speed_mm_per_min) const;

private:

    // Текущая позиция
    // TODO: Как обновлять позицию из потока задач?
    double current_pos_{0.0};
    
    // Настройки скорости оси
    axis_speed_settings speed_settings_;

    // Ограничения осей
    axis_limits limits_;

    // Передаточное отношение оси
    axis_gear_ratio ratio_;
    
    // Таблица портов оси
    axis_ports ports_;    
};

}

