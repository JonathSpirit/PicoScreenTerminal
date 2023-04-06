cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(picoScreenTerminal CXX C ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_library(${PROJECT_NAME}
    C_screen.cpp
    C_charBuffer.cpp
)

add_executable(exampleSnake
    main.cpp
)

target_link_libraries(${PROJECT_NAME} pico_stdlib)
target_link_libraries(exampleSnake ${PROJECT_NAME})

pico_add_extra_outputs(exampleSnake)
pico_enable_stdio_usb(exampleSnake 1)
pico_enable_stdio_uart(exampleSnake 0)