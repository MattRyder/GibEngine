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
set(GLFW_INCLUDE_DIRS ${source_dir}/include)

if(MSVC)
  set(GLFW_LIBRARIES ${CMAKE_BINARY_DIR}/lib/glfw/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3dll${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(GLFW_DLL ${CMAKE_BINARY_DIR}/lib/glfw/lib/glfw3${CMAKE_SHARED_LIBRARY_SUFFIX})
elseif(UNIX)
  set(GLFW_LIBRARIES ${CMAKE_BINARY_DIR}/lib/glfw/lib/${CMAKE_SHARED_LIBRARY_PREFIX}glfw${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()

set(GLFW_FOUND TRUE)