#pragma once

#include <cstdint>
#include <cstddef>

#include "peripheral.h"


/*
 * // 0x4A30_0000 512KB
 * 0x0000_0000Data8KB RAM0
 * 0x0000_2000Data8KB RAM1
 * 0x0001_0000SharedData12KBRAM2
 * 0x0002_0000INTC
 * 0x0002_2000PRU0Control
 * 0x0002_2400PRU0Debug
 * 0x0002_4000PRU1Control
 * 0x0002_4400PRU1Debug
 * 0x0002_6000CFG
 * 0x0002_8000UART0
 * 0x0002_A000Reserved
 * 0x0002_C000Reserved
 * 0x0002_E000IEP
 * 0x0003_0000eCAP0
 * 0x0003_2000MII_RT_CFG
 * 0x0003_2400MII_MDIO
 * 0x0003_4000PRU08KB IRAM
 * 0x0003_8000PRU18KB IRAM
 * 0x0004_0000Reserved
 */
namespace bbb::pruss {

template<unsigned module, size_t address>
struct module_def {
    static constexpr unsigned MODULE = module;
    static constexpr size_t ADDRESS = address;
};

template<typename T>
struct is_module_def : std::false_type {};

template<unsigned module, size_t address>
struct is_module_def<module_def<module, address>> : std::true_type {};

using pruicss = module_def<0, 0x4a300000>;

#pragma pack(push, 1)

struct pru_ctrl {
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t soft_rst_n : 1;
            uint32_t en : 1;
            uint32_t sleeping : 1;
            uint32_t ctr_en : 1;
            uint32_t reserved0 : 4;
            uint32_t single_step : 1;
            uint32_t reserved1 : 5;
            uint32_t reserved2 : 1;
            uint32_t runstate : 1;
            uint32_t pctr_rst_val : 16;
        } bits;
    } ctrl;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t pctr : 16;
        } bits;
    } sts;
    volatile uint32_t wakeup_en;
    volatile uint32_t cycle;
    volatile uint32_t stall;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t c24_blk_idx : 8;
            uint32_t reserved0 : 8;
            uint32_t c25_blk_idx : 8;
        } bits;
    } ctbir0;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t c26_blk_idx : 8;
            uint32_t reserved0 : 8;
            uint32_t c27_blk_idx : 8;
        } bits;
    } ctbir1;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t c28_pointer : 16;
            uint32_t c29_pointer : 16;
        } bits;
    } ctppr0;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t c30_pointer : 16;
            uint32_t c31_pointer : 16;
        } bits;
    } ctppr1;
};

#pragma pack(pop)

class module_peripheral : public peripheral {
public:
    static constexpr size_t MODULE_CTRL_SIZE = 0x80000;

    using register_pru0dram = reg<0x00000000, uint8_t>;
    using register_pru1dram = reg<0x00002000, uint8_t>;
    using register_sharedram = reg<0x00010000, uint8_t>;
    using register_intc = reg<0x00020000, uint8_t>;
    using register_pru0ctrl = reg<0x00022000, pru_ctrl>;
    using register_pru0debug = reg<0x00022400, uint8_t>;
    using register_pru1ctrl = reg<0x00024000, pru_ctrl>;
    using register_pru1debug = reg<0x00024400, uint8_t>;
    using register_cfg = reg<0x00026000, uint8_t>;
    using register_uart0 = reg<0x00028000, uint8_t>;
    using register_iep = reg<0x0002e000, uint8_t>;
    using register_ecap0 = reg<0x00030000, uint8_t>;
    using register_miirtcfg = reg<0x00032000, uint8_t>;
    using register_miimdio = reg<0x00032400, uint8_t>;
    using register_pru0iram = reg<0x00034000, uint8_t>;
    using register_pru1iram = reg<0x00038000, uint8_t>;

    explicit module_peripheral(size_t address) noexcept;
    module_peripheral(const module_peripheral& other) = delete;
    ~module_peripheral() override = default;
};

class pru {
public:
    pru(module_peripheral& module, unsigned num);

    template<typename T>
    volatile T* dram() {
        switch (m_num) {
            case 0: return access_register<T, module_peripheral::register_pru0dram>();
            case 1: return access_register<T, module_peripheral::register_pru1dram>();
            default: return nullptr;
        }
    }
    template<typename T>
    const volatile T* dram() const {
        switch (m_num) {
            case 0: return access_register<T, module_peripheral::register_pru0dram>();
            case 1: return access_register<T, module_peripheral::register_pru1dram>();
            default: return nullptr;
        }
    }

    template<typename T>
    volatile T* iram() {
        switch (m_num) {
            case 0: return access_register<T, module_peripheral::register_pru0iram>();
            case 1: return access_register<T, module_peripheral::register_pru1iram>();
            default: return nullptr;
        }
    }
    template<typename T>
    const volatile T* iram() const {
        switch (m_num) {
            case 0: return access_register<T, module_peripheral::register_pru0iram>();
            case 1: return access_register<T, module_peripheral::register_pru1iram>();
            default: return nullptr;
        }
    }

    template<typename T>
    volatile T* sharedmem() {
        return access_register<T, module_peripheral::register_sharedram>();
    }
    template<typename T>
    const volatile T* sharedmem() const {
        return access_register<T, module_peripheral::register_sharedram>();
    }

    void enable();
    void disable();

private:
    template<typename T, typename module_register>
    inline volatile T* access_register() {
        return reinterpret_cast<volatile T*>(m_module.data<module_register>());
    }
    template<typename T, typename module_register>
    inline const volatile T* access_register() const {
        return reinterpret_cast<const volatile T*>(m_module.data<module_register>());
    }

    volatile pru_ctrl* ctrl_reg();

    module_peripheral& m_module;
    unsigned m_num;
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
