//
// Created by VLADIMIR on 08.09.2021.
//

#include "board.h"
#include "axis.h"

namespace core {

const axis &board::get_axis(const std::string &name) const {
    auto it = axis_map_.find(name);
    if(it == axis_map_.end()) {
        throw std::invalid_argument("Wrong axis name");        
    }
    return *it->second;
}

void board::init_instance() {
    instance_.reset(new board());
}

void board::load_settings() {

}

board &board::instance() {
    if(!instance_)
        throw std::logic_error("Instance of board object need to be initialized");
    return *instance_;
}

board::board() = default;

board::~board() = default;

}
