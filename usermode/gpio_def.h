#pragma once

#include <ostream>


#define PIN_NUMBER(module, index) ((module) * 32 + (index))

// Defines for pins on GPIO0
#define P8_13 (23) // EHRPWM2B
#define P8_14 (26)
#define P8_17 (27)
#define P8_19 (22) // EHRPWM2A
#define P8_31 (10) // UART5_CTSN
#define P8_32 (11) // UART5_RTSN
#define P8_33 (9) // UART4_RTSN
#define P8_35 (8) // UART4_CTSN

#define P9_11 (30) // UART4_RXD
#define P9_13 (31) // UART4_TXD
#define P9_17 (5) // I2C1_SCL
#define P9_18 (4) // I2C1_SDA
#define P9_19 (13) // I2C2_SCL
#define P9_20 (12) // I2C2_SDA
#define P9_21 (3) // UART2_TXD
#define P9_22 (2) // UART2_RXD
#define P9_24 (15) // UART1_RXD
#define P9_26 (14) // UART1_RXD
#define P9_41A (20)
#define P9_42A (7)

// Defines for pins on GPIO1
#define P8_03 (6)
#define P8_04 (7)
#define P8_05 (2)
#define P8_06 (3)
#define P8_11 (13)
#define P8_12 (12)
#define P8_15 (15)
#define P8_16 (14)
#define P8_20 (31)
#define P8_21 (30)
#define P8_22 (5)
#define P8_23 (4)
#define P8_24 (1)
#define P8_25 (0)
#define P8_26 (29)

#define P9_12 (28)
#define P9_14 (18) // EHRPWM1A
#define P9_15 (16)
#define P9_16 (19) // EHRPWM1B
#define P9_23 (17)

#define USR0 (21)
#define USR1 (22)
#define USR2 (23)
#define USR3 (24)

// Defines for pins on GPIO2
#define P8_07 (2) // TIMER4
#define P8_08 (3) // TIMER7
#define P8_09 (5) // TIMER5
#define P8_10 (4) // TIMER6
#define P8_18 (1)
#define P8_27 (22)
#define P8_28 (24)
#define P8_29 (23)
#define P8_30 (25)
#define P8_34 (17) // UART3_RTSN
#define P8_36 (16) // UART3_CTSN
#define P8_37 (14) // UART5_TXD
#define P8_38 (15) // UART5_RXD
#define P8_39 (12)
#define P8_40 (13)
#define P8_41 (10)
#define P8_42 (11)
#define P8_43 (8)
#define P8_44 (9)
#define P8_45 (6)
#define P8_46 (7)

// Defines for pins on GPIO3
#define P9_25 (21)
#define P9_27 (19)
#define P9_28 (17) // SPI1_CS0
#define P9_29 (15) // SPI1_d0
#define P9_30 (16) // SPI1_D1
#define P9_31 (14) // SPI1_SCLK
#define P9_41B (20)
#define P9_42B (18)


namespace bbb::gpio {

enum direction_t {
    dir_input,
    dir_output
};

enum edge_t {
    edge_none,
    edge_rising,
    edge_falling,
    edge_both
};

enum value_t {
    value_low,
    value_high
};

class pin {
public:
    virtual direction_t direction() const = 0;
    virtual value_t value() const = 0;

