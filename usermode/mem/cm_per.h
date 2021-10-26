#pragma once

#include <cstddef>
#include <cstdint>

#include "mem/peripheral.h"


namespace bbb::cmper {

template<unsigned module, size_t address>
struct module_def {
    static constexpr unsigned MODULE = module;
    static constexpr size_t ADDRESS = address;
};

template<typename T>
struct is_module_def : std::false_type {};

template<unsigned module, size_t address>
struct is_module_def<module_def<module, address>> : std::true_type {};

using cmper = module_def<0, 0x44e00000>;

#pragma pack(push, 1)

// TODO: FILL SPECIFIC BIT INFORMATION
struct cmper_registers {
    volatile uint32_t l4ls_clkstctrl;
    volatile uint32_t l3s_clkstctrl;
    volatile uint32_t l3_clkstctrl;
    volatile uint32_t cpgmac0_clkctrl;
    volatile uint32_t lcdc_clkctrl;
    volatile uint32_t usb0_clkctrl;
    volatile uint32_t tptc0_clkctrl;
    volatile uint32_t emif_clkctrl;
    volatile uint32_t ocmcram_clkctrl;
    volatile uint32_t gpmc_clkctrl;
    volatile uint32_t mcasp0_clkctrl;
    volatile uint32_t uart5_clkctrl;
    volatile uint32_t mmc0_clkctrl;
    volatile uint32_t elm_clkctrl;
    volatile uint32_t i2c2_clkctrl;
    volatile uint32_t i2c1_clkctrl;
    volatile uint32_t spi0_clkctrl;
    volatile uint32_t spi1_clkctrl;
    volatile uint32_t l4ls_clkctrl;
    volatile uint32_t mcasp1_clkctrl;
    volatile uint32_t uart1_clkctrl;
    volatile uint32_t uart2_clkctrl;
    volatile uint32_t uart3_clkctrl;
    volatile uint32_t uart4_clkctrl;
    volatile uint32_t timer7_clkctrl;
    volatile uint32_t timer2_clkctrl;
    volatile uint32_t timer3_clkctrl;
    volatile uint32_t timer4_clkctrl;
    volatile uint32_t gpio1_clkctrl;
    volatile uint32_t gpio2_clkctrl;
    volatile uint32_t gpio3_clkctrl;
    volatile uint32_t tpcc_clkctrl;
    volatile uint32_t dcan0_clkctrl;
    volatile uint32_t dcan1_clkctrl;
    volatile uint32_t epwmss1_clkctrl;
    volatile union {
        enum module_mode_t {
            mode_disabled = 0x0,
            mode_enable = 0x2,
        };

        volatile uint32_t data;
        volatile struct {
            uint32_t module_mode : 2;
            uint32_t reserved0 : 14;
            uint32_t idlest : 2;
        } bits;
    } epwmss0_clkctrl;
    volatile uint32_t epwmss2_clkctrl;
    volatile uint32_t l3_instr_clkctrl;
    volatile uint32_t l3_clkctrl;
    volatile uint32_t ieee5000_clkctrl;
    volatile uint32_t pru_icss_clkctrl;
    volatile uint32_t timer5_clkctrl;
    volatile uint32_t timer6_clkctrl;
    volatile uint32_t mmc1_clkctrl;
    volatile uint32_t mmc2_clkctrl;
    volatile uint32_t tptc1_clkctrl;
    volatile uint32_t tptc2_clkctrl;
    volatile uint32_t spinklock_clkctrl;
    volatile uint32_t mailbox0_clkctrl;
    volatile uint32_t l4hs_clkstctrl;
    volatile uint32_t l4hs_clkctrl;
    volatile uint32_t ocpwp_l3_clkstctrl;
    volatile uint32_t ocpwp_clkctrl;
    volatile uint32_t pru_icss_clkstctrl;
    volatile uint32_t cpsw_clkstctrl;
    volatile uint32_t lcdc_clkstctrl;
    volatile uint32_t clkdiv32k_clkctrl;
    volatile uint32_t clk_24mhz_clkstctrl;
};

#pragma pack(pop)

class module_peripheral : public peripheral {
public:
    static constexpr size_t MODULE_CTRL_SIZE = 0x400;

    using register_all = reg<0x0, cmper_registers>;

    explicit module_peripheral(size_t address) noexcept;
    module_peripheral(const module_peripheral& other) = delete;
    ~module_peripheral() override = default;

    volatile cmper_registers* operator->() {
        return peripheral::data<register_all>();
    }

    const volatile cmper_registers* operator->() const {
        return peripheral::data<register_all>();
    }

    volatile cmper_registers* cm_per() {
        return peripheral::data<register_all>();
    }

    const volatile cmper_registers* cm_per() const {
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
