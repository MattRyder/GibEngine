# - Try to find Spdlog
# Once done this will define
#  SPDLOG_FOUND - System has spdlog
#  SPDLOG_INCLUDE_DIRS - The spdlog include directories
#=============================================================================
# Copyright 2017 Matt Ryder
#=============================================================================
# v1.0: No idea if this is the right way to FIND_PACKAGE, but it works.

ExternalProject_Add(spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog
  GIT_TAG 93d84e5d594b15be0abef4998cdd1a5be72db476
  CMAKE_ARGS
    -DSPDLOG_BUILD_TESTING=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/spdlog
)

ExternalProject_Get_Property(spdlog source_dir)
set(SPDLOG_INCLUDE_DIRS ${source_dir}/include)

set(SPDLOG_FOUND TRUE)