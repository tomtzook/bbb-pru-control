

#include "mem/pwmss.h"


namespace bbb::pwmss {

#ifdef MEM_GLOBAL_REGS
module_peripheral _global_modules[] = {
        module_peripheral(pwmss0::ADDRESS),
        module_peripheral(pwmss1::ADDRESS),
        module_peripheral(pwmss2::ADDRESS)
};
#endif

module_peripheral::module_peripheral(size_t address) noexcept
    : peripheral(address, MODULE_CTRL_SIZE)
{ }

}

std::ostream& operator<<(std::ostream& os, const bbb::pwmss::module_peripheral& module_peripheral) {
    os << "revision:" << std::endl
       << "\ty_minor=0x" << std::hex << module_peripheral->revision.bits.y_minor << std::endl
       << "\tcustom=0x" << std::hex << module_peripheral->revision.bits.custom << std::endl
       << "\tx_major=0x" << std::hex << module_peripheral->revision.bits.x_major << std::endl
       << "\tr_rtl=0x" << std::hex << module_peripheral->revision.bits.r_rtl << std::endl
       << "\tfunc=0x" << std::hex << module_peripheral->revision.bits.func << std::endl
       << "\tscheme=0x" << std::hex << module_peripheral->revision.bits.scheme << std::endl;

    os << "sysconfig:" << std::endl
       << "\tsoftreset=0x" << std::hex << module_peripheral->sysconfig.bits.softreset << std::endl
       << "\tfreeemu=0x" << std::hex << module_peripheral->sysconfig.bits.freeemu << std::endl
       << "\tidle_mode=0x" << std::hex << module_peripheral->sysconfig.bits.idle_mode << std::endl
       << "\tstandby_mode=0x" << std::hex << module_peripheral->sysconfig.bits.standby_mode << std::endl;

    os << "clkstatus:" << std::endl
       << "\tecap_clk_en_ack=0x" << std::hex << module_peripheral->clkstatus.bits.ecap_clk_en_ack << std::endl
       << "\tecap_clkstop_ack=0x" << std::hex << module_peripheral->clkstatus.bits.ecap_clkstop_ack << std::endl
       << "\teqep_clk_en_ack=0x" << std::hex << module_peripheral->clkstatus.bits.eqep_clk_en_ack << std::endl
       << "\teqep_clkstop_ack=0x" << std::hex << module_peripheral->clkstatus.bits.eqep_clkstop_ack << std::endl
       << "\tepwm_clk_en_ack=0x" << std::hex << module_peripheral->clkstatus.bits.epwm_clk_en_ack << std::endl
       << "\tepwm_clkstop_ack=0x" << std::hex << module_peripheral->clkstatus.bits.epwm_clkstop_ack;

    return os;
}
