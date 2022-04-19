# Copyright (C) 2015 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 2.8)

set(PRJ_NAME HelloWorld)

set(CMAKE_VERBOSE_MAKEFILE on)

OPTION(USE_FILE "Set to OFF to disable file logging" OFF )
message(STATUS "USE_FILE is set to value: ${USE_FILE}")

OPTION(USE_CONSOLE "Set to OFF to disable console logging" OFF )
message(STATUS "USE_CONSOLE is set to value: ${USE_CONSOLE}")

IF(USE_FILE)
  add_definitions(-DUSE_FILE)
ENDIF(USE_FILE)
IF(USE_CONSOLE)
  add_definitions(-DUSE_CONSOLE)
ENDIF(USE_CONSOLE)

SET(MAX_LOG_LEVEL "DEBUG" CACHE STRING "maximum log level")
message(STATUS "MAX_LOG_LEVEL is set to value: ${MAX_LOG_LEVEL}")
add_definitions(-DCOMMONAPI_LOGLEVEL=COMMONAPI_LOGLEVEL_${MAX_LOG_LEVEL})

if (MSVC)
# Visual C++ is not always sure whether he is really C++
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_CRT_SECURE_NO_WARNINGS /EHsc /wd\\\"4503\\\"")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS /wd\\\"4503\\\"")
else()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -O0 -std=c++11 -D_GLIBCXX_USE_NANOSLEEP -DLINUX")
endif()

message(STATUS "Compiler options: ${CMAKE_CXX_FLAGS}") 

if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
       "Choose the type of build, options are: Debug Release." FORCE)
endif(NOT CMAKE_BUILD_TYPE)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

OPTION(USE_INSTALLED_COMMONAPI "Set to OFF to use the local (build tree) version of CommonAPI" ON)
message(STATUS "USE_INSTALLED_COMMONAPI is set to value: ${USE_INSTALLED_COMMONAPI}")

if ("${USE_INSTALLED_COMMONAPI}" STREQUAL "ON")
    FIND_PACKAGE(CommonAPI 3.1.12 REQUIRED CONFIG NO_CMAKE_PACKAGE_REGISTRY)
else()
    FIND_PACKAGE(CommonAPI 3.1.12 REQUIRED CONFIG NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH)
endif()

FIND_PACKAGE(CommonAPI-SomeIP REQUIRED CONFIG NO_SYSTEM_ENVIRONMENT_PATH NO_CMAKE_SYSTEM_PATH)
set(COMMONAPI_SomeIP_INCLUDE_DIRS "/home/seohyun/Workspace/someip/capicxx-someip-runtime-3.1.12.17/include")

message(STATUS "CommonAPI_CONSIDERED_CONFIGS: ${CommonAPI_CONSIDERED_CONFIGS}")
message(STATUS "COMMONAPI_INCLUDE_DIRS: ${COMMONAPI_INCLUDE_DIRS}")

message(STATUS "CommonAPI-SomeIP_CONSIDERED_CONFIGS: ${CommonAPI-SomeIP_CONSIDERED_CONFIGS}")
message(STATUS "COMMONAPI_SomeIP_INCLUDE_DIRS: ${COMMONAPI_SomeIP_INCLUDE_DIRS}")







get_filename_component(INI_FILE ./commonapi4someip.ini ABSOLUTE)

set(SOMEIP_COMMONAPI_CONFIG "COMMONAPI_CONFIG=${INI_FILE}")
#if ("${SOMEIP_VSOMEIP_JSON_FILE}" STREQUAL "")
#    set(SOMEIP_VSOMEIP_JSON_FILE "../vsomeip.json")
#endif()
#set(VSOMEIP_CONFIGURATION "VSOMEIP_CONFIGURATION=${SOMEIP_VSOMEIP_JSON_FILE}")
set(SOMEIP_TEST_ENVIRONMENT
    ${SOMEIP_COMMONAPI_CONFIG}
    #${VSOMEIP_CONFIGURATION}
)










