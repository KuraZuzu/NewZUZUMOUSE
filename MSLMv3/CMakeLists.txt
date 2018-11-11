project(MSLMv3)

set(MSLM_SOURCE
        Motor.h
        Motor.cpp
        sensor.h
        deftype.h
        sensor.cpp
        switch.h
        vector.cpp
        block.h
        block.cpp
        )

add_library(MSLM ${MSLM_SOURCE})

target_link_libraries(MSLM ${MBED_LIBS})