#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <iostream>

#include <sysfs/gpio.h>
#include <mem/gpio.h>
#include <mem/pwmss.h>


int main() {
    //auto led = bbb::gpio::make_sysfs_pin<bbb::gpio::usr3>();
    /*auto led = bbb::gpio::make_direct_pin<bbb::gpio::usr3>();

    std::cout << led << std::endl;
    led.direction(bbb::gpio::dir_output);

    led.value(bbb::gpio::value_low);
    for (int i = 0; i < 10; ++i) {
        led.value(bbb::gpio::value_high);
        usleep(500000);
        led.value(bbb::gpio::value_low);
        usleep(500000);
    }*/

    /*auto& pwmss_module = bbb::pwmss::_global_pwmss_modules[0];
    //auto clk_status = pwmss_module.read_reg<bbb::pwmss::module_reg::register_clkstatus>();


    auto tbctl = pwmss_module.read_reg<bbb::pwmss::module_peripheral::register_epwm_tbctl>();
    std::cout << "TBCTL " << std::hex << tbctl << std::endl;
*/
    /*bbb::pwmss::clkstatus clk_status;
    clk_status.data = pwmss_module.read<uint32_t>(bbb::pwmss::module_peripheral::register_clkstatus::OFFSET);

    std::cout << "PWMSS0 CLKSTATUS: " << std::endl
            << "ecap_clk_en_ack=" << clk_status.bits.ecap_clk_en_ack << std::endl
            << "ecap_clkstop_ack=" << clk_status.bits.ecap_clkstop_ack << std::endl
            << "eqep_clk_en_ack=" << clk_status.bits.eqep_clk_en_ack << std::endl
            << "eqep_clkstop_ack=" << clk_status.bits.eqep_clkstop_ack << std::endl
            << "epwm_clk_en_ack=" << clk_status.bits.epwm_clk_en_ack << std::endl
            << "epwm_clkstop_ack=" << clk_status.bits.epwm_clkstop_ack << std::endl;*/

    auto& gpio = bbb::gpio::module<bbb::gpio::gpio0>();
    std::cout << "GPIO0" << std::endl << gpio << std::endl;

    return 0;
}
