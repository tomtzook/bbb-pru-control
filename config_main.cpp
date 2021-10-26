#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <iostream>

#include <sysfs/gpio.h>
#include <mem/gpio.h>
#include <mem/pwmss.h>
#include <mem/adctsc.h>
#include <mem/cm_per.h>
#include <mem/control_module.h>
#include <mem/pruss.h>

#include <prurp.h>


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

static void set_pwm(bbb::pwmss::module_peripheral& module) {
    auto epwm = module.epwm();

    epwm->tbctl.bits.ctrmode = epwm->tbctl.ctrmode_stop_freeze;
    epwm->tbctl.bits.clkdiv = epwm->tbctl.clkdiv_1;
    epwm->tbctl.bits.hspclkdiv = epwm->tbctl.hspclkdiv_1;

    epwm->cmpa = 0;
    epwm->cmpb = 0;
    epwm->tbprd = 0;
    epwm->tbcnt = 0;
}

static void enable_pwm(bbb::pwmss::module_peripheral& module) {
    auto epwm = module.epwm();

    epwm->aqctla.data = 0x2 | (0x3 << 4);
    epwm->aqctlb.data = 0x2 | (0x3 << 8);
    epwm->tbcnt = 0;
    epwm->tbctl.data &= ~0x3;
}

static void run_pru(pru::rp::pru& pru) {
    if (pru.is_running()) {
        std::cout << "PRU is running. Stopping..." << std::endl;
        pru.stop();
    }

    std::cout << "Upload software..." << std::endl;
    pru.load_firmware("/tmp/pru_test");

    std::cout << "Starting PRU..." << std::endl;
    pru.start();
}

static void disable_pwm(bbb::pwmss::module_peripheral& module) {
    auto epwm = module.epwm();

    epwm->tbctl.data |= 0x3;
    epwm->aqctla.data = 0x1 | (0x3 << 4);
    epwm->aqctlb.data = 0x1 | (0x3 << 8);
    epwm->tbcnt = 0;
}

static void print(bbb::pruss::module_peripheral& prumem) {
    auto ctrl = prumem.data<bbb::pruss::module_peripheral::register_pru0ctrl>();
    auto pru0iram = prumem.data<bbb::pruss::module_peripheral::register_pru0iram>();
    auto sharedmem = prumem.data<bbb::pruss::module_peripheral::register_sharedram>();

    std::cout << "pru0 ctrl: " << std::endl
              << "\trunstate=0x" << std::hex << ctrl->ctrl.bits.runstate << std::endl
              << "\tpctr=0x" << std::hex << ctrl->sts.bits.pctr << std::endl
              << "\tcycle=0x" << std::hex << ctrl->cycle << std::endl
              << "\tpctr_rst_val=0x" << std::hex << ctrl->ctrl.bits.pctr_rst_val << std::endl
              << "\tsoft_rst_n=0x" << std::hex << ctrl->ctrl.bits.soft_rst_n << std::endl;

    std::cout << "iram:" << std::endl;
    for (int i = 0; i < 20; ++i) {
        std::cout << "0x" << std::hex << (int)pru0iram[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "sharedmem:" << std::endl;
    for (int i = 0; i < 20; ++i) {
        std::cout << "0x" << std::hex << (int)sharedmem[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    //auto led = bbb::gpio::make_sysfs_pin<bbb::gpio::usr3>();

    /*auto& gpio = bbb::gpio::module<bbb::gpio::gpio1>();
    std::cout << "GPIO: " << gpio << std::endl;

    auto usr3 = bbb::gpio::make_direct_pin<bbb::gpio::usr3>();
    test_led(usr3);*/

    /*auto& adctsc = bbb::adctsc::module<bbb::adctsc::adctscss>();
    std::cout << "ADC-TSC: " << std::endl << adctsc << std::endl;

    auto& pwmss0 = bbb::pwmss::module<bbb::pwmss::pwmss0>();
    std::cout << "PWMSS0: " << std::endl << pwmss0 << std::endl;*/

    /*auto& pwmss0 = bbb::pwmss::module<bbb::pwmss::pwmss0>();
    std::cout << "enable" << std::endl;
    enable_pwm(pwmss0);
    std::cout << "set" << std::endl;
    set_pwm(pwmss0);

    std::cout << "PWMSS0: " << std::endl << pwmss0 << std::endl;*/

    auto& prumem = bbb::pruss::module<bbb::pruss::pruicss>();

    pru::rp::pru pru(pru::rp::pru0);
    if (pru.is_running()) {
        pru.stop();
    }
    pru.load_firmware("/tmp/pru_test");
    //pru.start();

    bbb::pruss::pru mpru(prumem, 0);
    mpru.enable();

    usleep(5000);
    mpru.disable();
    print(prumem);
    usleep(500000);
    print(prumem);

    pru.stop();

    return 0;
}
