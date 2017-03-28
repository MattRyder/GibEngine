cmake_minimum_required(VERSION 2.6)
project(GibEngine.Editor CXX)

set(GibEngine_Editor_VERSION_MAJOR 1)
set(GibEngine_Editor_VERSION_MINOR 0)
set(GibEngine_Editor_VERSION_PATCH 0)

MESSAGE(STATUS "GibEngine is at the: " ${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE GibEditorInclude include/*.h)
file(GLOB_RECURSE GibEditorSource src/*.cpp)

add_executable(GibEngine.Editor ${GibEditorSource} ${GibEditorInclude})