

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
