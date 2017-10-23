cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(GibEngine C CXX)

set(CC gcc)
set(CXX clang)

# Enable C++11 support
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Required to gen. symbols for GDB
set(CMAKE_BUILD_TYPE Debug)

option(COPY_DEMO_ASSETS "Copies demo assets for the Editor" ON)
option(BUILD_EDITOR "Builds the GibEditor" ON)
option(BUILD_TESTS "Build the test suite" ON)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/include)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
 
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_subdirectory(Engine/)

if(BUILD_EDITOR)
  add_subdirectory(Editor/)
endif()

#if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(Tests/)
#endif()