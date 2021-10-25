#pragma once

#include "gpio_def.h"
#include "mem/peripheral.h"


namespace bbb::gpio {

template<unsigned module, size_t address>
struct module_def {
    static constexpr unsigned MODULE = module;
    static constexpr size_t ADDRESS = address;
};

template<typename T>
struct is_module_def : std::false_type {};

template<unsigned module, size_t address>
struct is_module_def<module_def<module, address>> : std::true_type {};

using gpio0 = module_def<0, 0x44e07000>;
using gpio1 = module_def<1, 0x4804c000>;
using gpio2 = module_def<2, 0x481ac000>;
using gpio3 = module_def<3, 0x481ae000>;

union iprevision {
    uint32_t data;
    struct {
        uint32_t minor : 6;
        uint32_t custom : 2;
        uint32_t major : 3;
        uint32_t rtl : 5;
        uint32_t func : 12;
        uint32_t reserved0 : 2;
        uint32_t scheme : 2;
    } bits;

    DEFINE_STRUCT_CTORS(iprevision)
};
static_assert(sizeof(iprevision) == 4, "iprevision");

union sysconfig {
    enum idle_mode_t {
        idle_mode_force = 0x0,
        idle_mode_no = 0x1,
        idle_mode_smart = 0x2,
        idle_mode_smart_wakeup = 0x3
    };

    uint32_t data;
    struct {
        uint32_t auto_idle : 1;
        uint32_t softreset : 1;
        uint32_t ena_wakeup : 1;
        uint32_t idle_mode : 2;
    } bits;

    DEFINE_STRUCT_CTORS(sysconfig)
};
static_assert(sizeof(sysconfig) == 4, "sysconfig");

union eoi {
    uint32_t data;
    struct {
        uint32_t dma_event_ack : 1;
    } bits;

    DEFINE_STRUCT_CTORS(eoi)
};
static_assert(sizeof(eoi) == 4, "eoi");

union ctrl {
    uint32_t data;
    struct {
        uint32_t disable_module : 1;
        uint32_t gating_ratio : 2;
    } bits;

    DEFINE_STRUCT_CTORS(ctrl)
};
static_assert(sizeof(ctrl) == 4, "ctrl");

union debouncingtime {
    uint32_t data;
    struct {
        uint32_t debouncingtime : 8;
    } bits;

    DEFINE_STRUCT_CTORS(debouncingtime)
};
static_assert(sizeof(debouncingtime) == 4, "debouncingtime");

class module_peripheral : public peripheral {
public:
    static constexpr size_t MODULE_CTRL_SIZE = 0x1000;

    using register_idver = reg<0x0, iprevision>;
    using register_sysconfig = reg<0x10, sysconfig>;
    using register_eoi = reg<0x20, eoi>;
    using register_irqstatus_raw0 = reg<0x24, uint32_t>;
    using register_irqstatus_raw1 = reg<0x28, uint32_t>;
    using register_irqstatus0 = reg<0x2c, uint32_t>;
    using register_irqstatus1 = reg<0x30, uint32_t>;
    using register_irqstatus_set0 = reg<0x34, uint32_t>;
    using register_irqstatus_set1 = reg<0x38, uint32_t>;
    using register_irqstatus_clr0 = reg<0x3c, uint32_t>;
    using register_irqstatus_clr1 = reg<0x40, uint32_t>;
    using register_irqwaken0 = reg<0x44, uint32_t>;
    using register_irqwaken1 = reg<0x48, uint32_t>;
    using register_sysstatus = reg<0x114, uint32_t>;
    using register_ctrl = reg<0x130, ctrl>;
    using register_oe = reg<0x134, uint32_t>;
    using register_datain = reg<0x138, uint32_t>;
    using register_dataout = reg<0x13c, uint32_t>;
    using register_leveldetect0 = reg<0x140, uint32_t>;
    using register_leveldetect1 = reg<0x144, uint32_t>;
    using register_risingdetect = reg<0x148, uint32_t>;
    using register_fallingdetect = reg<0x14c, uint32_t>;
    using register_debouncenable = reg<0x150, uint32_t>;
    using register_debouncingtime = reg<0x154, debouncingtime>;
    using register_cleardataout = reg<0x190, uint32_t>;
    using register_setdataout = reg<0x194, uint32_t>;

    explicit module_peripheral(size_t address) noexcept;
    module_peripheral(const module_peripheral& other) = delete;
    ~module_peripheral() override = default;
};

class direct_pin {
public:
    direct_pin(module_peripheral* module, unsigned mask);

    direction_t direction() const;
    edge_t edge() const;
    value_t value() const;

    void direction(direction_t direction);
    void edge(edge_t edge);
    void value(value_t value);

private:
    module_peripheral* m_module;
    unsigned m_mask;
};

#ifdef MEM_GLOBAL_REGS
extern module_peripheral _global_gpio_modules[];

template<
        typename T,
        typename std::enable_if<
                is_module_def<T>::value,
                bool>::type = 0
>
module_peripheral& module() {
    return _global_gpio_modules[T::MODULE];
}

template<
        typename T,
        typename std::enable_if<
                is_pin_def<T>::value,
                bool>::type = 0
>
direct_pin make_direct_pin() {
    return direct_pin(_global_gpio_modules + T::MODULE, 1u << T::INDEX);
}
#endif

}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::module_peripheral& module_peripheral);
std::ostream& operator<<(std::ostream& os, const bbb::gpio::direct_pin& pin);
