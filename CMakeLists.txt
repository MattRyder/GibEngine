cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(GibEngine C CXX)

# Enable C++11 support
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EDITOR "Builds the GibEditor" ON)
option(BUILD_TESTS "Build the test suite" ON)

include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")

add_subdirectory(Engine/)

#if(BUILD_EDITOR)
#  add_subdirectory(Editor/)
#endif()

#if(BUILD_TESTS)
	add_subdirectory(Tests/)
#endif()