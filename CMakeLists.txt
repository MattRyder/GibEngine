cmake_minimum_required(VERSION 2.6)
project(GibEngine CXX)


option(BUILD_EDITOR "Builds the GibEditor" ON)
option(BUILD_TESTS "Build the test suite" OFF)

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
endif(BUILD_EDITOR)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(Tests/)
endif(BUILD_TESTS)