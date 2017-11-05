# - Try to find g-truc GLM
# Once done this will define
#  GLM_FOUND - System has glm
#  GLM_INCLUDE_DIRS - The glm include directories
#=============================================================================
# Copyright 2017 Matt Ryder
#=============================================================================
# v1.0: No idea if this is the right way to FIND_PACKAGE, but it works.

ExternalProject_Add(glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG 5dcc56489e1b66dfd5bca751fa9b8dc68059e008
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/glm
)

ExternalProject_Get_Property(glm source_dir)
set(GLM_INCLUDE_DIRS ${source_dir})

set(GLM_FOUND TRUE)