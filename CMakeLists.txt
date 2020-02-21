
cmake_minimum_required (VERSION 2.6)

project (znamenkaTest)

if(UNIX AND NOT APPLE)
SET(LINUX true)
endif()

#SET(FreeBSD true)
SET(DFS true)
if(LINUX)
    set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.7/gcc_64)
    set(CMAKE_SHARED_LINKER_FLAGS "-Xlinker --export-dynamic -Xlinker -zdefs")
else()
    set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt/5.14.1/clang_64)
endif()


OPTION(MT_CORE_SERVICES_SINGLE_PLUGING "Build apps/core-plugins - all core plugins in one file" ON)
include_directories(corelib .
			mt_main 
			lib/jsoncpp-0.5.0/include
			)

include_directories(system /usr/local/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fPIC -g -ggdb3 ")
link_directories( /usr/local/lib)
IF(APPLE)
    SET(CMAKE_MACOSX_RPATH 1)
ENDIF()
SET(ENABLE_QT_GUI on)
SET(DISABLE_UPNP on)
SET(ENABLE_GTEST on)



SET(CAPS_IP "testquant.com")
#SET(CAPS_IP "127.0.0.1")
SET(PORT 10100)
SET(CLIENTPORT 10101)


IF(LINUX)
SET(DL "dl")
ENDIF()

SET(PROJECT_BASE_DIR ~/bin-Belyalov)
SET(PLUGIN_TARGET_DIR ${PROJECT_BASE_DIR}/plugin)
SET(BIN_TARGET_DIR ${PROJECT_BASE_DIR}/bin)
SET(LIB_TARGET_DIR ${PROJECT_BASE_DIR}/lib)
SET(LOG_TARGET_DIR ${PROJECT_BASE_DIR}/log)
SET(DATA_TARGET_DIR ${PROJECT_BASE_DIR}/data)
SET(CONFIG_TARGET_DIR ${PROJECT_BASE_DIR}/conf)
SET(CACHE_TARGET_DIR ${PROJECT_BASE_DIR}/cache)


CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/test_config.h.in"
                "${PROJECT_SOURCE_DIR}/test_config.h"
                NEWLINE_STYLE UNIX )


set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE )
#add_definitions(  -DDEBUG )
    add_definitions(  -DWITHOUT_UPNP -DREAL_DOUBLE)

find_library(GTest REQUIRED)

#ADD_SUBDIRECTORY(megatron)

    



add_subdirectory(corelib)
add_subdirectory(modules)
add_subdirectory(mt_lib)
add_subdirectory(peerObserver)
add_subdirectory(lib/jsoncpp-0.5.0/src/lib_json)


