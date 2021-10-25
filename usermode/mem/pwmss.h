#pragma once

#include <cstdint>
#include <ostream>

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

#pragma pack(push, 1)

struct pwmss_registers {
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
    volatile union {
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

        volatile uint32_t data;
        volatile struct {
            uint32_t softreset : 1;
            uint32_t freeemu : 1;
            idle_mode_t idle_mode : 2;
            standby_mode_t standby_mode : 2;
        } bits;
    } sysconfig;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t ecap_clk_en : 1;
            uint32_t ecap_clkstop_req : 1;
            uint32_t reserved0 : 2;
            uint32_t eqep_clk_en : 1;
            uint32_t eqep_clkstop_req : 1;
            uint32_t reserved1 : 2;
            uint32_t epwm_clk_en : 1;
            uint32_t epwm_clkstop_req : 1;
        } bits;
    } clkconfig;
    volatile union {
        volatile uint32_t data;
        volatile struct {
            uint32_t ecap_clk_en_ack : 1;
            uint32_t ecap_clkstop_ack : 1;
            uint32_t reserved0 : 2;
            uint32_t eqep_clk_en_ack : 1;
            uint32_t eqep_clkstop_ack : 1;
            uint32_t reserved1 : 2;
            uint32_t epwm_clk_en_ack : 1;
            uint32_t epwm_clkstop_ack : 1;
        } bits;
    } clkstatus;
};

struct ecap_registers {
    volatile uint32_t tsctr;
    volatile uint32_t ctrphs;
    volatile uint32_t cap1;
    volatile uint32_t cap2;
    volatile uint32_t cap3;
    volatile uint32_t cap4;
    volatile union {
        enum prescale_t : uint16_t {
            prescale_divide_1 = 0x0,
            prescale_divide_2 = 0x1,
            prescale_divide_4 = 0x2,
            prescale_divide_6 = 0x3,
            prescale_divide_8 = 0x4,
            prescale_divide_10 = 0x5,
            prescale_divide_60 = 0x1e,
            prescale_divide_62 = 0x1f,
        };

        volatile uint16_t data;
        volatile struct {
            uint16_t cap1pol : 1;
            uint16_t ctrrst1 : 1;
            uint16_t cap2pol : 1;
            uint16_t ctrrst2 : 1;
            uint16_t cap3pol : 1;
            uint16_t ctrrst3 : 1;
            uint16_t cap4pol : 1;
            uint16_t ctrrst4 : 1;
            uint16_t caplden : 1;
            prescale_t prescale : 5;
            uint16_t free_soft : 2;
        } bits;
    } ecctl1;
    volatile union {
        enum stop_wrap_t : uint16_t {
            stop_wrap_1 = 0x0,
            stop_wrap_2 = 0x1,
            stop_wrap_3 = 0x2,
            stop_wrap_4 = 0x3,
        };
        enum synco_sel_t : uint16_t {
            synch_out_passthrough = 0x0,
            synch_out_prdeq = 0x1,
            synch_out_disable = 0x2,
            synch_out_disable1 = 0x3,
        };

        volatile uint16_t data;
        volatile struct {
            uint16_t cont_onesht : 1;
            stop_wrap_t stop_wrap : 2;
            uint16_t re_arm : 1;
            uint16_t tsctrstop : 1;
            uint16_t synci_en : 1;
            synco_sel_t synco_sel : 2;
            uint16_t swsync : 1;
            uint16_t cap_apwm : 1;
            uint16_t apwmpol : 1;
        } bits;
    } ecctl2;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t reserved0 : 1;
            uint16_t cevt1 : 1;
            uint16_t cevt2 : 1;
            uint16_t cevt3 : 1;
            uint16_t cevt4 : 1;
            uint16_t cntovf : 1;
            uint16_t prdeq : 1;
            uint16_t cmpeq : 1;
        } bits;
    } eceint;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t ecint : 1;
            uint16_t cevt1 : 1;
            uint16_t cevt2 : 1;
            uint16_t cevt3 : 1;
            uint16_t cevt4 : 1;
            uint16_t cntovf : 1;
            uint16_t prdeq : 1;
            uint16_t cmpeq : 1;
        } bits;

    } ecflag;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t ecint : 1;
            uint16_t cevt1 : 1;
            uint16_t cevt2 : 1;
            uint16_t cevt3 : 1;
            uint16_t cevt4 : 1;
            uint16_t cntovf : 1;
            uint16_t prdeq : 1;
            uint16_t cmpeq : 1;
        } bits;

    } ecclr;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t reserved0 : 1;
            uint16_t cevt1 : 1;
            uint16_t cevt2 : 1;
            uint16_t cevt3 : 1;
            uint16_t cevt4 : 1;
            uint16_t cntovf : 1;
            uint16_t prdeq : 1;
            uint16_t cmpeq : 1;
        } bits;
    } ecfrc;
    uint8_t reserved0[0x2a];
    volatile uint32_t revid;
};

