#pragma once

#include <cstdint>

#include "mem/peripheral.h"


namespace bbb::pwmss {

template<unsigned module, size_t address>
struct module_def {
    static constexpr unsigned MODULE = module;
    static constexpr size_t ADDRESS = address;
};

template<typename T>
struct is_module_def : std::false_type {};

template<unsigned module, size_t address>
struct is_module_def<module_def<module, address>> : std::true_type {};

using pwmss0 = module_def<0, 0x48300000>;
using pwmss1 = module_def<1, 0x48302000>;
using pwmss2 = module_def<2, 0x48304000>;

union iprevision {
    uint32_t data;
    struct {
        uint32_t y_minor : 6;
        uint32_t custom : 2;
        uint32_t x_major : 3;
        uint32_t r_rtl : 5;
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
    enum standby_mode_t {
        standby_mode_force = 0x0,
        standby_mode_no = 0x1,
        standby_mode_smart = 0x2,
        standby_mode_smart_wakeup = 0x3
    };

    uint32_t data;
    struct {
        uint32_t softreset : 1;
        uint32_t freeemu : 1;
        idle_mode_t idle_mode : 2;
        standby_mode_t standby_mode : 2;
    } bits;

    DEFINE_STRUCT_CTORS(sysconfig)
};
static_assert(sizeof(sysconfig) == 4, "sysconfig");

union clkconfig {
    uint32_t data;
    struct {
        uint32_t ecap_clk_en : 1;
        uint32_t ecap_clkstop_req : 1;
        uint32_t reserved0 : 2;
        uint32_t eqep_clk_en : 1;
        uint32_t eqep_clkstop_req : 1;
        uint32_t reserved1 : 2;
        uint32_t epwm_clk_en : 1;
        uint32_t epwm_clkstop_req : 1;
    } bits;

    DEFINE_STRUCT_CTORS(clkconfig)
};
static_assert(sizeof(clkconfig) == 4, "clkconfig");

union clkstatus {
    uint32_t data;
    struct {
        uint32_t ecap_clk_en_ack : 1;
        uint32_t ecap_clkstop_ack : 1;
        uint32_t reserved0 : 2;
        uint32_t eqep_clk_en_ack : 1;
        uint32_t eqep_clkstop_ack : 1;
        uint32_t reserved1 : 2;
        uint32_t epwm_clk_en_ack : 1;
        uint32_t epwm_clkstop_ack : 1;
    } bits;

    DEFINE_STRUCT_CTORS(clkstatus)
};
static_assert(sizeof(clkstatus) == 4, "clkstatus");

class module_peripheral : public peripheral {
public:
    static constexpr size_t MODULE_CTRL_SIZE = 0x1000;

    static constexpr size_t ECAP_OFFSET = 0x100;
    static constexpr size_t EQEP_OFFSET = 0x180;
    static constexpr size_t EPWM_OFFSET = 0x200;

    using register_idver = reg<0x0, iprevision>;
    using register_sysconfig = reg<0x4, sysconfig>;
    using register_clkconfig = reg<0x8, clkconfig>;
    using register_clkstatus = reg<0xc, clkstatus>;

    using register_epwm_tbctl = reg<EPWM_OFFSET + 0x0, uint16_t>;
    using register_epwm_tbsts = reg<EPWM_OFFSET + 0x2, uint16_t>;
    using register_epwm_tbphshr = reg<EPWM_OFFSET + 0x4, uint16_t>;
    using register_epwm_tbphs = reg<EPWM_OFFSET + 0x6, uint16_t>;
    using register_epwm_tbcnt = reg<EPWM_OFFSET + 0x8, uint16_t>;
    using register_epwm_tbprd = reg<EPWM_OFFSET + 0xa, uint16_t>;
    using register_epwm_cmpctl = reg<EPWM_OFFSET + 0xe, uint16_t>;
    using register_epwm_cmpahr = reg<EPWM_OFFSET + 0x10, uint16_t>;
    using register_epwm_cmpa = reg<EPWM_OFFSET + 0x12, uint16_t>;
    using register_epwm_cmpb = reg<EPWM_OFFSET + 0x14, uint16_t>;
    using register_epwm_aqctla = reg<EPWM_OFFSET + 0x16, uint16_t>;
    using register_epwm_aqctlb = reg<EPWM_OFFSET + 0x18, uint16_t>;
    using register_epwm_aqsfrc = reg<EPWM_OFFSET + 0x1a, uint16_t>;
    using register_epwm_aqcsfrc = reg<EPWM_OFFSET + 0x1c, uint16_t>;
    using register_epwm_dbctl = reg<EPWM_OFFSET + 0x1e, uint16_t>;
    using register_epwm_dbred = reg<EPWM_OFFSET + 0x20, uint16_t>;
    using register_epwm_dbfed = reg<EPWM_OFFSET + 0x22, uint16_t>;

    explicit module_peripheral(size_t address) noexcept;
    ~module_peripheral() override = default;
};

#ifdef MEM_GLOBAL_REGS
extern module_peripheral _global_pwmss_modules[];

template<
        typename T,
        typename std::enable_if<
                is_module_def<T>::value,
                bool>::type = 0
>
module_peripheral& module() {
    return _global_pwmss_modules[T::MODULE];
}
#endif

}