# CommonAPI
include(FindPkgConfig)
###############################################################################
# SOME/IP
find_package (CommonAPI-SomeIP 3.1.12 REQUIRED)
find_package (vsomeip REQUIRED)

# Source Files
set(PRJ_SRC_PATH src)
set(PRJ_SRC_GEN_PATH src-gen)
set(PRJ_SRC_GEN_COMMONAPI_PATH ${PRJ_SRC_GEN_PATH}/core/v1/commonapi)
set(PRJ_SRC_GEN_COMMONAPI_SOMEIP_PATH ${PRJ_SRC_GEN_PATH}/someip/v1/commonapi)

set(PRJ_NAME_CLIENT ${PRJ_NAME}Client)
set(PRJ_NAME_SERVICE ${PRJ_NAME}Service)

# Application
FILE(GLOB PRJ_PROXY_GEN_SRCS ${PRJ_SRC_GEN_COMMONAPI_PATH}/*Proxy.cpp)
FILE(GLOB PRJ_STUB_GEN_SRCS ${PRJ_SRC_GEN_COMMONAPI_PATH}/*Stub*.cpp)
FILE(GLOB PRJ_STUB_IMPL_SRCS ${PRJ_SRC_COMMONAPI_PATH}/*Stub*.cpp)
# SOME/IP library
FILE(GLOB PRJ_SOMEIP_LIB_SRCS ${PRJ_SRC_GEN_COMMONAPI_SOMEIP_PATH}/*.cpp)
set(PRJ_CLIENT_SRCS ${PRJ_SRC_PATH}/${PRJ_NAME_CLIENT}.cpp ${PRJ_PROXY_GEN_SRCS} ${PRJ_SOMEIP_LIB_SRCS})
set(PRJ_SERVICE_SRCS ${PRJ_SRC_PATH}/${PRJ_NAME_SERVICE}.cpp ${PRJ_SRC_PATH}/${PRJ_NAME}StubImpl.cpp ${PRJ_STUB_GEN_SRCS} ${PRJ_STUB_IMPL_SRCS} ${PRJ_SOMEIP_LIB_SRCS})

# Boost
find_package( Boost 1.54 COMPONENTS system thread log REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )




include_directories(
    src-gen/core
    src-gen/someip
    ${COMMONAPI_INCLUDE_DIRS}
    ${COMMONAPI_SOMEIP_INCLUDE_DIRS}
    ${VSOMEIP_INCLUDE_DIRS}
)

link_directories(
    ${COMMONAPI_LIBDIR}/build
    ${COMMONAPI_SOMEIP_CMAKE_DIR}/build
    ${Boost_LIBRARY_DIR}
)

if (MSVC)
  set(LINK_LIBRARIES CommonAPI CommonAPI-SomeIP)
else()
  set(LINK_LIBRARIES CommonAPI CommonAPI-SomeIP)
endif()


# Build SOME/IP library
#add_library (${PRJ_NAME}-someip SHARED ${PRJ_SOMEIP_LIB_SRCS})
#target_link_libraries(${PRJ_NAME}-someip CommonAPI-SomeIP)


# Build Client
add_executable(${PRJ_NAME_CLIENT} ${PRJ_CLIENT_SRCS})
#set_property(TARGET APPEND PROPERTY ENVIRONMENT ${SOMEIP_TEST_ENVIRONMENT})
target_link_libraries(${PRJ_NAME_CLIENT} ${LINK_LIBRARIES} ${PRJ_NAME}-someip)

# Build service
add_executable(${PRJ_NAME_SERVICE} ${PRJ_SERVICE_SRCS})
#set_property(TARGET APPEND PROPERTY ENVIRONMENT ${SOMEIP_TEST_ENVIRONMENT})
target_link_libraries(${PRJ_NAME_SERVICE} ${LINK_LIBRARIES} ${PRJ_NAME}-someip) 