struct eqep_registers {
    volatile uint32_t qposcnt;
    volatile uint32_t qposinit;
    volatile uint32_t qposmax;
    volatile uint32_t qposcmp;
    volatile uint32_t qposilat;
    volatile uint32_t qposslat;
    volatile uint32_t qposlat;
    volatile uint32_t qutmar;
    volatile uint32_t quprd;
    volatile uint32_t qwdtmr;
    volatile uint32_t qwdprd;
    volatile union {
        enum pos_counter_mode_t : uint16_t {
            count_mode_quadrature = 0x0,
            count_mode_direction = 0x1,
            count_mode_up_freq = 0x2,
            count_mode_down_freq = 0x3,
        };

        volatile uint16_t data;
        volatile struct {
            uint16_t reserved : 5;
            uint16_t qsp : 1;
            uint16_t qip : 1;
            uint16_t qbp : 1;
            uint16_t qap : 1;
            uint16_t igate : 1;
            uint16_t swap : 1;
            uint16_t xcr : 1;
            uint16_t spsel : 1;
            uint16_t soen : 1;
            pos_counter_mode_t qsrc : 2;
        } bits;
    } qdecctl;
    volatile union {
        enum counter_latch_t : uint16_t {
            latch_counter_rising = 0x1,
            latch_counter_falling = 0x2,
            latch_counter_index_marker = 0x3,
        };
        enum index_event_init_t : uint16_t {
            index_event_init_nothing = 0x0,
            index_event_init_nothing1 = 0x1,
            index_event_init_qepi_rising = 0x2,
            index_event_init_qepi_falling = 0x3,
        };
        enum strobe_event_init_t : uint16_t {
            strobe_event_init_nothing = 0x0,
            strobe_event_init_nothing1 = 0x1,
            strobe_event_init_qeps_rising = 0x2,
            strobe_event_init_qeps_direction = 0x3,
        };
        enum counter_reset_t : uint16_t {
            counter_reset_index_event = 0x0,
            counter_reset_max_pos = 0x1,
            counter_reset_first_index_event = 0x2,
            counter_reset_unit_time_event = 0x3,
        };
        enum emulation_ctrl_t : uint16_t {
            emulation_stop_immediately = 0x0,
            emulation_count_to_rollover = 0x1,
            emulation_unaffected = 0x2,
            emulation_unaffected1 = 0x3,
        };

        volatile uint16_t data;
        volatile struct {
            uint16_t wde : 1;
            uint16_t ute : 1;
            uint16_t qclm : 1;
            uint16_t phen : 1;
            counter_latch_t iel : 2;
            uint16_t sel : 1;
            uint16_t swi : 1;
            index_event_init_t iei : 2;
            strobe_event_init_t sei : 2;
            counter_reset_t pcrm : 2;
            emulation_ctrl_t free_soft : 2;
        } bits;
    } qepctl;
    volatile union {
        enum pos_event_prescaler_t : uint16_t {
            pos_prescaler_div_1 = 0x0,
            pos_prescaler_div_2 = 0x1,
            pos_prescaler_div_4 = 0x2,
            pos_prescaler_div_8 = 0x3,
            pos_prescaler_div_16 = 0x4,
            pos_prescaler_div_32 = 0x5,
            pos_prescaler_div_64 = 0x6,
            pos_prescaler_div_128 = 0x7,
            pos_prescaler_div_256 = 0x8,
            pos_prescaler_div_512 = 0x9,
            pos_prescaler_div_1024 = 0xa,
            pos_prescaler_div_2048 = 0xb,
        };
        enum cap_timer_prescaler_t : uint16_t {
            cap_prescaler_div_1 = 0x0,
            cap_prescaler_div_2 = 0x1,
            cap_prescaler_div_4 = 0x2,
            cap_prescaler_div_8 = 0x3,
            cap_prescaler_div_16 = 0x4,
            cap_prescaler_div_32 = 0x5,
            cap_prescaler_div_64 = 0x6,
            cap_prescaler_div_128 = 0x7,
        };

        volatile uint16_t data;
        volatile struct {
            pos_event_prescaler_t upps : 4;
            cap_timer_prescaler_t ccps : 3;
            uint16_t reserved0 : 8;
            uint16_t cen : 1;
        } bits;
    } qcapct;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t pcspw : 12;
            uint16_t pce : 1;
            uint16_t pcpol : 1;
            uint16_t pcload : 1;
            uint16_t pcshdw : 1;
        } bits;
    } qposctl;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t reserved0 : 1;
            uint16_t pce : 1;
            uint16_t phe : 1;
            uint16_t qdc : 1;
            uint16_t wto : 1;
            uint16_t pcu : 1;
            uint16_t pco : 1;
            uint16_t pcr : 1;
            uint16_t pcm : 1;
            uint16_t sel : 1;
            uint16_t iel : 1;
            uint16_t uto : 1;
        } bits;
    } qeint;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t qeint : 1;
            uint16_t pce : 1;
            uint16_t phe : 1;
            uint16_t qdc : 1;
            uint16_t wto : 1;
            uint16_t pcu : 1;
            uint16_t pco : 1;
            uint16_t pcr : 1;
            uint16_t pcm : 1;
            uint16_t sel : 1;
            uint16_t iel : 1;
            uint16_t uto : 1;
        } bits;
    } qflg;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t qeint : 1;
            uint16_t pce : 1;
            uint16_t phe : 1;
            uint16_t qdc : 1;
            uint16_t wto : 1;
            uint16_t pcu : 1;
            uint16_t pco : 1;
            uint16_t pcr : 1;
            uint16_t pcm : 1;
            uint16_t sel : 1;
            uint16_t iel : 1;
            uint16_t uto : 1;
        } bits;
    } qclr;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t reserved0 : 1;
            uint16_t pce : 1;
            uint16_t phe : 1;
            uint16_t qdc : 1;
            uint16_t wto : 1;
            uint16_t pcu : 1;
            uint16_t pco : 1;
            uint16_t pcr : 1;
            uint16_t pcm : 1;
            uint16_t sel : 1;
            uint16_t iel : 1;
            uint16_t uto : 1;
        } bits;
    } qfrc;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t pcef : 1;
            uint16_t fimf : 1;
            uint16_t cdef : 1;
            uint16_t coef : 1;
            uint16_t qdlf : 1;
            uint16_t qdf : 1;
            uint16_t fdf : 1;
            uint16_t upevnt : 1;
        } bits;
    } qepsts;
    volatile uint16_t qctmr;
    volatile uint16_t qcprd;
    volatile uint16_t qctmrlat;
    volatile uint16_t qcprdlat;
    uint8_t reserved0[0x18];
    volatile uint32_t revid;
};

