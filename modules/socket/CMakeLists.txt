cmake_minimum_required (VERSION 2.6)

add_library(core-socket STATIC
    socketService.cpp
)

target_link_libraries(core-socket megatron-core pthread)

#install(TARGETS core-socket DESTINATION ${PLUGIN_TARGET_DIR})

