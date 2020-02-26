cmake_minimum_required (VERSION 2.6)

add_executable(peerObserver.exe 
main.cpp


)
target_link_libraries(peerObserver.exe core-socket core-timer core-objectProxy mt_lib  megatron-core   pthread dl)

install(TARGETS peerObserver.exe DESTINATION ${BIN_TARGET_DIR})

