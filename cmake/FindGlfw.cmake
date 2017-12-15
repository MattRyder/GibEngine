# - Try to find GLFW
# Once done this will define
#  GLFW_FOUND         System has GLFW
#  GLFW_INCLUDE_DIRS  The GLFW include directories
#  GLFW_LIBRARIES     The libraries needed to use GLFW
#  GLFW_DLL           DLL for Windows / MSVC 
#=============================================================================
# Copyright 2017 Matt Ryder
#=============================================================================
# v1.0: No idea if this is the right way to FIND_PACKAGE, but it works.

#
# Find GLFW
#
# Try to find GLFW library.
# This module defines the following variables:
# - GLFW_INCLUDE_DIRS
# - GLFW_LIBRARIES
# - GLFW_FOUND
#
# The following variables can be set as arguments for the module.
# - GLFW_ROOT_DIR : Root library directory of GLFW
# - GLFW_USE_STATIC_LIBS : Specifies to use static version of GLFW library (Windows only)
#
# References:
# - https://github.com/progschj/OpenGL-Examples/blob/master/cmake_modules/FindGLFW.cmake
# - https://bitbucket.org/Ident8/cegui-mk2-opengl3-renderer/src/befd47200265/cmake/FindGLFW.cmake
#

# Additional modules
include(FindPackageHandleStandardArgs)

if (WIN32)
	# Find include files
	find_path(
		GLFW_INCLUDE_DIR
		NAMES GLFW/glfw3.h
		PATHS
		$ENV{PROGRAMFILES}/include
		${GLFW_ROOT_DIR}/include
		DOC "The directory where GLFW/glfw.h resides")

	# Use glfw3.lib for static library
	if (GLFW_USE_STATIC_LIBS)
		set(GLFW_LIBRARY_NAME glfw3)
	else()
		set(GLFW_LIBRARY_NAME glfw3dll)
	endif()

	# Find library files
	find_library(
		GLFW_LIBRARY
		NAMES ${GLFW_LIBRARY_NAME}
		PATHS
		$ENV{PROGRAMFILES}/lib
		${GLFW_ROOT_DIR}/lib)

	unset(GLFW_LIBRARY_NAME)
else()
	# Find include files
	find_path(
		GLFW_INCLUDE_DIR
		NAMES GLFW/glfw3.h
		PATHS
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include)
  
	# Find library files
	find_library(
		GLFW_LIBRARY
		NAMES glfw
		PATHS
		/usr/lib64
    /usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		${GLFW_ROOT_DIR}/lib)
endif()

# Define GLFW_LIBRARIES and GLFW_INCLUDE_DIRS
if (GLFW_FOUND)
	set(GLFW_LIBRARY ${OPENGL_LIBRARIES} ${GLFW_LIBRARY})
  set(GLFW_INCLUDE_DIR ${GLFW_INCLUDE_DIR})

else()
	ExternalProject_Add(glfw
		GIT_REPOSITORY https://github.com/glfw/glfw
		GIT_TAG 999f3556fdd80983b10051746264489f2cb1ef16
		CMAKE_ARGS
			-DGLFW_BUILD_EXAMPLES=OFF
			-DGLFW_BUILD_TESTS=OFF
			-DGLFW_BUILD_DOCS=OFF
			-DBUILD_SHARED_LIBS=ON
			-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/glfw
	)

	ExternalProject_Get_Property(glfw source_dir)
	set(GLFW_INCLUDE_DIR ${source_dir}/include)

	if(MSVC)
		set(GLFW_LIBRARY ${CMAKE_BINARY_DIR}/lib/glfw/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3dll${CMAKE_STATIC_LIBRARY_SUFFIX})
		set(GLFW_DLL ${CMAKE_BINARY_DIR}/lib/glfw/lib/glfw3${CMAKE_SHARED_LIBRARY_SUFFIX})
	elseif(UNIX)
		set(GLFW_LIBRARY ${CMAKE_BINARY_DIR}/lib/glfw/lib/${CMAKE_SHARED_LIBRARY_PREFIX}glfw${CMAKE_SHARED_LIBRARY_SUFFIX})
	endif()
endif()

# Hide variables from the user:
mark_as_advanced(GLFW_INCLUDE_DIR GLFW_LIBRARY)

# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(GLFW DEFAULT_MSG GLFW_INCLUDE_DIR GLFW_LIBRARY)