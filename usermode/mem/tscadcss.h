#pragma once

#include <cstdint>
#include <cstddef>
#include <type_traits>
#include "peripheral.h"


namespace bbb::adctsc {

template<unsigned module, size_t address>
struct module_def {
    static constexpr unsigned MODULE = module;
    static constexpr size_t ADDRESS = address;
};

template<typename T>
struct is_module_def : std::false_type {};

template<unsigned module, size_t address>
struct is_module_def<module_def<module, address>> : std::true_type {};

using adctscss = module_def<0, 0x44E0D000>;

#pragma pack(push, 1)

union adc_stepconfig {
    enum mode_t : uint32_t {
        mode_sw_enabled_oneshot = 0x0,
        mode_sw_enabled_continuous = 0x1,
        mode_hw_sync_oneshot = 0x2,
        mode_hw_sync_continuous = 0x3,
    };
    enum averaging_t : uint32_t {
        averaging_no = 0x0,
        averaging_2 = 0x1,
        averaging_4 = 0x2,
        averaging_8 = 0x3,
        averaging_16 = 0x4,
    };
    enum sel_rfp_t : uint32_t {
        sel_rfp_t_vdda_adc = 0x0,
        sel_rfp_t_vdda_xpul = 0x1,
        sel_rfp_t_vdda_ypll = 0x2,
        sel_rfp_t_vdda_vrefp = 0x3,
    };
    enum sel_inm_t : uint32_t {
        sel_inm_channel_1 = 0x0,
        sel_inm_channel_8 = 0x7,
        sel_inm_adcrefm = 0x8,
    };
    enum sel_inp_t : uint32_t {
        sel_inp_channel_1 = 0x0,
        sel_inp_channel_8 = 0x7,
        sel_inp_vrefn = 0x8,
    };
    enum sel_rfm_t : uint32_t {
        sel_rfm_vssa_adc = 0x0,
        sel_rfm_xnur = 0x1,
        sel_rfm_ynlr = 0x2,
        sel_rfm_vrefn = 0x3
    };

    volatile uint32_t data;
    volatile struct {
        mode_t mode : 2;
        averaging_t averaging : 3;
        uint32_t xppsw_swc : 1;
        uint32_t xnnsw_swc : 1;
        uint32_t yppsw_swc : 1;
        uint32_t ynnsw_swc : 1;
        uint32_t xnpsw_swc : 1;
        uint32_t ypnsw_swc : 1;
        uint32_t wpnsw_swc : 1;
        sel_rfp_t sel_rfp_swc_2_0 : 3;
        sel_inm_t sel_inm_swc_3_0 : 4;
        sel_inp_t sel_inp_swc_3_0 : 4;
        sel_rfm_t sel_rfm_swc_1_0 : 2;
        uint32_t diff_cntrl : 1;
        uint32_t fifo_select : 1;
        uint32_t range_check : 1;
    } bits;
};

union adc_stepdelay {
    volatile uint32_t data;
    volatile struct {
        uint32_t open_delay : 18;
        uint32_t reserved0 : 6;
        uint32_t sample_delay : 8;
    } bits;
};

union adc_fifocount {
    volatile uint32_t data;
    volatile struct {
        uint32_t words : 7;
    } bits;
};

union adc_fifothreshold {
    volatile uint32_t data;
    volatile struct {
        uint32_t level : 6;
    } bits;
};

union adc_dmareq {
    volatile uint32_t data;
    volatile struct {
        uint32_t dma_request_level : 6;
    } bits;
};

union adc_fifodata {
    volatile uint32_t data;
    volatile struct {
        uint32_t adcdata : 12;
        uint32_t reserved0 : 4;
        uint32_t adcchnlid : 4;
    } bits;
};

struct adc_registers {
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t y_minor : 6;
            uint32_t custom : 2;
            uint32_t x_major : 3;
            uint32_t r_rtl : 5;
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
            idle_mode_smart_wakeup = 0x3,
        };

