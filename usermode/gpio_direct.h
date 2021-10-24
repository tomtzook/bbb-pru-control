#pragma once

#include "gpio_def.h"


namespace bbb::gpio {

class module_access_exception : std::exception {

};

class direct_module {
public:
    static constexpr size_t GPIO0_OFFSET = 0x44e07000;
    static constexpr size_t GPIO1_OFFSET = 0x4804c000;
    static constexpr size_t GPIO2_OFFSET = 0x481ac000;
    static constexpr size_t GPIO3_OFFSET = 0x481ae000;

    static constexpr size_t CTRL_OE = 0x134;
    static constexpr size_t CTRL_DATAIN = 0x138;
    static constexpr size_t CTRL_DATAOUT = 0x13c;
    static constexpr size_t CTRL_CLEARDATAOUT = 0x190;
    static constexpr size_t CTRL_SETDATAOUT = 0x194;

    explicit direct_module(size_t module_mem_offset) noexcept;
    ~direct_module();

    template<size_t offset=0>
    volatile unsigned int* ctrl() {
        if (nullptr == m_module_ctrl) {
            throw module_access_exception();
        }

        return reinterpret_cast<volatile unsigned int*>(m_module_ctrl + offset);
    }

private:
    static constexpr size_t MODULE_CTRL_SIZE = 0x1000;

    volatile uint8_t* m_module_ctrl;
};

class direct_pin {
public:
    direct_pin(direct_module* module, unsigned mask);

    direction_t direction() const;
    edge_t edge() const;
    value_t value() const;

    void direction(direction_t direction);
    void edge(edge_t edge);
    void value(value_t value);

private:
    direct_module* m_module;
    unsigned m_mask;
};

#ifdef GPIO_DIRECT_GLOBAL
extern direct_module _global_gpio_modules[];

template<
        typename T,
        typename std::enable_if<
                is_pin_def<T>::value,
                bool>::type = 0
>
direct_pin make_direct_pin() {
    return direct_pin(_global_gpio_modules + T::MODULE, 1u << T::INDEX);
}
#endif

}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::direct_pin& pin);
