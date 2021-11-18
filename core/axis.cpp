#include "axis.h"
#include "tasks.h"
#include "acc_dec_pulse_generator.h"
#include "delay.h"

namespace core {


void axis::save() const {
        
}

void axis::load() {
    
}

std::shared_ptr<tasks::task_base> axis::task_jog(double speed_mm_per_min) {
    auto out_dir = ports().get_port_dir();
    auto out_step = ports().get_port_step();
    // Ограничиваем скорость вдоль оси
    speed_mm_per_min = speed_settings().limit_speed(speed_mm_per_min);
    auto dist = speed_mm_per_min > 0.0 ? limits().high() : limits().low();
    auto func = [=](std::atomic_bool& cancel) {
        // Ограничиваем величину оси (двигаемся до ограничения)
        acc_dec_pulse_generator gen {dist,
                                    gear_ratio().mm_per_step(),
                                    std::abs(speed_mm_per_min),
                                    speed_settings().acc_mm_per_sec2(),
                                    speed_settings().dec_mm_per_sec2()};
        if(speed_mm_per_min > 0.0) out_dir.set();
        else out_dir.clr();
        while (!cancel && gen) {
            auto delay_func = gen.delay_us<delay::proxy_delay, 2>();
            out_step.set();
            delay_func();
            out_step.clr();
            delay_func();
            ++gen;
        }
        return true;
    };
    return tasks::make_shared_task_func(std::move(func));
}

std::shared_ptr<tasks::task_base> axis::task_find_home() const {
    auto out_dir = ports().get_port_dir();
    auto out_step = ports().get_port_step();
    auto in_switch = ports().get_port_in();
    // Декодер битов
    auto step_decoder = ports().get_in_to_step_decoder<2>();
    auto func = [=](std::atomic_bool& cancel) {
        // Едем вперед, пока концевики замкнуты
        acc_dec_pulse_generator gen_fwd{
            gear_ratio().mm_per_step(),
            speed_settings().speed_home_fwd(),
            speed_settings().acc_mm_per_sec2()
        };
        // Включаем одно направление
        out_dir.set();
        while (!cancel) {
            auto sw_mask = in_switch.read();
            if(!sw_mask) break; // Концевик размокнут
            // Перекаодируем в маску степов
            auto mask = step_decoder.decode_left_to_right(sw_mask);
            // Устанавливаем степы с перекаодированной маской
            auto delay_func = gen_fwd.delay_us<delay::proxy_delay>();
            out_step.set(mask);
            delay_func();
            out_step.clr(mask);
            delay_func();
            ++gen_fwd;

        }
        out_dir.clr();
        // Едем назад пока концевики разомкнуты
        acc_dec_pulse_generator gen_back{
            gear_ratio().mm_per_step(),
            speed_settings().speed_home_back(),
            speed_settings().acc_mm_per_sec2()
        };
        while (!cancel) {
            auto sw_mask = in_switch.read();
            if(sw_mask) break; // Концевик размокнут
            // Перекаодируем в маску степов
            auto mask = step_decoder.decode_left_to_right(sw_mask);
            // Устанавливаем степы с перекаодированной маской
            auto delay_func = gen_back.delay_us<delay::proxy_delay>();
            out_step.set(~mask);
            delay_func();
            out_step.clr(~mask);
            delay_func();
            ++gen_back;
        }
        return true;
    };
    return tasks::make_shared_task_func(std::move(func));
}

std::shared_ptr<tasks::task_base> axis::task_move_to(double pos, double speed_mm_per_min) const {
    auto out_dir = ports().get_port_dir();
    auto out_step = ports().get_port_step();
    // Расстояние, которое нужно проехать
    auto dist = limits().clamp(pos) - current_pos_;
    speed_mm_per_min = std::abs(speed_settings().limit_speed(speed_mm_per_min));
    auto func = [=](std::atomic_bool& cancel) {
        // Передвижение в координату
        acc_dec_pulse_generator gen{
                dist,
                gear_ratio().mm_per_step(),
                speed_mm_per_min,
                speed_settings().acc_mm_per_sec2(),
                speed_settings().dec_mm_per_sec2()
        };
        if(dist < 0) out_dir.clr();
        else out_dir.set();
        while (!cancel && gen) {
            auto delay_func = gen.delay_us<delay::proxy_delay, 2>();
            out_step.set();
            delay_func();
            out_step.clr();
            delay_func();
            ++gen;
        }
        return true;
    };
    return tasks::make_shared_task_func(std::move(func));
}


}
