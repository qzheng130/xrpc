cmake_minimum_required(VERSION 3.20)
project(xrpc)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# only build examples if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL "xrpc")
  option(BUILD_EXAMPLES "Build examples" ON)
endif()

set(CXX_FLAGS
 -g
 -DVALGRIND
 -DCHECK_PTHREAD_RETURN_VALUE
 -D_FILE_OFFSET_BITS=64
 -Wall
 -Wextra
#  -Werror
 -Wconversion
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 -std=c++20
 -rdynamic
 )

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  list(APPEND CXX_FLAGS "-Wno-null-dereference")
  list(APPEND CXX_FLAGS "-Wno-sign-conversion")
  list(APPEND CXX_FLAGS "-Wno-unused-local-typedef")
  list(APPEND CXX_FLAGS "-Wthread-safety")
  list(REMOVE_ITEM CXX_FLAGS "-rdynamic")
endif()
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_VERBOSE_MAKEFILE off)

find_package(Boost REQUIRED COMPONENTS
  program_options
)
# if(Boost_FOUND)
#     message(STATUS "Boost version: ${Boost_VERSION}")
#     message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
#     message(STATUS "Boost libraries: ${Boost_LIBRARIES}")
#     include_directories(${Boost_INCLUDE_DIRS})
# endif()
include_directories(${Boost_INCLUDE_DIRS})

find_package(Protobuf REQUIRED)
include_directories(${Protobuf_INCLUDE_DIRS})

#find_package(GTest)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/xnet/include)

add_subdirectory(base)
add_subdirectory(xrpc)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

#add_subdirectory(test)
#add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty/spdlog)
#include_directories(${PROJECT_SOURCE_DIR}/thirdparty/spdlog/include)
#add_subdirectory(thirdparty/googletest)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
#set(FETCHCONTENT_FULLY_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF) 
set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/deps)
include(FetchContent)

FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  # URL https://github.com/gabime/spdlog/archive/refs/tags/v1.11.0.tar.gz
  GIT_TAG v1.11.0  # stable
)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1  # stable
)
# for Windows user
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# download and config
FetchContent_MakeAvailable(spdlog googletest)
# deps info
message(STATUS "gtest include目录: ${gtest_SOURCE_DIR}/googletest/include")
message(STATUS "gmock include目录: ${gtest_SOURCE_DIR}/googlemock/include")
# fetchcontent info
message(STATUS "依赖项将下载到: ${FETCHCONTENT_BASE_DIR}")

# using target_link_libraries auto includes header files，no need additional "include_directories"
#include_directories(
#  ${spdlog_SOURCE_DIR}/include
#  ${gtest_SOURCE_DIR}/googletest/include
#  ${gtest_SOURCE_DIR}/googlemock/include
#)

# 启用测试
enable_testing()

# message(STATUS "${PROJECT_BINARY_DIR}")
# message(STATUS "${PROJECT_SOURCE_DIR}")
# message(STATUS "${CMAKE_BINARY_DIR}")
