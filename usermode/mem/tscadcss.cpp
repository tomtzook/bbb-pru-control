
#include "mem/tscadcss.h"


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
