cmake_minimum_required(VERSION 3.0)
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

find_package(GTest)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/xnet/include)

add_subdirectory(base)
include_directories(${PROJECT_SOURCE_DIR}/base)
add_subdirectory(xrpc)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

add_subdirectory(test)

add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty/spdlog)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/spdlog/include)

# message(STATUS "${PROJECT_BINARY_DIR}")
# message(STATUS "${PROJECT_SOURCE_DIR}")
# message(STATUS "${CMAKE_BINARY_DIR}")