project(MSLMv3)

set(MSLM_SOURCE
        Motor.h
        sensor.h
        deftype.h
        Motor.cpp
        sensor.cpp
        switch.h
        )

add_library(MSLM ${MSLM_SOURCE})

target_link_libraries(MSLM ${MBED_LIBS})