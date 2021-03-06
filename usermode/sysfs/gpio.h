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

    virtual const char* what() const noexcept override {
        return "Bad value";
    }

private:
    std::string m_value;
};

class sysfs_pin : public pin {
public:
    explicit sysfs_pin(unsigned number);
    ~sysfs_pin();

    bool accessible() const;
    bool readable() const;
    bool writable() const;

    unsigned number() const;

    std::string label() const;
    direction_t direction() const override;
    edge_t edge() const;
    value_t value() const override;

    void direction(direction_t direction) override;
    void edge(edge_t edge);
    void value(value_t value) override;

    static void export_pin(unsigned number);
    static void unexport_pin(unsigned number);

private:
    static constexpr const char* SYSFS_EXPORT = "/sys/class/gpio/export";
    static constexpr const char* SYSFS_UNEXPORT = "/sys/class/gpio/unexport";

    static constexpr const char* SYSFS_FILE_FORMAT = "/sys/class/gpio/gpio%d/%s";

    static constexpr const char* FILE_LABEL = "label";
    static constexpr const char* FILE_DIRECTION = "direction";
    static constexpr const char* FILE_EDGE = "edge";
    static constexpr const char* FILE_VALUE = "value";

    static constexpr const char* DIRECTION_INPUT = "in";
    static constexpr const char* DIRECTION_OUTPUT = "out";

    static constexpr const char* EDGE_NONE = "none";
    static constexpr const char* EDGE_RISING = "rising";
    static constexpr const char* EDGE_FALLING = "falling";
    static constexpr const char* EDGE_BOTH = "both";

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
sysfs_pin make_sysfs_pin() {
    return sysfs_pin(T::NUMBER);
}

}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::sysfs_pin& pin);
