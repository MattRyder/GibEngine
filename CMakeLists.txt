cmake_minimum_required(VERSION 2.6)
project(GibEngine C CXX)

set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

option(BUILD_EDITOR "Builds the GibEditor" OFF)
option(BUILD_TESTS "Build the test suite" ON)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/include)


set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
 
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

if(MSVC)
  include(ListCombinations)
  include(MSVCStaticRuntime)
endif(MSVC)

add_subdirectory(Engine/)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(Tests/)
endif(BUILD_TESTS)

if(BUILD_EDITOR)
  add_subdirectory(Editor/)
endif(BUILD_EDITOR)