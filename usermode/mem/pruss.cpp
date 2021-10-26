
#include "pruss.h"


namespace bbb::pruss {

#ifdef MEM_GLOBAL_REGS
module_peripheral _global_modules[] = {
        module_peripheral(pruicss::ADDRESS)
};
#endif

module_peripheral::module_peripheral(size_t address) noexcept
        : peripheral(address, MODULE_CTRL_SIZE)
{ }


pru::pru(module_peripheral& module, unsigned num)
    : m_module(module)
    , m_num(num) {
}

void pru::enable() {
    auto reg = ctrl_reg();
    reg->ctrl.data = 0;
    reg->ctrl.bits.en = 1;
}

void pru::disable() {
    auto reg = ctrl_reg();
    reg->ctrl.bits.en = 0;
}

volatile pru_ctrl* pru::ctrl_reg() {
    switch (m_num) {
        case 0: return m_module.data<module_peripheral::register_pru0ctrl>();
        case 1: return m_module.data<module_peripheral::register_pru1ctrl>();
        default: return nullptr;
    }
}

}
