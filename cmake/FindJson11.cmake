# - Try to find dropbox/Json11
# Once done this will define
#  JSON11_FOUND - System has json11
#  JSON11_INCLUDE_DIRS - The json11 include directories
#=============================================================================
# Copyright 2017 Matt Ryder
#=============================================================================
# v1.0: No idea if this is the right way to FIND_PACKAGE, but it works.

ExternalProject_Add(json11
  GIT_REPOSITORY https://github.com/dropbox/json11
  GIT_TAG ec4e45219af1d7cde3d58b49ed762376fccf1ace
  CMAKE_ARGS
    -DJSON11_BUILD_TESTS=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/json11
)

set(JSON11_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/lib/json11/include)

if(MSVC)
  set(JSON11_LIBRARIES ${CMAKE_BINARY_DIR}/lib/json11/lib/${CMAKE_STATIC_LIBRARY_PREFIX}json11${CMAKE_STATIC_LIBRARY_SUFFIX})
elseif(UNIX)
  set(JSON11_LIBRARIES ${CMAKE_BINARY_DIR}/lib/assimp/lib/${CMAKE_SHARED_LIBRARY_PREFIX}json11${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()

set(JSON11_FOUND TRUE)