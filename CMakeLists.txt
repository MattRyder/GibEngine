cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(GibEngine C CXX)

set(CC gcc)
set(CXX clang)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED on)

# Enable C++11 support
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)


option(COPY_DEMO_ASSETS "Copies demo assets for the Editor" ON)
option(BUILD_EDITOR "Builds the GibEditor" ON)
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

if(BUILD_EDITOR)
  add_subdirectory(Editor/)

  if(COPY_DEMO_ASSETS)
#	if(MSVC)
#		file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR}/Debug)
#	elseif(UNIX)
#		file(COPY Assets DESTINATION ${CMAKE_BINARY_DIR})
#	endif()
  endif()
endif()

#if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(Tests/)
#endif()