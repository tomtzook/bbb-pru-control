#pragma once

#include <string>
#include <ostream>
#include <exception>

#include "gpio_def.h"


namespace bbb::gpio {

class bad_value_exception : public std::exception {
public:
    explicit bad_value_exception(std::string value)
        : m_value(std::move(value))
    {}

    std::string value() const {
        return m_value;
    }

private:
    std::string m_value;
};

enum direction_t {
    dir_input,
    dir_output
};

enum edge_t {
    edge_none
};

enum value_t {
    value_low,
    value_high
};

class pin {
public:
    explicit pin(unsigned number);

    std::string label() const;
    direction_t direction() const;
    edge_t edge() const;
    value_t value() const;

    void direction(direction_t direction);
    void edge(edge_t edge);
    void value(value_t value);

private:
    static constexpr const char* SYSFS_FILE_FORMAT = "/sys/class/gpio/gpio%d/%s";

    static constexpr const char* FILE_LABEL = "label";
    static constexpr const char* FILE_DIRECTION = "direction";
    static constexpr const char* FILE_EDGE = "edge";
    static constexpr const char* FILE_VALUE = "value";

    static constexpr const char* DIRECTION_INPUT = "in";
    static constexpr const char* DIRECTION_OUTPUT = "out";

    static constexpr const char* EDGE_NONE = "none";

    static constexpr const char* VALUE_LOW = "0";
    static constexpr const char* VALUE_HIGH = "1";

    std::string read(const char* file) const;
    void write(const char* file, const std::string& value);

    unsigned m_number;
};

template<
        typename T,
        typename std::enable_if<
                is_pin_def<T>::value,
                bool>::type = 0
>
pin make_pin() {
    return pin(T::NUMBER);
}

}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::pin& pin);
