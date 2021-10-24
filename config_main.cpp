#include <unistd.h>
#include <iostream>

#include <gpio_sysfs.h>


int main() {
    auto led = bbb::gpio::make_pin<bbb::gpio::usr3>();

    led.direction(bbb::gpio::dir_output);

    led.value(bbb::gpio::value_low);
    for (int i = 0; i < 10; ++i) {
        led.value(bbb::gpio::value_high);
        usleep(500000);
        led.value(bbb::gpio::value_low);
        usleep(500000);
    }

    return 0;
}
