
#include "mem/adctsc.h"


namespace bbb::adctsc {

#ifdef MEM_GLOBAL_REGS
module_peripheral _global_modules[] = {
        module_peripheral(adctscss::ADDRESS)
};
#endif

module_peripheral::module_peripheral(size_t address) noexcept
        : peripheral(address, MODULE_CTRL_SIZE)
{ }

}

std::ostream& operator<<(std::ostream& os, const bbb::adctsc::module_peripheral& module_peripheral) {
    os << "revision:" << std::endl
            << "\ty_minor=0x" << std::hex << module_peripheral->revision.bits.y_minor << std::endl
            << "\tcustom=0x" << std::hex << module_peripheral->revision.bits.custom << std::endl
            << "\tx_major=0x" << std::hex << module_peripheral->revision.bits.x_major << std::endl
            << "\tr_rtl=0x" << std::hex << module_peripheral->revision.bits.r_rtl << std::endl
            << "\tfunc=0x" << std::hex << module_peripheral->revision.bits.func << std::endl
            << "\tscheme=0x" << std::hex << module_peripheral->revision.bits.scheme;

    return os;
}
