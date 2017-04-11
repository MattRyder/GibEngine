cmake_minimum_required(VERSION 2.6)
project(Editor CXX)

set(EDITOR_INCLUDE_DIRS
  ${PROJECT_SOURCE_DIR}/include
  ${ENGINE_INCLUDE_DIRS}
  CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

include_directories(${EDITOR_INCLUDE_DIRS})

add_executable(GibEditor
  include/Editor.h
  include/Main.h
  src/Editor.cpp
  src/Main.cpp)
  
target_link_libraries(GibEditor GibEngine)

add_dependencies(GibEditor GibEngine)