#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <iostream>
#include <fstream>
#include <vector>

#include <sysfs/gpio.h>
#include <mem/gpio.h>
#include <mem/pwmss.h>
#include <mem/adctsc.h>
#include <mem/cm_per.h>
#include <mem/control_module.h>
#include <mem/pruss.h>

#include <elf.h>
#include <cstring>


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

static void disable_pwm(bbb::pwmss::module_peripheral& module) {
    auto epwm = module.epwm();

    epwm->tbctl.data |= 0x3;
    epwm->aqctla.data = 0x1 | (0x3 << 4);
    epwm->aqctlb.data = 0x1 | (0x3 << 8);
    epwm->tbcnt = 0;
}

static void load_code_to_pru(bbb::pruss::pru& pru, const char* path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(file_size);
    file.read(buffer.data(), file_size);

    char code[1024] = {0};
    size_t code_idx = 0;
    char data[1024] = {0};
    size_t data_idx = 0;

    elf::image image(buffer.data());
    for (auto program : image.programs()) {
        if (program.flags().bits.execute) {
            memcpy(code + code_idx, program.data<char>(), program.size());
            code_idx += program.size();
        } else if (program.flags().bits.read || program.flags().bits.write) {
            memcpy(data + data_idx, program.data<char>(), program.size());
            data_idx += program.size();
        }
    }

    std::cout << "code" << std::endl;
    for (int i = 0; i < code_idx; ++i) {
        std::cout << "0x" << std::hex << (int)pru.iram<char>()[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "data" << std::endl;
    for (int i = 0; i < data_idx; ++i) {
        std::cout << "0x" << std::hex << (int)pru.dram<char>()[i] << " ";
    }
    std::cout << std::endl;

    memcpy((void*) pru.iram<char>(), code, code_idx);
    memcpy((void*) pru.dram<char>(), data, data_idx);
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

struct message {
    unsigned int count;
    bool overflow;
};

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
    bbb::pruss::pru pru(prumem, 0);

    pru.disable();
    pru.load_from_elf("/tmp/pru_test");
    pru.enable();

    std::cout << "PRU loaded" << std::endl;

    usleep(1000 * 1000 * 60);

    pru.disable();

    return 0;
}
