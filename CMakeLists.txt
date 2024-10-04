cmake_minimum_required(VERSION 3.15...3.25)

if(DEFINED DEBUG)
    message(STATUS "Building for DEBUG")
    add_definitions(-DDEBUG)
endif()

if(DEFINED RP2040)
    message(STATUS "Compiling for RP2040")
    add_definitions(-DRP2040)
    include(pico_sdk_import.cmake)
    include(pico_extras_import_optional.cmake)
elseif(DEFINED CH32X)
    message(STATUS "Compiling for CH32V003")
    add_definitions(-DCH32X)
else()
    message(STATUS "Nothing to do.")
endif()

project(picofusb302 C ASM CXX)


add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        -g
        )

add_executable(picofusb302 main.c)

if(DEFINED RP2040)
pico_sdk_init()

add_library(fusb302 STATIC fusb302.c)

target_link_libraries(fusb302 pico_stdlib hardware_i2c)


target_link_libraries(picofusb302 fusb302 pico_stdlib hardware_i2c)

pico_enable_stdio_usb(picofusb302 1)
pico_enable_stdio_uart(picofusb302 1)

pico_add_extra_outputs(picofusb302)
endif()