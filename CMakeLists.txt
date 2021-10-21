cmake_minimum_required(VERSION 3.20)
project(bbb-pru-uio-control C CXX)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")

set(CMAKE_CXX_STANDARD 17)

add_library(prussdrv STATIC
        am335x_pru_package/pru_sw/app_loader/interface/prussdrv.c
        )
target_include_directories(prussdrv PUBLIC
        am335x_pru_package/pru_sw/app_loader/include)

add_library(prussdrvcxx STATIC prussdrvcxx.cpp)
target_link_libraries(prussdrvcxx PUBLIC prussdrv)

add_executable(bbb_host_control_test control_main.cpp)
target_link_libraries(bbb_host_control_test PRIVATE prussdrvcxx)
