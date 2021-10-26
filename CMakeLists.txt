cmake_minimum_required(VERSION 3.20)
project(bbb-pru-control C CXX)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(common)
add_subdirectory(rp)
add_subdirectory(uio)

add_subdirectory(usermode)

add_executable(uio_host_test uio_main.cpp)
target_link_libraries(uio_host_test PRIVATE pruuio)

add_executable(rp_host_test rp_main.cpp)
target_link_libraries(rp_host_test PRIVATE prurp)

add_executable(config_host_test config_main.cpp)
target_link_libraries(config_host_test PRIVATE bbb_usermode prurp)
