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

#pragma pack(push, 1)

struct gpio_registers {
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t minor : 6;
            uint32_t custom : 2;
            uint32_t major : 3;
            uint32_t rtl : 5;
            uint32_t func : 12;
            uint32_t reserved0 : 2;
            uint32_t scheme : 2;
        } bits;
    } revision;
    uint8_t reserved0[0xc];
    volatile union {
        enum idle_mode_t : uint32_t {
            idle_mode_force = 0x0,
            idle_mode_no = 0x1,
            idle_mode_smart = 0x2,
            idle_mode_smart_wakeup = 0x3
        };

        volatile uint32_t data;
        volatile struct {
            uint32_t auto_idle : 1;
            uint32_t softreset : 1;
            uint32_t ena_wakeup : 1;
            idle_mode_t idle_mode : 2;
        } bits;
    } sysconfig;
    uint8_t reserved1[0xc];
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t dma_event_ack : 1;
        } bits;
    } eoi;
    volatile uint32_t irqstatus_raw0;
    volatile uint32_t irqstatus_raw1;
    volatile uint32_t irqstatus0;
    volatile uint32_t irqstatus1;
    volatile uint32_t irqstatus_set0;
    volatile uint32_t irqstatus_set1;
    volatile uint32_t irqstatus_clr0;
    volatile uint32_t irqstatus_clr1;
    volatile uint32_t irqwaken0;
    volatile uint32_t irqwaken1;
    uint8_t reserved2[0xc8];
    volatile uint32_t sysstatus;
    uint8_t reserved3[0x18];
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t disable_module : 1;
            uint32_t gating_ratio : 2;
        } bits;
    } ctrl;
    volatile uint32_t oe;
    volatile uint32_t datain;
    volatile uint32_t dataout;
    volatile uint32_t leveldetect0;
    volatile uint32_t leveldetect1;
    volatile uint32_t risingdetect;
    volatile uint32_t fallingdetect;
    volatile uint32_t debouncingenable;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t debouncingtime : 8;
        } bits;
    } debouncingtime;
    uint8_t reserved5[0x38];
    volatile uint32_t cleardataout;
    volatile uint32_t setdataout;
};

#pragma pack(pop)

class module_peripheral : public peripheral {
public:
    static constexpr size_t MODULE_CTRL_SIZE = 0x1000;

    using register_all = reg<0x0, gpio_registers>;

    explicit module_peripheral(size_t address) noexcept;
    module_peripheral(const module_peripheral& other) = delete;
    ~module_peripheral() override = default;

    volatile gpio_registers* operator->() {
        return peripheral::data<register_all>();
    }

    const volatile gpio_registers* operator->() const {
        return peripheral::data<register_all>();
    }

    volatile gpio_registers* gpio() {
        return peripheral::data<register_all>();
    }

    const volatile gpio_registers* gpio() const {
        return peripheral::data<register_all>();
    }
};

class direct_pin : public pin {
public:
    direct_pin(module_peripheral& module, unsigned mask);

    direction_t direction() const override;
    value_t value() const override;

    void direction(direction_t direction) override;
    void value(value_t value) override;

private:
    volatile gpio_registers* m_module_ctrl;
    unsigned m_mask;
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

template<
        typename T,
        typename std::enable_if<
                is_pin_def<T>::value,
                bool>::type = 0
>
direct_pin make_direct_pin() {
    return direct_pin(_global_modules[T::MODULE], 1u << T::INDEX);
}
#endif

}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::module_peripheral& module_peripheral);
std::ostream& operator<<(std::ostream& os, const bbb::gpio::direct_pin& pin);
