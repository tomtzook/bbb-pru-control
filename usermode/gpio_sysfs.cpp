
#include <unistd.h>

#include <fstream>
#include <climits>

#include "gpio_sysfs.h"


namespace bbb::gpio {

pin::pin(unsigned number)
    : m_number(number) {
    if (!accessible()) {
        export_pin(m_number);
    }
}

pin::~pin() {
    if (accessible()) {
        unexport_pin(m_number);
    }
}

bool pin::accessible() const {
    char path[PATH_MAX] = {0};
    sprintf(path, SYSFS_FILE_FORMAT, m_number, "");

    return 0 == access(path, F_OK);
}

bool pin::readable() const {
    char path[PATH_MAX] = {0};
    sprintf(path, SYSFS_FILE_FORMAT, m_number, "");

    return 0 == access(path, R_OK);
}

bool pin::writable() const {
    char path[PATH_MAX] = {0};
    sprintf(path, SYSFS_FILE_FORMAT, m_number, "");

    return 0 == access(path, W_OK);
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

    std::ifstream stream(path);
    stream.exceptions(std::ifstream::failbit);

    std::string value;
    stream >> value;

    return value;
}

void pin::write(const char* file, const std::string& value) {
    char path[PATH_MAX] = {0};
    sprintf(path, SYSFS_FILE_FORMAT, m_number, file);

    std::ofstream stream(path);
    stream.exceptions(std::ifstream::failbit);

    stream << value;
}

void pin::export_pin(unsigned number) {
    std::ofstream stream(SYSFS_EXPORT);
    stream.exceptions(std::ifstream::failbit);

    stream << number;
}

void pin::unexport_pin(unsigned number) {
    std::ofstream stream(SYSFS_UNEXPORT);
    stream.exceptions(std::ifstream::failbit);

    stream << number;
}

}

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

std::ostream& operator<<(std::ostream& os, const bbb::gpio::pin& pin) {
    os << "PIN: " << std::endl;

    if (pin.readable()) {
        os  << "\tlabel: " << pin.label() << std::endl
            << "\tdirection: " << pin.direction() << std::endl
            << "\tedge: " << pin.edge() << std::endl
            << "\tvalue: " << pin.value();
    } else {
        os << "\tNo read access";
    }

    return os;
}
