cmake_minimum_required(VERSION 2.6)
project(GibEngine CXX)

####################################################
#	PROJECT DEPENDENCIES
####################################################
include(ExternalProject)
ExternalProject_Add(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG 999f3556fdd80983b10051746264489f2cb1ef16
  CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/glfw"
)
ExternalProject_Get_Property(glfw source_dir)
set(glfw_include_dir ${source_dir}/include)

include(ExternalProject)
ExternalProject_Add(spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog
  GIT_TAG 93d84e5d594b15be0abef4998cdd1a5be72db476
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/spdlog
)
ExternalProject_Get_Property(spdlog source_dir)
set(spdlog_include_dir ${source_dir}/include)

include(ExternalProject)
ExternalProject_Add(glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG 5dcc56489e1b66dfd5bca751fa9b8dc68059e008
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/glm
)
ExternalProject_Get_Property(glm source_dir)
set(glm_include_dir ${source_dir})

include(ExternalProject)
ExternalProject_Add(assimp
  GIT_REPOSITORY https://github.com/assimp/assimp
  GIT_TAG a8673d4828df5107186f49e5e4efa5316b727482
  CMAKE_ARGS -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/assimp
)
ExternalProject_Get_Property(assimp source_dir)
set(assimp_include_dir ${source_dir}/include)

set(GibEngine_VERSION_MAJOR 1)
set(GibEngine_VERSION_MINOR 0)
set(GibEngine_VERSION_PATCH 0)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

include_directories(${glfw_include_dir} ${spdlog_include_dir} ${glm_include_dir} ${assimp_include_dir} include/)

set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
    
file(GLOB_RECURSE GibEngineSource src/*.cpp)

add_library(GibEngine ${GibEngineSource} ${GibEngine_INCLUDE_DIRS})

add_dependencies(GibEngine assimp glm glfw spdlog)