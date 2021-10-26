
add_library(bbb_usermode STATIC
        gpio_def.cpp
        sysfs/gpio.cpp
        mem/gpio.cpp
        mem/peripheral.cpp
        mem/pwmss.cpp
        mem/adctsc.cpp mem/cm_per.cpp mem/cm_per.h mem/control_module.cpp mem/control_module.h mem/pruss.cpp mem/pruss.h)
target_include_directories(bbb_usermode PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(bbb_usermode PUBLIC MEM_GLOBAL_REGS=1)
target_link_libraries(bbb_usermode elf)
