
add_library(bbb_usermode STATIC
        gpio_def.cpp
        sysfs/gpio.cpp
        mem/gpio.cpp
        mem/peripheral.cpp
        mem/pwmss.cpp
        mem/adctsc.cpp)
target_include_directories(bbb_usermode PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(bbb_usermode PUBLIC MEM_GLOBAL_REGS=1)
