cmake_minimum_required(VERSION 3.13)

function (AddExample TARGET_NAME SOURCES)
    add_executable(${TARGET_NAME} ${SOURCES})
    target_link_libraries(${TARGET_NAME} ${PROJECT_NAME})

    pico_add_extra_outputs(${TARGET_NAME})
    pico_enable_stdio_usb(${TARGET_NAME} 1)
    pico_enable_stdio_uart(${TARGET_NAME} 0)
endfunction()

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(picoScreenTerminal CXX C ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_library(${PROJECT_NAME}
    sources/C_screen.cpp
    sources/C_charBuffer.cpp
)
target_link_libraries(${PROJECT_NAME} pico_stdlib)
target_include_directories(${PROJECT_NAME} PUBLIC includes)

AddExample(exampleSnake
    examples/theSnake/main.cpp
)
