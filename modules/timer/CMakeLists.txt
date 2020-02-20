cmake_minimum_required (VERSION 2.6)

add_library(core-timer STATIC
    timerService.cpp
)

target_link_libraries(core-timer megatron-core pthread)

#install(TARGETS core-timer DESTINATION ${PLUGIN_TARGET_DIR})

