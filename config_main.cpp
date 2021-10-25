#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <iostream>

#include <sysfs/gpio.h>
#include <mem/gpio.h>
#include <mem/pwmss.h>


static void test_led(bbb::gpio::pin& led) {
    led.direction(bbb::gpio::dir_output);

    led.value(bbb::gpio::value_low);
    for (int i = 0; i < 10; ++i) {
        led.value(bbb::gpio::value_high);
        usleep(500000);
        led.value(bbb::gpio::value_low);
        usleep(500000);
    }
}

int main() {
    //auto led = bbb::gpio::make_sysfs_pin<bbb::gpio::usr3>();

    auto& gpio = bbb::gpio::module<bbb::gpio::gpio1>();
    std::cout << "GPIO: " << gpio << std::endl;

    auto usr3 = bbb::gpio::make_direct_pin<bbb::gpio::usr3>();
    test_led(usr3);

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

    /*auto& gpio = bbb::gpio::module<bbb::gpio::gpio0>();
    //auto sysconfig = gpio.data<bbb::gpio::module_peripheral::register_sysconfig>();


    {
        auto idver = gpio.data<bbb::gpio::module_peripheral::register_idver>();
        auto sysconfig = gpio.data<bbb::gpio::module_peripheral::register_sysconfig>();
        auto ctrl = gpio.data<bbb::gpio::module_peripheral::register_ctrl>();

        std::cout << "GPIO TEST" << std::endl
                << "idver: " << std::endl
                << "\tminor=" << std::hex << idver->bits.minor << std::endl
                << "\tcustom=" << std::hex << idver->bits.custom << std::endl
                << "\tmajor=" << std::hex << idver->bits.major << std::endl
                << "\trtl=" << std::hex << idver->bits.rtl << std::endl
                << "\tfunc=" << std::hex << idver->bits.func << std::endl
                << "\tscheme=" << std::hex << idver->bits.scheme << std::endl
                << "sysconfig:" << std::endl
                << "\tauto_idle=" << std::hex << sysconfig->bits.auto_idle << std::endl
                << "\tena_wakeup=" << std::hex << sysconfig->bits.ena_wakeup << std::endl
                << "\tena_wakeup=" << std::hex << sysconfig->bits.ena_wakeup << std::endl
                << "\tidle_mode=" << std::hex << sysconfig->bits.idle_mode << std::endl
                << "ctrl:" << std::endl
                << "\tdisable_module=" << std::hex << ctrl->bits.disable_module << std::endl
                << "\tgating_ratio=" << std::hex << ctrl->bits.gating_ratio << std::endl;
    }

    {
        auto all = gpio.data<bbb::gpio::module_peripheral::register_all>();

        std::cout << "GPIO TEST2" << std::endl
                  << "idver: " << std::endl
                  << "\tminor=" << std::hex << all->idver.bits.minor << std::endl
                  << "\tcustom=" << std::hex << all->idver.bits.custom << std::endl
                  << "\tmajor=" << std::hex << all->idver.bits.major << std::endl
                  << "\trtl=" << std::hex << all->idver.bits.rtl << std::endl
                  << "\tfunc=" << std::hex << all->idver.bits.func << std::endl
                  << "\tscheme=" << std::hex << all->idver.bits.scheme << std::endl
                  << "sysconfig:" << std::endl
                  << "\tauto_idle=" << std::hex << all->sysconfig.bits.auto_idle << std::endl
                  << "\tena_wakeup=" << std::hex << all->sysconfig.bits.ena_wakeup << std::endl
                  << "\tena_wakeup=" << std::hex << all->sysconfig.bits.ena_wakeup << std::endl
                  << "\tidle_mode=" << std::hex << all->sysconfig.bits.idle_mode << std::endl
                  << "ctrl:" << std::endl
                  << "\tdisable_module=" << std::hex << all->ctrl.bits.disable_module << std::endl
                  << "\tgating_ratio=" << std::hex << all->ctrl.bits.gating_ratio << std::endl;
    }

    std::cout << "GPIO0" << std::endl << gpio << std::endl;


    auto all = gpio.data<bbb::gpio::module_peripheral::register_all>();
    unsigned int mask = 1u << bbb::gpio::usr3::INDEX;

    std::cout << "mem=" << std::hex << (void*)all << std::endl;
    std::cout << "mem=" << std::hex << (void*)gpio.data<bbb::gpio::module_peripheral::register_all>() << std::endl;

    std::cout << "pin oe=" << std::hex << all->oe << std::endl;
    all->oe |= mask;
    std::cout << "pin oe=" << std::hex << all->oe << std::endl;
    all->oe &= ~mask;
    std::cout << "pin oe=" << std::hex << all->oe << std::endl;
    auto v = gpio.read_reg<bbb::gpio::module_peripheral::register_oe>();
    v |= mask;
    gpio.write_reg<bbb::gpio::module_peripheral::register_oe>(v);
    std::cout << "pin oe=" << std::hex << all->oe << std::endl;
    v = gpio.read_reg<bbb::gpio::module_peripheral::register_oe>();
    v &= ~mask;
    gpio.write_reg<bbb::gpio::module_peripheral::register_oe>(v);
    std::cout << "pin oe=" << std::hex << all->oe << std::endl;

    all->cleardataout |= mask;
    for (int i = 0; i < 10; ++i) {
        all->setdataout |= mask;
        std::cout
            << "pin datain=" << std::hex << all->datain
            << " dataout=" << std::hex << all->dataout << std::endl;

        usleep(500000);
        all->cleardataout |= mask;
        usleep(500000);
    }*/

    /*unsigned int mask = 1u << bbb::gpio::usr3::INDEX;
    auto& gpio = bbb::gpio::module<bbb::gpio::gpio1>();

    auto all = gpio.data<bbb::gpio::module_peripheral::register_all>();
    auto oe = gpio.data<bbb::gpio::module_peripheral::register_oe>();
    auto dataout = gpio.data<bbb::gpio::module_peripheral::register_dataout>();
    auto setdataout = gpio.data<bbb::gpio::module_peripheral::register_setdataout>();
    auto cleardataout = gpio.data<bbb::gpio::module_peripheral::register_cleardataout>();

    /*oe &= ~mask;
    *cleardataout |= mask;
    for (int i = 0; i < 10; ++i) {
        *setdataout |= mask;
        usleep(500000);
        *cleardataout |= mask;
        usleep(500000);
    }*/

    return 0;
}
