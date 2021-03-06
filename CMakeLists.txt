
# set the arm toolchain
set(CMAKE_TOOLCHAIN_FILE mbed-cmake/arm_toolchain.cmake)

cmake_minimum_required(VERSION 3.0.1)

project (NewZUZUMOUSE C CXX ASM)

# ------------------------------------------------------------------------------
# set the target processor and include settings for cmake

set(MBED_TARGET LPC1768)
#set(MBED_TARGET LPC11U24)
#set(MBED_TARGET RBLAB_NRF51822)

# ------------------------------------------------------------------------------
# will add the include dirs and link the lib
#set(USE_RTOS true)
#set(USE_NET true)
#set(USE_USB true)
#set(USE_DSP true)

# ------------------------------------------------------------------------------
# for installing an serial console
set(MBEDMOUNT /Volumes/MBED)
set(SERCON /dev/tty.usbmodem14202)


# ------------------------------------------------------------------------------
# build the executable
set(SOURCE_FILE
        main.cpp
        defines.h
        explore.cpp
        explore.h
        machine.h
        machine.cpp
        serial_utility.cpp
        )



set(BIN
  NewZUZUMOUSE
)

include(mbed-cmake/arm_mbed.cmake)


add_subdirectory(MSLMv3)

# ------------------------------------------------------------------------------
# build the executable


add_executable(${BIN} ${SOURCE_FILE} ${MBED_OBJECTS})
target_link_libraries(${BIN} ${MBED_LIBS} MSLMv3)
