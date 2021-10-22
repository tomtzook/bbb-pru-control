

add_library(prurp STATIC
        prurp.cpp
        rpmsg.cpp)
target_include_directories(prurp PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(prurp pru_common)
