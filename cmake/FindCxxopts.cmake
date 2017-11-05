# - Try to find Cxxopts
# Once done this will define
#  CXXOPTS_FOUND - System has cxxopts
#  CXXOPTS_INCLUDE_DIRS - The cxxopts include directories
#=============================================================================
# Copyright 2017 Matt Ryder
#=============================================================================
# v1.0: No idea if this is the right way to FIND_PACKAGE, but it works.

ExternalProject_Add(cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts
  GIT_TAG 0b7686949d01f6475cc13ba0693725aefb76fc0c
  CMAKE_ARGS
    -DCXXOPTS_BUILD_EXAMPLES=OFF
    -DCXXOPTS_BUILD_TESTS=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/cxxopts
)

ExternalProject_Get_Property(cxxopts source_dir)
list(APPEND GIBENGINE_INCLUDE_DIRS ${source_dir}/include)

set(CXXOPTS_FOUND TRUE)