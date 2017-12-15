# - Try to find g-truc GLM
# Once done this will define
#  GLM_FOUND - System has glm
#  GLM_INCLUDE_DIRS - The glm include directories
#=============================================================================
# Copyright 2017 Matt Ryder
#=============================================================================
# v1.0: No idea if this is the right way to FIND_PACKAGE, but it works.

#
# Find GLM
#
# Try to find GLM : OpenGL Mathematics.
# This module defines 
# - GLM_INCLUDE_DIRS
# - GLM_FOUND
#
# The following variables can be set as arguments for the module.
# - GLM_ROOT_DIR : Root library directory of GLM 
#
# References:
# - https://github.com/Groovounet/glm/blob/master/util/FindGLM.cmake
# - https://bitbucket.org/alfonse/gltut/src/28636298c1c0/glm-0.9.0.7/FindGLM.cmake
#

# Additional modules
include(FindPackageHandleStandardArgs)

if (WIN32)
	# Find include files
	find_path(
		GLM_INCLUDE_DIR
		NAMES glm/glm.hpp
		PATHS
		$ENV{PROGRAMFILES}/include
		${GLM_ROOT_DIR}/include
		DOC "The directory where glm/glm.hpp resides")
else()
	# Find include files
	find_path(
		GLM_INCLUDE_DIR
		NAMES glm/glm.hpp
		PATHS
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		${GLM_ROOT_DIR}/include)
endif()

# Define GLM_INCLUDE_DIR
if (GLM_FOUND)
	set(GLM_INCLUDE_DIR ${GLM_INCLUDE_DIR})
  

else(GLM_FOUND)
	ExternalProject_Add(glm
		GIT_REPOSITORY https://github.com/g-truc/glm
		GIT_TAG 5dcc56489e1b66dfd5bca751fa9b8dc68059e008
		CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/glm
	)

	ExternalProject_Get_Property(glm source_dir)
	set(GLM_INCLUDE_DIR ${source_dir})
endif(GLM_FOUND)

# Hide some variables
mark_as_advanced(GLM_INCLUDE_DIR)

# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(GLM DEFAULT_MSG GLM_INCLUDE_DIR)