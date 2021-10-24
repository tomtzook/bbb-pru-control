
add_library(bbb_usermode STATIC
        gpio_sysfs.cpp gpio_direct.cpp gpio_direct.h gpio_def.cpp)
target_include_directories(bbb_usermode PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(bbb_usermode PUBLIC GPIO_DIRECT_GLOBAL=1)
