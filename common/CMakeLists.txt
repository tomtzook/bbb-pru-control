
add_library(pru_common STATIC
        pru.cpp)
target_include_directories(pru_common PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
