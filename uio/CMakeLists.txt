

add_library(prussdrv STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/am335x_pru_package/pru_sw/app_loader/interface/prussdrv.c
        )
target_include_directories(prussdrv PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/am335x_pru_package/pru_sw/app_loader/include
        )


add_library(pruuio STATIC
        prussdrvcxx.cpp)
target_include_directories(pruuio PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(pruuio PUBLIC
        pru_common
        prussdrv)