struct epwm_registers {
    volatile union {
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

        volatile uint16_t data;
        volatile struct {
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
    } tbctl;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t ctrdir : 1;
            uint16_t synci : 1;
            uint16_t ctrmax : 1;
        } bits;
    } tbsts;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t reserved0 : 8;
            uint16_t tbphsh : 8;
        } bits;
    } tbphshr;
    volatile uint16_t tbphs;
    volatile uint16_t tbcnt;
    volatile uint16_t tbprd;
    volatile uint16_t reserved0;
    volatile union {
        enum active_ctr_mode_t : uint16_t {
            active_mode_load_0 = 0x0,
            active_mode_load_prd = 0x1,
            active_mode_load_either = 0x2,
            active_mode_load_freeze = 0x3,
        };

        volatile uint16_t data;
        volatile struct {
            active_ctr_mode_t load_a_mode : 2;
            active_ctr_mode_t load_b_mode : 2;
            uint16_t shdw_a_mode : 1;
            uint16_t shdw_b_mode : 1;
            uint16_t reserved0 : 1;
            uint16_t shdw_a_full : 1;
            uint16_t shdw_b_full : 1;
        } bits;
    } cmpctl;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t reserved0 : 8;
            uint16_t cmpahr : 8;
        } bits;
    } cmpahr;
    volatile uint16_t cmpa;
    volatile uint16_t cmpb;
    volatile union {
        enum action_t : uint16_t {
            action_disabled = 0x0,
            action_clear = 0x1,
            action_set = 0x2,
            action_toggle = 0x3,
        };

        volatile uint16_t data;
        volatile struct {
            action_t zro : 2;
            action_t prd : 2;
            action_t cau : 2;
            action_t cad : 2;
            action_t cbu : 2;
            action_t cbd : 2;
        } bits;
    } aqctla;
    volatile union {
        enum action_t : uint16_t {
            action_disabled = 0x0,
            action_clear = 0x1,
            action_set = 0x2,
            action_toggle = 0x3,
        };

        volatile uint16_t data;
        volatile struct {
            action_t zro : 2;
            action_t prd : 2;
            action_t cau : 2;
            action_t cad : 2;
            action_t cbu : 2;
            action_t cbd : 2;
        } bits;
    } aqctlb;
    volatile union {
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

        volatile uint16_t data;
        volatile struct {
            action_t actsfa : 2;
            uint16_t otsfa : 1;
            action_t actsfb : 2;
            uint16_t otsfb : 1;
            active_reload_t rldcsf : 2;
        } bits;
    } aqsfrc;
    volatile union {
        enum software_force_t : uint16_t {
            force_disabled = 0x0,
            force_low = 0x1,
            force_high = 0x2,
            force_software_disabled = 0x3,
        };

        volatile uint16_t data;
        volatile struct {
            software_force_t csfa : 2;
            software_force_t csfb : 2;
        } bits;
    } aqcsfrc;
    volatile union {
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

        volatile uint16_t data;
        volatile struct {
            deadband_out_mode_t out_mode : 2;
            polarity_t polsel : 2;
            deadband_in_mode_t in_mode : 2;
        } bits;
    } dbctl;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t del : 10;
        } bits;
    } dbred;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t del : 10;
        } bits;
    } dbfed;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t cbcn : 8;
            uint16_t oshtn : 8;
        } bits;
    } tzsel;
    volatile union {
        enum action_t : uint16_t {
            action_high_impedance = 0x0,
            action_force_high = 0x1,
            action_force_low = 0x2,
            action_nothing = 0x3,
        };

        volatile uint16_t data;
        volatile struct {
            action_t tza : 2;
            action_t tzb : 2;
        } bits;
    } tzctl;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t reserved0 : 1;
            uint16_t cbc : 1;
            uint16_t ost : 1;
        } bits;
    } tzeint;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t tint : 1;
            uint16_t cbc : 1;
            uint16_t ost : 1;
        } bits;
    } tzflg;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t tint : 1;
            uint16_t cbc : 1;
            uint16_t ost : 1;
        } bits;
    } tzclr;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t reserved0 : 1;
            uint16_t cbc : 1;
            uint16_t ost : 1;
        } bits;
    } tzfrc;
    volatile union {
        enum interrupt_sel_t : uint16_t {
            int_option_enable_equal_0 = 0x1,
            int_option_enable_equal_period = 0x2,
            int_option_enable_equal_cmpa_inc = 0x4,
            int_option_enable_equal_cmpa_dec = 0x5,
            int_option_enable_equal_cmpb_inc = 0x6,
            int_option_enable_equal_cmpb_dec = 0x7,
        };

        volatile uint16_t data;
        volatile struct {
            interrupt_sel_t intsel : 3;
            uint16_t inten : 1;
        } bits;
    } etsel;
    volatile union {
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

        volatile uint16_t data;
        volatile struct {
            period_sel_t intprd : 2;
            counter_register_t intcnt : 2;
        } bits;
    } etps;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t ints;
        } bits;
    } etflg;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t ints;
        } bits;
    } etclr;
    volatile union {
        volatile uint16_t data;
        volatile struct {
            uint16_t ints;
        } bits;
    } etfrc;
    volatile union {
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

        volatile uint16_t data;
        volatile struct {
            uint16_t chpen : 1;
            pulse_width_t oshtwth : 4;
            frequency_t chpfreq : 3;
            duty_cycle_t chpduty : 3;
        } bits;
    } pcctl;
    uint8_t reserved1[0x82];
    volatile union {
        enum edge_mode_t : uint16_t {
            edge_mode_disabled = 0x0,
            edge_mode_rising = 0x1,
            edge_mode_falling = 0x2,
            edge_mode_both = 0x3,
        };

        volatile uint16_t data;
        volatile struct {
            edge_mode_t edge_mode : 2;
            uint16_t cltmode : 1;
            uint16_t hrload : 1;
        } bits;
    } hrcnfg;
};