        volatile uint32_t data;
        volatile struct {
            uint32_t reserved0 : 2;
            idle_mode_t idle_mode : 2;
        } bits;
    } sysconfig;
    uint8_t reserved1[0x10];
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t hw_pen_event_async : 1;
            uint32_t end_of_sequence : 1;
            uint32_t fifo0_threshold : 1;
            uint32_t fifo0_overrun : 1;
            uint32_t fifo0_underflow : 1;
            uint32_t fifo1_threshold : 1;
            uint32_t fifo1_overrun : 1;
            uint32_t fifo1_underflow : 1;
            uint32_t out_of_range : 1;
            uint32_t pen_up_event : 1;
            uint32_t pen_irq_sync : 1;
        } bits;
    } irqstatus_raw;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t hw_pen_event_async : 1;
            uint32_t end_of_sequence : 1;
            uint32_t fifo0_threshold : 1;
            uint32_t fifo0_overrun : 1;
            uint32_t fifo0_underflow : 1;
            uint32_t fifo1_threshold : 1;
            uint32_t fifo1_overrun : 1;
            uint32_t fifo1_underflow : 1;
            uint32_t out_of_range : 1;
            uint32_t pen_up_event : 1;
            uint32_t pen_irq_sync : 1;
        } bits;
    } irqstatus;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t hw_pen_event_async : 1;
            uint32_t end_of_sequence : 1;
            uint32_t fifo0_threshold : 1;
            uint32_t fifo0_overrun : 1;
            uint32_t fifo0_underflow : 1;
            uint32_t fifo1_threshold : 1;
            uint32_t fifo1_overrun : 1;
            uint32_t fifo1_underflow : 1;
            uint32_t out_of_range : 1;
            uint32_t pen_up_event : 1;
            uint32_t pen_irq_sync : 1;
        } bits;
    } irqenable_set;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t hw_pen_event_async : 1;
            uint32_t end_of_sequence : 1;
            uint32_t fifo0_threshold : 1;
            uint32_t fifo0_overrun : 1;
            uint32_t fifo0_underflow : 1;
            uint32_t fifo1_threshold : 1;
            uint32_t fifo1_overrun : 1;
            uint32_t fifo1_underflow : 1;
            uint32_t out_of_range : 1;
            uint32_t pen_up_event : 1;
            uint32_t pen_irq_sync : 1;
        } bits;
    } irqstatus_clr;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t wakeen0 : 1;
        } bits;
    } irqwakeup;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t enable_0 : 1;
            uint32_t enable_1 : 1;
        } bits;
    } dmaenable_set;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t enable_0 : 1;
            uint32_t enable_1 : 1;
        } bits;
    } dmaenable_clr;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t enable : 1;
            uint32_t step_id_tag : 1;
            uint32_t stepconfig_writeprotect_n_active_low : 1;
            uint32_t adc_bias_select : 1;
            uint32_t power_down : 1;
            uint32_t afe_pen_ctrl : 2;
            uint32_t touch_screen_enable : 1;
            uint32_t hw_event_mapping : 1;
            uint32_t hw_preempt : 1;
        } bits;
    } ctrl;
    volatile union {
        enum step_id_t : uint32_t {
            step_id_idle = 0x10,
            step_id_charge = 0x11,
            step_id_1 = 0x0,
            step_id_2 = 0x1,
            step_id_3 = 0x2,
            step_id_4 = 0x3,
            step_id_5 = 0x4,
            step_id_6 = 0x5,
            step_id_7 = 0x6,
            step_id_8 = 0x7,
            step_id_9 = 0x8,
            step_id_10 = 0x9,
            step_id_11 = 0xa,
            step_id_12 = 0xb,
            step_id_13 = 0xc,
            step_id_14 = 0xd,
            step_id_15 = 0xe,
            step_id_16 = 0xf,
        };

        volatile uint32_t data;
        volatile struct {
            step_id_t step_id : 5;
            uint32_t fsm_busy : 1;
            uint32_t pen_irq0 : 1;
            uint32_t pen_irq1 : 1;
        } bits;
    } adcstat;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t low_range_data : 12;
            uint32_t reserved0 : 4;
            uint32_t high_range_data : 12;
        } bits;
    } adcrange;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t adc_clkdiv : 16;
        } bits;
    } adc_clkdiv;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t afe_spare_input : 4;
            uint32_t afe_spare_output : 4;
        } bits;
    } adc_misc;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t ts_charge : 1;
            uint32_t step1 : 1;
            uint32_t step2 : 1;
            uint32_t step3 : 1;
            uint32_t step4 : 1;
            uint32_t step5 : 1;
            uint32_t step6 : 1;
            uint32_t step7 : 1;
            uint32_t step8 : 1;
            uint32_t step9 : 1;
            uint32_t step10 : 1;
            uint32_t step11 : 1;
            uint32_t step12 : 1;
            uint32_t step13 : 1;
            uint32_t step14 : 1;
            uint32_t step15 : 1;
            uint32_t step16 : 1;
        } bits;
    } stepenable;
    volatile union {
        enum sel_rfp_t : uint32_t {
            sel_rfp_t_vdda_adc = 0x0,
            sel_rfp_t_vdda_xpul = 0x1,
            sel_rfp_t_vdda_ypll = 0x2,
            sel_rfp_t_vdda_vrefp = 0x3,
        };
        enum sel_inm_t : uint32_t {
            sel_inm_channel_1 = 0x0,
            sel_inm_channel_8 = 0x7,
            sel_inm_adcrefm = 0x8,
        };
        enum sel_inp_t : uint32_t {
            sel_inp_channel_1 = 0x0,
            sel_inp_channel_8 = 0x7,
            sel_inp_vrefn = 0x8,
        };
        enum sel_rfm_t : uint32_t {
            sel_rfm_vssa_adc = 0x0,
            sel_rfm_xnur = 0x1,
            sel_rfm_ynlr = 0x2,
            sel_rfm_vrefn = 0x3
        };

        volatile uint32_t data;
        volatile struct {
            uint32_t reserved : 5;
            uint32_t xppsw_swc : 1;
            uint32_t xnnsw_swc : 1;
            uint32_t yppsw_swc : 1;
            uint32_t ynnsw_swc : 1;
            uint32_t xnpsw_swc : 1;
            uint32_t ypnsw_swc : 1;
            uint32_t wpnsw_swc : 1;
            sel_rfp_t sel_rfp_swc_2_0 : 3;
            sel_inm_t sel_inm_swc_3_0 : 4;
            sel_inp_t sel_inp_swc_3_0 : 4;
            sel_rfm_t sel_rfm_swc_1_0 : 2;
            uint32_t diff_cntrl : 1;
        } bits;
    } idleconfig;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t reserved : 5;
            uint32_t xppsw_swc : 1;
            uint32_t xnnsw_swc : 1;
            uint32_t yppsw_swc : 1;
            uint32_t ynnsw_swc : 1;
            uint32_t xnpsw_swc : 1;
            uint32_t ypnsw_swc : 1;
            uint32_t wpnsw_swc : 1;
            uint32_t sel_rfp_swc_2_0 : 3;
            uint32_t sel_inm_swc_3_0 : 4;
            uint32_t sel_inp_swc_3_0 : 4;
            uint32_t sel_rfm_swc_1_0 : 2;
            uint32_t diff_cntrl : 1;
        } bits;
    } ts_charge_stepconfig;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t open_delay : 18;
        } bits;
    } ts_charge_delay;
    volatile adc_stepconfig stepconfig1;
    volatile adc_stepdelay stepdelay1;
    volatile adc_stepconfig stepconfig2;
    volatile adc_stepdelay stepdelay2;
    volatile adc_stepconfig stepconfig3;
    volatile adc_stepdelay stepdelay3;
    volatile adc_stepconfig stepconfig4;
    volatile adc_stepdelay stepdelay4;
    volatile adc_stepconfig stepconfig5;
    volatile adc_stepdelay stepdelay5;
    volatile adc_stepconfig stepconfig6;
    volatile adc_stepdelay stepdelay6;
    volatile adc_stepconfig stepconfig7;
    volatile adc_stepdelay stepdelay7;
    volatile adc_stepconfig stepconfig8;
    volatile adc_stepdelay stepdelay8;
    volatile adc_stepconfig stepconfig9;
    volatile adc_stepdelay stepdelay9;
    volatile adc_stepconfig stepconfig10;
    volatile adc_stepdelay stepdelay10;
    volatile adc_stepconfig stepconfig11;
    volatile adc_stepdelay stepdelay11;
    volatile adc_stepconfig stepconfig12;
    volatile adc_stepdelay stepdelay12;
    volatile adc_stepconfig stepconfig13;
    volatile adc_stepdelay stepdelay13;
    volatile adc_stepconfig stepconfig14;
    volatile adc_stepdelay stepdelay14;
    volatile adc_stepconfig stepconfig15;
    volatile adc_stepdelay stepdelay15;
    volatile adc_stepconfig stepconfig16;
    volatile adc_stepdelay stepdelay16;
    volatile adc_fifocount fifo0count;
    volatile adc_fifothreshold fifo0threshold;
    volatile adc_dmareq dma0req;
    volatile adc_fifocount fifo1count;
    volatile adc_fifothreshold fifo1threshold;
    volatile adc_dmareq dma1req;
    volatile adc_fifodata fifo0data;
    volatile adc_fifodata fifo1data;
};

#pragma pack(pop)

class module_peripheral : public peripheral {
public:
    static constexpr size_t MODULE_CTRL_SIZE = 0x2000;

    using register_all = reg<0x0, adc_registers>;

    explicit module_peripheral(size_t address) noexcept;
    module_peripheral(const module_peripheral& other) = delete;
    ~module_peripheral() override = default;

    volatile adc_registers* adc() {
        return peripheral::data<register_all>();
    }

    const volatile adc_registers* adc() const {
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
