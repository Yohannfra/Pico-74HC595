cmake_minimum_required(VERSION 3.13)

#pull in pico SDK (must before project)
include(pico_sdk_import.cmake)

project(blinky_74hc595 C CXX ASM)

#initialize the SDK
pico_sdk_init()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME}
    main.c
    ../../src/74HC595.c
    )

#pull in our pico_stdib which pulls common
target_link_libraries(blinky_74hc595 pico_stdlib)

#create map/bin/hes file etc.
pico_add_extra_outputs(blinky_74hc595)
