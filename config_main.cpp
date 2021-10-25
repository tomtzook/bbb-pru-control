#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <iostream>

#include <sysfs/gpio.h>
#include <mem/gpio.h>
#include <mem/pwmss.h>
#include <mem/adctsc.h>


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

    /*auto& gpio = bbb::gpio::module<bbb::gpio::gpio1>();
    std::cout << "GPIO: " << gpio << std::endl;

    auto usr3 = bbb::gpio::make_direct_pin<bbb::gpio::usr3>();
    test_led(usr3);*/

    auto& adctsc = bbb::adctsc::module<bbb::adctsc::adctscss>();
    std::cout << "ADC-TSC: " << std::endl << adctsc << std::endl;

    auto& pwmss0 = bbb::pwmss::module<bbb::pwmss::pwmss0>();
    std::cout << "PWMSS0: " << std::endl << pwmss0 << std::endl;

    return 0;
}
