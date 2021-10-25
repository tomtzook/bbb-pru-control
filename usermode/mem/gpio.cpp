
#include "mem/gpio.h"


namespace bbb::gpio {

#ifdef MEM_GLOBAL_REGS
module_peripheral _global_gpio_modules[] = {
        module_peripheral(gpio0::ADDRESS),
        module_peripheral(gpio1::ADDRESS),
        module_peripheral(gpio2::ADDRESS),
        module_peripheral(gpio3::ADDRESS)
};
#endif

module_peripheral::module_peripheral(size_t address) noexcept
    : peripheral(address, MODULE_CTRL_SIZE) {
}

direct_pin::direct_pin(module_peripheral* module, unsigned mask)
    : m_module(module)
    , m_mask(mask) {
}

direction_t direct_pin::direction() const {
    auto value = m_module->read_reg<module_peripheral::register_oe>();
    if (value & m_mask) {
        return dir_input;
    } else {
        return dir_output;
    }
}

edge_t direct_pin::edge() const {
    return edge_none;
}

value_t direct_pin::value() const {
    unsigned int reg_value;
    switch (direction()) {
        case dir_input:
            reg_value = m_module->read_reg<module_peripheral::register_datain>();
            break;
        case dir_output:
            reg_value = m_module->read_reg<module_peripheral::register_dataout>();
            break;
    }

    return (reg_value & m_mask) ?
        value_high :
        value_low;
}

void direct_pin::direction(direction_t direction) {
    auto value = m_module->read_reg<module_peripheral::register_oe>();

    switch (direction) {
        case dir_input:
            value |= m_mask;
            m_module->write_reg<module_peripheral::register_oe>(value);
            break;
        case dir_output:
            value &= ~m_mask;
            m_module->write_reg<module_peripheral::register_oe>(value);
            break;
    }
}

void direct_pin::edge(edge_t edge) {

}

void direct_pin::value(value_t value) {
    unsigned int reg_value;

    switch (value) {
        case value_low:
            reg_value = m_module->read_reg<module_peripheral::register_cleardataout>();
            reg_value |= m_mask;
            m_module->write_reg<module_peripheral::register_cleardataout>(reg_value);
            break;
        case value_high:
            reg_value = m_module->read_reg<module_peripheral::register_setdataout>();
            reg_value |= m_mask;
            m_module->write_reg<module_peripheral::register_setdataout>(reg_value);
            break;
    }
}

}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::module_peripheral& module_peripheral) {
    auto idver = module_peripheral.read_reg<bbb::gpio::module_peripheral::register_idver>();
    auto sysconfig = module_peripheral.read_reg<bbb::gpio::module_peripheral::register_sysconfig>();
    auto ctrl = module_peripheral.read_reg<bbb::gpio::module_peripheral::register_ctrl>();

    os
        << "idver: " << std::endl
        << "\tminor=" << std::hex << idver.bits.minor << std::endl
        << "\tcustom=" << std::hex << idver.bits.custom << std::endl
        << "\tmajor=" << std::hex << idver.bits.major << std::endl
        << "\trtl=" << std::hex << idver.bits.rtl << std::endl
        << "\tfunc=" << std::hex << idver.bits.func << std::endl
        << "\tscheme=" << std::hex << idver.bits.scheme << std::endl
        << "sysconfig:" << std::endl
        << "\tauto_idle=" << std::hex << sysconfig.bits.auto_idle << std::endl
        << "\tena_wakeup=" << std::hex << sysconfig.bits.ena_wakeup << std::endl
        << "\tena_wakeup=" << std::hex << sysconfig.bits.ena_wakeup << std::endl
        << "\tidle_mode=" << std::hex << sysconfig.bits.idle_mode << std::endl
        << "ctrl:" << std::endl
        << "\tdisable_module=" << std::hex << ctrl.bits.disable_module << std::endl
        << "\tgating_ratio=" << std::hex << ctrl.bits.gating_ratio;

    return os;
}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::direct_pin& pin) {
    os
        << "\tdirection: " << pin.direction() << std::endl
        << "\tedge: " << pin.edge() << std::endl
        << "\tvalue: " << pin.value();

    return os;
}
