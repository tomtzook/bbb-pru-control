
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
    auto registers = module_peripheral.gpio();

    os
        << "idver: " << std::endl
        << "\tminor=" << std::hex << registers->idver.bits.minor << std::endl
        << "\tcustom=" << std::hex << registers->idver.bits.custom << std::endl
        << "\tmajor=" << std::hex << registers->idver.bits.major << std::endl
        << "\trtl=" << std::hex << registers->idver.bits.rtl << std::endl
        << "\tfunc=" << std::hex << registers->idver.bits.func << std::endl
        << "\tscheme=" << std::hex << registers->idver.bits.scheme << std::endl
        << "sysconfig:" << std::endl
        << "\tauto_idle=" << std::hex << registers->sysconfig.bits.auto_idle << std::endl
        << "\tena_wakeup=" << std::hex << registers->sysconfig.bits.ena_wakeup << std::endl
        << "\tena_wakeup=" << std::hex << registers->sysconfig.bits.ena_wakeup << std::endl
        << "\tidle_mode=" << std::hex << registers->sysconfig.bits.idle_mode << std::endl
        << "ctrl:" << std::endl
        << "\tdisable_module=" << std::hex << registers->ctrl.bits.disable_module << std::endl
        << "\tgating_ratio=" << std::hex << registers->ctrl.bits.gating_ratio;

    return os;
}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::direct_pin& pin) {
    os
        << "\tdirection: " << pin.direction() << std::endl
        << "\tvalue: " << pin.value();

    return os;
}