#pragma pack(pop)


class module_peripheral : public peripheral {
public:
    static constexpr size_t MODULE_CTRL_SIZE = 0x1000;

    using register_pwmss = reg<0x0, pwmss_registers>;
    using register_ecap = reg<0x100, ecap_registers>;
    using register_eqep = reg<0x180, eqep_registers>;
    using register_epwm = reg<0x200, epwm_registers>;

    explicit module_peripheral(size_t address) noexcept;
    ~module_peripheral() override = default;

    volatile pwmss_registers* operator->() {
        return peripheral::data<register_pwmss>();
    }

    const volatile pwmss_registers* operator->() const {
        return peripheral::data<register_pwmss>();
    }

    volatile pwmss_registers* pwmss() {
        return peripheral::data<register_pwmss>();
    }

    const volatile pwmss_registers* pwmss() const {
        return peripheral::data<register_pwmss>();
    }

    volatile ecap_registers* ecap() {
        return peripheral::data<register_ecap>();
    }

    const volatile ecap_registers* ecap() const {
        return peripheral::data<register_ecap>();
    }

    volatile eqep_registers* eqep() {
        return peripheral::data<register_eqep>();
    }

    const volatile eqep_registers* eqep() const {
        return peripheral::data<register_eqep>();
    }

    volatile epwm_registers* epwm() {
        return peripheral::data<register_epwm>();
    }

    const volatile epwm_registers* epwm() const {
        return peripheral::data<register_epwm>();
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

std::ostream& operator<<(std::ostream& os, const bbb::pwmss::module_peripheral& module_peripheral);
