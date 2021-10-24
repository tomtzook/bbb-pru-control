
#include <iostream>

#include <gpio_config.h>


int main() {
    auto pin = bbb::gpio::make_pin<bbb::gpio::p8_31>();

    pin.direction(bbb::gpio::dir_output);
    pin.value(bbb::gpio::value_low);

    std::cout << pin << std::endl;

    return 0;
}
