
add_library(bbb_usermode STATIC
        gpio_sysfs.cpp)
target_include_directories(bbb_usermode PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
