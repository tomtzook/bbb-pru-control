#pragma once

#include <cstddef>
#include <cstdint>

#include "mem/peripheral.h"


namespace bbb::cm {

template<unsigned module, size_t address>
struct module_def {
    static constexpr unsigned MODULE = module;
    static constexpr size_t ADDRESS = address;
};

template<typename T>
struct is_module_def : std::false_type {};

template<unsigned module, size_t address>
struct is_module_def<module_def<module, address>> : std::true_type {};

using cm = module_def<0, 0x44e10000>;

#pragma pack(push, 1)

// TODO: FILL SPECIFIC BIT INFORMATION
struct cm_registers {

};

#pragma pack(pop)

class module_peripheral : public peripheral {
public:
    static constexpr size_t MODULE_CTRL_SIZE = 0x2000;

    using register_all = reg<0x0, cm_registers>;
    using register_pwmss = reg<0x664, uint32_t>;

    explicit module_peripheral(size_t address) noexcept;
    module_peripheral(const module_peripheral& other) = delete;
    ~module_peripheral() override = default;

    volatile cm_registers* operator->() {
        return peripheral::data<register_all>();
    }

    const volatile cm_registers* operator->() const {
        return peripheral::data<register_all>();
    }

    volatile cm_registers* cm() {
        return peripheral::data<register_all>();
    }

    const volatile cm_registers* cm() const {
        return peripheral::data<register_all>();
    }
};

#ifdef MEM_GLOBAL_REGS
extern module_peripheral _global_modules[];

template<
        typename T,
        typename std::enable_if<
                is_module_def<T>::value,
                bool>::type = 0
>
module_peripheral& module() {
    return _global_modules[T::MODULE];
}
#endif

}
