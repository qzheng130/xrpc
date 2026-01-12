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
 -Werror
 -Wconversion
 -Wno-unused-parameter
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 -std=c++17
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

# message(STATUS "项目构建目录: ${PROJECT_BINARY_DIR}")
# message(STATUS "顶级构建目录: ${CMAKE_BINARY_DIR}")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_VERBOSE_MAKEFILE off)

# find_package查找.cmake的默认查询路径有如下
# PATH
# CMAKE_PREFIX_PATH
# CMAKE_FRAMEWORK_PATH
# CMAKE_APPBUNDLE_PATH

# 用来查找第三方依赖包的 .cmake文件，并根据.cmake文件生成依赖包的头文件目录和库文件路径等
find_package(Boost REQUIRED COMPONENTS
  program_options
)
include_directories(${Boost_INCLUDE_DIRS})
# 打印Boost变量，Boost库头文件们路径、库文件们路径、库们、版本等
# get_property(pkg_vars DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VARIABLES)
# foreach(var ${pkg_vars})
#     if(var MATCHES "^Boost_")
#         message("${var} = ${${var}}")
#     endif()
# endforeach()

find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})
MESSAGE(${GTEST_INCLUDE_DIRS})
MESSAGE(${GTEST_BOTH_LIBRARIES})
MESSAGE(${GTEST_LIBRARIES})
MESSAGE(${GTEST_MAIN_LIBRARIES})

find_package(Protobuf)
if(PROTOBUF_FOUND)
  message(STATUS "found protobuf")
endif()


include_directories(${PROJECT_SOURCE_DIR})
# include_directories(base)
# include_directories(xrpc)

add_subdirectory(base)
add_subdirectory(xrpc)

string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

add_subdirectory(test)
