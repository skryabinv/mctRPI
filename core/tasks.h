#pragma once

#include <functional>
#include <atomic>
#include <memory>

namespace core {
namespace tasks {

// Базовый класс для задачи
class task_base : public std::enable_shared_from_this<task_base> {
public:
    // Конструктор
    task_base();
    // Деструктор
    virtual ~task_base();
    // Отменить задачу
    void cancel() noexcept {
        cancel_ = true;
    }
    // Отменена ли задача
    bool is_canceled() const noexcept {
        return cancel_;
    }
    // Флаг выполнения задачи
    bool done() const noexcept {
        return done_;
    }
    // Преобразование в функциональный объект stl
    std::function<bool()> to_std_function();
    // Запуск задачм
    bool run();
protected:
    std::atomic_bool cancel_;
private:
    virtual bool run_impl() = 0;
    std::atomic_bool done_;
};

// Задача создаваемая по лямбда-выражению
// Функтор получает ссылку на атомарный флаг отмены, при вызове
// bool FuncType(std::atomic_bool&)
template <typename FuncType>
class task_func : public task_base{
public:
    task_func(FuncType func)
        : func_{std::move(func)} {
    }
private:
    bool run_impl() override {
        return func_(cancel_);
    }
private:
    FuncType func_;
};

template <typename FuncType>
auto make_shared_task_func(FuncType func) {
    return std::make_shared<task_func<FuncType>>(std::move(func));
}

}
}
