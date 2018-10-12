
# set the arm toolchain
set(CMAKE_TOOLCHAIN_FILE mbed-cmake/arm_toolchain.cmake)

cmake_minimum_required(VERSION 3.0.1)

project (newzuzumouse C CXX ASM)

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
set(SERCON /dev/tty.usbmodem1412)


# ------------------------------------------------------------------------------
# build the executable
set(SOURCE_FILE
        main.cpp
        new_zuzumouse.h
        defines.h
        explore.cpp
        explore.h)



set(BIN
  new_zuzumouse
)

include(mbed-cmake/arm_mbed.cmake)


add_subdirectory(MSLMv3)

# ------------------------------------------------------------------------------
# build the executable


add_executable(${BIN} ${SOURCE_FILE} ${MBED_OBJECTS})
target_link_libraries(${BIN} ${MBED_LIBS} MSLM)
