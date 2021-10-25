
#include "gpio_def.h"


std::ostream& operator<<(std::ostream& os, const bbb::gpio::direction_t& dir) {
    switch (dir) {
        case bbb::gpio::direction_t::dir_input: os << "in"; break;
        case bbb::gpio::direction_t::dir_output: os << "out"; break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::edge_t& edge) {
    switch (edge) {
        case bbb::gpio::edge_t::edge_none: os << "none"; break;
        case bbb::gpio::edge_t::edge_rising: os << "rising"; break;
        case bbb::gpio::edge_t::edge_falling: os << "falling"; break;
        case bbb::gpio::edge_t::edge_both: os << "both"; break;
    }

    return os;
}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::value_t& value) {
    switch (value) {
        case bbb::gpio::value_t::value_low: os << "low"; break;
        case bbb::gpio::value_t::value_high: os << "high"; break;
    }

    return os;
}
