
#include <fstream>
#include <climits>

#include "gpio_config.h"


namespace bbb::gpio {

pin::pin(unsigned number)
    : m_number(number) {
}

std::string pin::label() const {
    return read(FILE_LABEL);
}

direction_t pin::direction() const {
    std::string value = read(FILE_DIRECTION);
    if (DIRECTION_INPUT == value) {
        return dir_input;
    } else if (DIRECTION_OUTPUT == value) {
        return dir_output;
    } else {
        throw bad_value_exception(value);
    }
}

edge_t pin::edge() const {
    std::string value = read(FILE_EDGE);
    if (EDGE_NONE == value) {
        return edge_none;
    } else {
        throw bad_value_exception(value);
    }
}

value_t pin::value() const {
    std::string value = read(FILE_VALUE);
    if (VALUE_LOW == value) {
        return value_low;
    } else if (VALUE_HIGH == value) {
        return value_high;
    } else {
        throw bad_value_exception(value);
    }
}

void pin::direction(direction_t direction) {
    switch (direction) {
        case dir_input:
            write(FILE_DIRECTION, DIRECTION_INPUT);
            break;
        case dir_output:
            write(FILE_DIRECTION, DIRECTION_OUTPUT);
            break;
    }
}

void pin::edge(edge_t edge) {
    switch (edge) {
        case edge_none:
            write(FILE_EDGE, EDGE_NONE);
            break;
    }
}

void pin::value(value_t value) {
    switch (value) {
        case value_low:
            write(FILE_VALUE, VALUE_LOW);
            break;
        case value_high:
            write(FILE_VALUE, VALUE_HIGH);
            break;
    }
}

std::string pin::read(const char* file) const {
    char path[PATH_MAX] = {0};
    sprintf(path, SYSFS_FILE_FORMAT, m_number, file);

    std::ifstream stream;
    stream.open(path);

    std::string value;
    stream >> value;

    return value;
}

void pin::write(const char* file, const std::string& value) {
    char path[PATH_MAX] = {0};
    sprintf(path, SYSFS_FILE_FORMAT, m_number, file);

    std::ofstream stream;
    stream.open(path);

    stream << value;
}

}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::pin& pin) {
    os << "PIN: " << std::endl
        << "\tlabel: " << pin.label() << std::endl
        << "\tdirection: " << pin.direction() << std::endl
        << "\tedge: " << pin.edge() << std::endl
        << "\tvalue: " << pin.value();

    return os;
}
