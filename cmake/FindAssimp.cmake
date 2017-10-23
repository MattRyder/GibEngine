# - Try to find Assimp
# Once done this will define
#  ASSIMP_FOUND - System has Assimp
#  ASSIMP_INCLUDE_DIRS - The Assimp include directories
#  ASSIMP_LIBRARIES     The libraries needed to use Assimp
#  ASSIMP_DLL           DLL for Windows / MSVC 
#=============================================================================
# Copyright 2017 Matt Ryder
#=============================================================================
# v1.0: No idea if this is the right way to FIND_PACKAGE, but it works.

ExternalProject_Add(assimp
  GIT_REPOSITORY https://github.com/assimp/assimp
  GIT_TAG a8673d4828df5107186f49e5e4efa5316b727482
  CMAKE_ARGS
    -DASSIMP_BUILD_ASSIMP_TOOLS=OFF
    -DASSIMP_BUILD_TESTS=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/assimp
)
ExternalProject_Get_Property(assimp source_dir)
list(APPEND GIBENGINE_INCLUDE_DIRS ${source_dir}/include)

if(MSVC)
  set(ASSIMP_LIBRARIES ${CMAKE_BINARY_DIR}/lib/assimp/lib/${CMAKE_STATIC_LIBRARY_PREFIX}assimp-vc140-mt${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(ASSIMP_DLL ${CMAKE_BINARY_DIR}/lib/assimp/bin/assimp-vc140-mt${CMAKE_SHARED_LIBRARY_SUFFIX})
elseif(UNIX)
  set(ASSIMP_LIBRARIES ${CMAKE_BINARY_DIR}/lib/assimp/lib/${CMAKE_SHARED_LIBRARY_PREFIX}assimp${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()

set(ASSIMP_FOUND TRUE)