    virtual void direction(direction_t direction) = 0;
    virtual void value(value_t value) = 0;
};

template<unsigned module, unsigned index>
struct pin_def {
    static constexpr unsigned MODULE = module;
    static constexpr unsigned INDEX = index;
    static constexpr unsigned NUMBER = PIN_NUMBER(module, index);
};

template<typename T>
struct is_pin_def : std::false_type {};

template<unsigned module, unsigned index>
struct is_pin_def<pin_def<module, index>> : std::true_type {};


using p8_13 = pin_def<0, P8_13>;
using p8_14 = pin_def<0, P8_14>;
using p8_17 = pin_def<0, P8_17>;
using p8_19 = pin_def<0, P8_19>;
using p8_31 = pin_def<0, P8_31>;
using p8_32 = pin_def<0, P8_32>;
using p8_33 = pin_def<0, P8_33>;
using p8_35 = pin_def<0, P8_35>;

using p9_11 = pin_def<0, P9_11>;
using p9_13 = pin_def<0, P9_13>;
using p9_17 = pin_def<0, P9_17>;
using p9_18 = pin_def<0, P9_18>;
using p9_19 = pin_def<0, P9_19>;
using p9_20 = pin_def<0, P9_20>;
using p9_21 = pin_def<0, P9_21>;
using p9_22 = pin_def<0, P9_22>;
using p9_24 = pin_def<0, P9_24>;
using p9_26 = pin_def<0, P9_26>;
using p9_41a = pin_def<0, P9_41A>;
using p9_42a = pin_def<0, P9_42A>;

using p8_03 = pin_def<1, P8_03>;
using p8_04 = pin_def<1, P8_04>;
using p8_05 = pin_def<1, P8_05>;
using p8_06 = pin_def<1, P8_06>;
using p8_11 = pin_def<1, P8_11>;
using p8_12 = pin_def<1, P8_12>;
using p8_15 = pin_def<1, P8_15>;
using p8_16 = pin_def<1, P8_16>;
using p8_20 = pin_def<1, P8_20>;
using p8_21 = pin_def<1, P8_21>;
using p8_22 = pin_def<1, P8_22>;
using p8_23 = pin_def<1, P8_23>;
using p8_24 = pin_def<1, P8_24>;
using p8_25 = pin_def<1, P8_25>;
using p8_26 = pin_def<1, P8_26>;

using p9_12 = pin_def<1, P9_12>;
using p9_14 = pin_def<1, P9_14>;
using p9_15 = pin_def<1, P9_15>;
using p9_16 = pin_def<1, P9_16>;
using p9_23 = pin_def<1, P9_23>;

using usr0 = pin_def<1, USR0>;
using usr1 = pin_def<1, USR1>;
using usr2 = pin_def<1, USR2>;
using usr3 = pin_def<1, USR3>;

using p8_07 = pin_def<2, P8_07>;
using p8_08 = pin_def<2, P8_08>;
using p8_09 = pin_def<2, P8_09>;
using p8_10 = pin_def<2, P8_10>;
using p8_18 = pin_def<2, P8_18>;
using p8_27 = pin_def<2, P8_27>;
using p8_28 = pin_def<2, P8_28>;
using p8_29 = pin_def<2, P8_29>;
using p8_30 = pin_def<2, P8_30>;
using p8_34 = pin_def<2, P8_34>;
using p8_36 = pin_def<2, P8_36>;
using p8_37 = pin_def<2, P8_37>;
using p8_38 = pin_def<2, P8_38>;
using p8_39 = pin_def<2, P8_39>;
using p8_40 = pin_def<2, P8_40>;
using p8_41 = pin_def<2, P8_41>;
using p8_42 = pin_def<2, P8_42>;
using p8_43 = pin_def<2, P8_43>;
using p8_44 = pin_def<2, P8_44>;
using p8_45 = pin_def<2, P8_45>;
using p8_46 = pin_def<2, P8_46>;

using p9_25 = pin_def<3, P9_25>;
using p9_27 = pin_def<3, P9_27>;
using p9_28 = pin_def<3, P9_28>;
using p9_29 = pin_def<3, P9_29>;
using p9_30 = pin_def<3, P9_30>;
using p9_31 = pin_def<3, P9_31>;
using p9_41b = pin_def<3, P9_41B>;
using p9_42b = pin_def<3, P9_42B>;

}

std::ostream& operator<<(std::ostream& os, const bbb::gpio::direction_t& dir);
std::ostream& operator<<(std::ostream& os, const bbb::gpio::edge_t& edge);
std::ostream& operator<<(std::ostream& os, const bbb::gpio::value_t& value);
