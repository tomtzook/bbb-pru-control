
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "gpio_direct.h"


namespace bbb::gpio {

#ifdef GPIO_DIRECT_GLOBAL
direct_module _global_gpio_modules[] = {
    direct_module(direct_module::GPIO0_OFFSET),
    direct_module(direct_module::GPIO1_OFFSET),
    direct_module(direct_module::GPIO2_OFFSET),
    direct_module(direct_module::GPIO3_OFFSET)
};
#endif

direct_module::direct_module(size_t module_mem_offset) noexcept
    : m_module_ctrl(nullptr) {
    int fd = open("/dev/mem", O_RDWR);
    if (fd < 0) {
        return;
    }

    volatile void* mem = mmap(nullptr, MODULE_CTRL_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, module_mem_offset);
    if (MAP_FAILED == mem) {
        close(fd);
        return;
    }

    close(fd);

    m_module_ctrl = reinterpret_cast<volatile uint8_t*>(mem);
}

direct_module::~direct_module() {
    if (nullptr != m_module_ctrl) {
        munmap((void*) m_module_ctrl, MODULE_CTRL_SIZE);
    }
}

direct_pin::direct_pin(direct_module* module, unsigned mask)
    : m_module(module)
    , m_mask(mask) {
}

direction_t direct_pin::direction() const {
    auto ctrl_value = *m_module->ctrl<direct_module::CTRL_OE>();
    if (ctrl_value & m_mask) {
        return dir_input;
    } else {
        return dir_output;
    }
}

edge_t direct_pin::edge() const {
    return edge_none;
}

value_t direct_pin::value() const {
    unsigned int ctrl_value;
    switch (direction()) {
        case dir_input:
            ctrl_value = *m_module->ctrl<direct_module::CTRL_DATAIN>();
            break;
        case dir_output:
            ctrl_value = *m_module->ctrl<direct_module::CTRL_DATAOUT>();
            break;
    }

    return (ctrl_value & m_mask) ?
        value_high :
        value_low;
}

void direct_pin::direction(direction_t direction) {
    switch (direction) {
        case dir_input:
            *m_module->ctrl<direct_module::CTRL_OE>() |= m_mask;
            break;
        case dir_output:
            *m_module->ctrl<direct_module::CTRL_OE>() &= ~m_mask;
            break;
    }
}

void direct_pin::edge(edge_t edge) {

}

void direct_pin::value(value_t value) {
    switch (value) {
        case value_low:
            *m_module->ctrl<direct_module::CTRL_CLEARDATAOUT>() |= m_mask;
            break;
        case value_high:
            *m_module->ctrl<direct_module::CTRL_SETDATAOUT>() |= m_mask;
            break;
    }
}

}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::direct_pin& pin) {
    os << "PIN: " << std::endl
       << "\tdirection: " << pin.direction() << std::endl
       << "\tedge: " << pin.edge() << std::endl
       << "\tvalue: " << pin.value();

    return os;
}
