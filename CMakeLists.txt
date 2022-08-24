cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(lcd_i2c C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall)

# Initialize the SDK
pico_sdk_init()

add_executable(main main.c lcd_i2c.c)

# pull in common dependencies
target_link_libraries(main pico_stdlib hardware_i2c)

# create map/bin/hex file etc.
pico_add_extra_outputs(main)