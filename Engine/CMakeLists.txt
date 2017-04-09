cmake_minimum_required(VERSION 2.6)
project(GibEngine C CXX)

set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

set(ENGINE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

####################################################
#	PROJECT DEPENDENCIES
####################################################
include(ExternalProject)
ExternalProject_Add(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 999f3556fdd80983b10051746264489f2cb1ef16
  CMAKE_ARGS
    -DGLFW_BUILD_EXAMPLES=OFF
    -DGLFW_BUILD_TESTS=OFF
    -DGLFW_BUILD_DOCS=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/glfw
)
ExternalProject_Get_Property(glfw source_dir)
list(APPEND ENGINE_INCLUDE_DIRS ${source_dir}/include)

ExternalProject_Add(spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog
  GIT_TAG 93d84e5d594b15be0abef4998cdd1a5be72db476
  CMAKE_ARGS
    -DSPDLOG_BUILD_TESTING=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/spdlog
)
ExternalProject_Get_Property(spdlog source_dir)
list(APPEND ENGINE_INCLUDE_DIRS ${source_dir}/include)

ExternalProject_Add(glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG 5dcc56489e1b66dfd5bca751fa9b8dc68059e008
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/glm
)
ExternalProject_Get_Property(glm source_dir)
list(APPEND ENGINE_INCLUDE_DIRS ${source_dir})

ExternalProject_Add(assimp
  GIT_REPOSITORY https://github.com/assimp/assimp
  GIT_TAG a8673d4828df5107186f49e5e4efa5316b727482
  CMAKE_ARGS
    -DASSIMP_BUILD_ASSIMP_TOOLS=OFF
    -DASSIMP_BUILD_TESTS=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/assimp
)
ExternalProject_Get_Property(assimp source_dir)
list(APPEND ENGINE_INCLUDE_DIRS ${source_dir}/include)

set(GibEngine_VERSION_MAJOR 1)
set(GibEngine_VERSION_MINOR 0)
set(GibEngine_VERSION_PATCH 0)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

set(ENGINE_INCLUDE_DIRS ${ENGINE_INCLUDE_DIRS}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

include_directories(${ENGINE_INCLUDE_DIRS})

add_library(GibEngine
  include/CameraBase.h
  include/Entity.h
  include/File.h
  include/FreeCamera.h
  include/Game.h
  include/Input.h
  include/Logger.h
  include/Model.h
  include/Shader.h
  include/Texture.h
  src/gl3w/gl3w.c
  src/CameraBase.cpp
  src/Entity.cpp
  src/File.cpp
  src/FreeCamera.cpp
  src/Game.cpp
  src/Input.cpp
  src/Logger.cpp
  src/Model.cpp
  src/Shader.cpp
  src/Texture.cpp
)

if(WIN32)
  message(STATUS "Linking for Windows OS")
  target_link_libraries(GibEngine opengl32)
elseif(UNIX)
  message(STATUS "Linking for Linux")
  target_link_libraries(GibEngine dl)
endif()

add_dependencies(GibEngine assimp glm glfw spdlog)