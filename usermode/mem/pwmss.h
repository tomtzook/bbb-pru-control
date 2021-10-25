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
    enum idle_mode_t : uint32_t {
        idle_mode_force = 0x0,
        idle_mode_no = 0x1,
        idle_mode_smart = 0x2,
        idle_mode_smart_wakeup = 0x3
    };
    enum standby_mode_t : uint32_t {
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

union tbctl {
    enum ctr_mode_t : uint16_t {
        ctrmode_up_count = 0x0,
        ctrmode_down_count = 0x1,
        ctrmode_up_down_count = 0x2,
        ctrmode_stop_freeze = 0x3
    };
    enum syncosel_t : uint16_t {
        syncosel_epwm_x_sync = 0x0,
        syncosel_ctr_0 = 0x1,
        syncosel_ctr_cmpb = 0x2,
        syncosel_disable = 0x3
    };
    enum hspclkdiv_t : uint16_t {
        hspclkdiv_1 = 0x0,
        hspclkdiv_2 = 0x1,
        hspclkdiv_4 = 0x2,
        hspclkdiv_6 = 0x3,
        hspclkdiv_8 = 0x4,
        hspclkdiv_10 = 0x5,
        hspclkdiv_12 = 0x6,
        hspclkdiv_14 = 0x7,
    };
    enum clkdiv_t : uint16_t {
        clkdiv_1 = 0x0,
        clkdiv_2 = 0x1,
        clkdiv_4 = 0x2,
        clkdiv_8 = 0x3,
        clkdiv_16 = 0x4,
        clkdiv_32 = 0x5,
        clkdiv_64 = 0x6,
        clkdiv_128 = 0x7,
    };
    enum free_soft_t : uint16_t {
        free_soft_stop_next = 0x0,
        free_soft_stop_cycle = 0x1,
        free_soft_free_run = 0x2,
        free_soft_free_run1 = 0x3,
    };

    uint16_t data;
    struct {
        ctr_mode_t ctrmode : 2;
        uint16_t phsen : 1;
        uint16_t prdld : 1;
        syncosel_t syncosel : 2;
        uint16_t swsync : 1;
        hspclkdiv_t hspclkdiv : 3;
        clkdiv_t clkdiv : 3;
        uint16_t phsdir : 1;
        free_soft_t free_soft : 2;
    } bits;

    DEFINE_STRUCT_CTORS(tbctl)
};
static_assert(sizeof(tbctl) == 2, "tbctl");

union tbsts {
    uint16_t data;
    struct {
        uint16_t ctrdir : 1;
        uint16_t synci : 1;
        uint16_t ctrmax : 1;
    } bits;

    DEFINE_STRUCT_CTORS(tbsts)
};
static_assert(sizeof(tbsts) == 2, "tbsts");

union tbphshr {
    uint16_t data;
    struct {
        uint16_t reserved0 : 8;
        uint16_t tbphsh : 8;
    } bits;

    DEFINE_STRUCT_CTORS(tbphshr)
};
static_assert(sizeof(tbphshr) == 2, "tbphshr");

union cmpctl {
    enum active_ctr_mode_t : uint16_t {
        active_mode_load_0 = 0x0,
        active_mode_load_prd = 0x1,
        active_mode_load_either = 0x2,
        active_mode_load_freeze = 0x3,
    };

    uint16_t data;
    struct {
        active_ctr_mode_t load_a_mode : 2;
        active_ctr_mode_t load_b_mode : 2;
        uint16_t shdw_a_mode : 1;
        uint16_t shdw_b_mode : 1;
        uint16_t reserved0 : 1;
        uint16_t shdw_a_full : 1;
        uint16_t shdw_b_full : 1;
    } bits;

    DEFINE_STRUCT_CTORS(cmpctl)
};
static_assert(sizeof(cmpctl) == 2, "cmpctl");

union cmpahr {
    uint16_t data;
    struct {
        uint16_t reserved0 : 8;
        uint16_t cmpahr : 8;
    } bits;

    DEFINE_STRUCT_CTORS(cmpahr)
};
static_assert(sizeof(cmpahr) == 2, "cmpahr");

union aqctl {
    enum action_t : uint16_t {
        action_disabled = 0x0,
        action_clear = 0x1,
        action_set = 0x2,
        action_toggle = 0x3,
    };

    uint16_t data;
    struct {
        action_t zro : 2;
        action_t prd : 2;
        action_t cau : 2;
        action_t cad : 2;
        action_t cbu : 2;
        action_t cbd : 2;
    } bits;

    DEFINE_STRUCT_CTORS(aqctl)
};
static_assert(sizeof(aqctl) == 2, "aqctl");

union aqsfrc {
    enum action_t : uint16_t {
        action_disabled = 0x0,
        action_clear = 0x1,
        action_set = 0x2,
        action_toggle = 0x3,
    };
    enum active_reload_t : uint16_t {
        active_reload_0 = 0x0,
        active_reload_period = 0x1,
        active_reload_either = 0x2,
        active_reload_immediate = 0x3,
    };

    uint16_t data;
    struct {
        action_t actsfa : 2;
        uint16_t otsfa : 1;
        action_t actsfb : 2;
        uint16_t otsfb : 1;
        active_reload_t rldcsf : 2;
    } bits;

    DEFINE_STRUCT_CTORS(aqsfrc)
};
static_assert(sizeof(aqsfrc) == 2, "aqsfrc");

union aqscfrc {
    enum software_force_t : uint16_t {
        force_disabled = 0x0,
        force_low = 0x1,
        force_high = 0x2,
        force_software_disabled = 0x3,
    };

    uint16_t data;
    struct {
        software_force_t csfa : 2;
        software_force_t csfb : 2;
    } bits;

    DEFINE_STRUCT_CTORS(aqscfrc)
};
static_assert(sizeof(aqscfrc) == 2, "aqscfrc");

union dbctl {
    enum deadband_out_mode_t : uint16_t {
        deadband_out_bypassed = 0x0,
        deadband_out_disable_rising_delay = 0x1,
        deadband_out_disable_falling_delay = 0x2,
        deadband_out_enable_full = 0x3,
    };
    enum polarity_t : uint16_t {
        polarity_active_high = 0x0,
        polarity_alc = 0x1,
        polarity_ahc = 0x2,
        polarity_active_low = 0x3,
    };
    enum deadband_in_mode_t : uint16_t {
        deadband_in_a_both = 0x0,
        deadband_in_b_rise_a_fall = 0x1,
        deadband_in_a_rise_b_fall = 0x2,
        deadband_in_b_both = 0x3,
    };

    uint16_t data;
    struct {
        deadband_out_mode_t out_mode : 2;
        polarity_t polsel : 2;
        deadband_in_mode_t in_mode : 2;
    } bits;

    DEFINE_STRUCT_CTORS(dbctl)
};
static_assert(sizeof(dbctl) == 2, "dbctl");

union edge_delay {
    uint16_t data;
    struct {
        uint16_t del : 10;
    } bits;

    DEFINE_STRUCT_CTORS(edge_delay)
};
static_assert(sizeof(edge_delay) == 2, "edge_delay");

union tzsel {
    uint16_t data;
    struct {
        uint16_t cbcn : 8;
        uint16_t oshtn : 8;
    } bits;

    DEFINE_STRUCT_CTORS(tzsel)
};
static_assert(sizeof(tzsel) == 2, "tzsel");

union tzctl {
    enum action_t : uint16_t {
        action_high_impedance = 0x0,
        action_force_high = 0x1,
        action_force_low = 0x2,
        action_nothing = 0x3,
    };

    uint16_t data;
    struct {
        action_t tza : 2;
        action_t tzb : 2;
    } bits;

    DEFINE_STRUCT_CTORS(tzctl)
};
static_assert(sizeof(tzctl) == 2, "tzctl");

union tze_ctl0 {
    uint16_t data;
    struct {
        uint16_t reserved0 : 1;
        uint16_t cbc : 1;
        uint16_t ost : 1;
    } bits;

    DEFINE_STRUCT_CTORS(tze_ctl0)
};
static_assert(sizeof(tze_ctl0) == 2, "tze_ctl0");

union tze_ctl1 {
    uint16_t data;
    struct {
        uint16_t tint : 1;
        uint16_t cbc : 1;
        uint16_t ost : 1;
    } bits;

    DEFINE_STRUCT_CTORS(tze_ctl1)
};
static_assert(sizeof(tze_ctl1) == 2, "tze_ctl1");

union etsel {
    enum interrupt_sel_t : uint16_t {
        int_option_enable_equal_0 = 0x1,
        int_option_enable_equal_period = 0x2,
        int_option_enable_equal_cmpa_inc = 0x4,
        int_option_enable_equal_cmpa_dec = 0x5,
        int_option_enable_equal_cmpb_inc = 0x6,
        int_option_enable_equal_cmpb_dec = 0x7,
    };

    uint16_t data;
    struct {
        interrupt_sel_t intsel : 3;
        uint16_t inten : 1;
    } bits;

    DEFINE_STRUCT_CTORS(etsel)
};
static_assert(sizeof(etsel) == 2, "etsel");

union etps {
    enum period_sel_t : uint16_t {
        interrupt_generate_disable = 0x0,
        interrupt_generate_first_event = 0x1,
        interrupt_generate_second_event = 0x2,
        interrupt_generate_third_event = 0x3,
    };
    enum counter_register_t : uint16_t {
        register_no_event = 0x0,
        register_1_event = 0x1,
        register_2_event = 0x2,
        register_3_event = 0x3,
    };

    uint16_t data;
    struct {
        period_sel_t intprd : 2;
        counter_register_t intcnt : 2;
    } bits;

    DEFINE_STRUCT_CTORS(etps)
};
static_assert(sizeof(etps) == 2, "etps");

union intstatus {
    uint16_t data;
    struct {
        uint16_t ints;
    } bits;

    DEFINE_STRUCT_CTORS(intstatus)
};
static_assert(sizeof(intstatus) == 2, "intstatus");

union pcctl {
    enum pulse_width_t : uint16_t {
        pulse_width_1 = 0x0,
        pulse_width_2 = 0x1,
        pulse_width_3 = 0x2,
        pulse_width_4 = 0x3,
        pulse_width_16 = 0xf,
    };
    enum frequency_t : uint16_t {
        frequency_divide_1 = 0x0,
        frequency_divide_2 = 0x1,
        frequency_divide_3 = 0x2,
        frequency_divide_4 = 0x3,
        frequency_divide_5 = 0x4,
        frequency_divide_6 = 0x5,
        frequency_divide_7 = 0x6,
        frequency_divide_8 = 0x7,
    };
    enum duty_cycle_t : uint16_t {
        duty_1_8 = 0x0,
        duty_2_8 = 0x1,
        duty_3_8 = 0x2,
        duty_4_8 = 0x3,
        duty_5_8 = 0x4,
        duty_6_8 = 0x5,
        duty_7_8 = 0x6,
    };

    uint16_t data;
    struct {
        uint16_t chpen : 1;
        pulse_width_t oshtwth : 4;
        frequency_t chpfreq : 3;
        duty_cycle_t chpduty : 3;
    } bits;

    DEFINE_STRUCT_CTORS(pcctl)
};
static_assert(sizeof(pcctl) == 2, "pcctl");

union hrcnfg {
    enum edge_mode_t {
        edge_mode_disabled = 0x0,
        edge_mode_rising = 0x1,
        edge_mode_falling = 0x2,
        edge_mode_both = 0x3,
    };

    uint16_t data;
    struct {
        edge_mode_t edge_mode : 2;
        uint16_t cltmode : 1;
        uint16_t hrload : 1;
    } bits;

    DEFINE_STRUCT_CTORS(hrcnfg)
};
static_assert(sizeof(hrcnfg) == 2, "hrcnfg");

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

    using register_epwm_tbctl = reg<EPWM_OFFSET + 0x0, tbctl>;
    using register_epwm_tbsts = reg<EPWM_OFFSET + 0x2, tbsts>;
    using register_epwm_tbphshr = reg<EPWM_OFFSET + 0x4, tbphshr>;
    using register_epwm_tbphs = reg<EPWM_OFFSET + 0x6, uint16_t>;
    using register_epwm_tbcnt = reg<EPWM_OFFSET + 0x8, uint16_t>;
    using register_epwm_tbprd = reg<EPWM_OFFSET + 0xa, uint16_t>;
    using register_epwm_cmpctl = reg<EPWM_OFFSET + 0xe, cmpctl>;
    using register_epwm_cmpahr = reg<EPWM_OFFSET + 0x10, cmpahr>;
    using register_epwm_cmpa = reg<EPWM_OFFSET + 0x12, uint16_t>;
    using register_epwm_cmpb = reg<EPWM_OFFSET + 0x14, uint16_t>;
    using register_epwm_aqctla = reg<EPWM_OFFSET + 0x16, aqctl>;
    using register_epwm_aqctlb = reg<EPWM_OFFSET + 0x18, aqctl>;
    using register_epwm_aqsfrc = reg<EPWM_OFFSET + 0x1a, aqsfrc>;
    using register_epwm_aqcsfrc = reg<EPWM_OFFSET + 0x1c, aqscfrc>;
    using register_epwm_dbctl = reg<EPWM_OFFSET + 0x1e, dbctl>;
    using register_epwm_dbred = reg<EPWM_OFFSET + 0x20, edge_delay>;
    using register_epwm_dbfed = reg<EPWM_OFFSET + 0x22, edge_delay>;
    using register_epwm_tzsel = reg<EPWM_OFFSET + 0x24, tzsel>;
    using register_epwm_tzctl = reg<EPWM_OFFSET + 0x28, tzctl>;
    using register_epwm_tzeint = reg<EPWM_OFFSET + 0x2a, tze_ctl0>;
    using register_epwm_tzflg = reg<EPWM_OFFSET + 0x2c, tze_ctl1>;
    using register_epwm_tzclr = reg<EPWM_OFFSET + 0x2e, tze_ctl1>;

    using register_epwm_tzfrc = reg<EPWM_OFFSET + 0x30, tze_ctl0>;
    using register_epwm_etsel = reg<EPWM_OFFSET + 0x32, etsel>;
    using register_epwm_etps = reg<EPWM_OFFSET + 0x34, etps>;
    using register_epwm_etflg = reg<EPWM_OFFSET + 0x36, intstatus>;
    using register_epwm_etclr = reg<EPWM_OFFSET + 0x38, intstatus>;
    using register_epwm_etfrc = reg<EPWM_OFFSET + 0x3a, intstatus>;
    using register_epwm_pcctl = reg<EPWM_OFFSET + 0x3c, pcctl>;
    using register_epwm_hrcnfg = reg<EPWM_OFFSET + 0xc0, hrcnfg>;

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
