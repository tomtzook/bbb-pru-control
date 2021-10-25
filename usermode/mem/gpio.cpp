
#include "mem/gpio.h"


namespace bbb::gpio {

#ifdef MEM_GLOBAL_REGS
module_peripheral _global_modules[] = {
        module_peripheral(gpio0::ADDRESS),
        module_peripheral(gpio1::ADDRESS),
        module_peripheral(gpio2::ADDRESS),
        module_peripheral(gpio3::ADDRESS)
};
#endif

module_peripheral::module_peripheral(size_t address) noexcept
    : peripheral(address, MODULE_CTRL_SIZE) {
}

direct_pin::direct_pin(module_peripheral& module, unsigned mask)
    : m_module_ctrl(module.gpio())
    , m_mask(mask) {
}

direction_t direct_pin::direction() const {
    if (m_module_ctrl->oe & m_mask) {
        return dir_input;
    } else {
        return dir_output;
    }
}

value_t direct_pin::value() const {
    unsigned int reg_value;
    switch (direction()) {
        case dir_input:
            reg_value = m_module_ctrl->datain;
            break;
        case dir_output:
            reg_value = m_module_ctrl->dataout;
            break;
    }

    return (reg_value & m_mask) ?
        value_high :
        value_low;
}

void direct_pin::direction(direction_t direction) {
    switch (direction) {
        case dir_input:
            m_module_ctrl->oe |= m_mask;
            break;
        case dir_output:
            m_module_ctrl->oe &= ~m_mask;
            break;
    }
}

void direct_pin::value(value_t value) {
    switch (value) {
        case value_low:
            m_module_ctrl->cleardataout |= m_mask;
            break;
        case value_high:
            m_module_ctrl->setdataout |= m_mask;
            break;
    }
}

}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::module_peripheral& module_peripheral) {
    os << "revision:" << std::endl
       << "\tminor=0x" << std::hex << module_peripheral->revision.bits.minor << std::endl
       << "\tcustom=0x" << std::hex << module_peripheral->revision.bits.custom << std::endl
       << "\tmajor=0x" << std::hex << module_peripheral->revision.bits.major << std::endl
       << "\trtl=0x" << std::hex << module_peripheral->revision.bits.rtl << std::endl
       << "\tfunc=0x" << std::hex << module_peripheral->revision.bits.func << std::endl
       << "\tscheme=0x" << std::hex << module_peripheral->revision.bits.scheme;

    return os;
}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::direct_pin& pin) {
    os
        << "\tdirection: " << pin.direction() << std::endl
        << "\tvalue: " << pin.value();

    return os;
}
