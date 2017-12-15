# - Try to find Assimp
# Once done this will define
#  assimp_FOUND - System has Assimp
#  assimp_INCLUDE_DIRS - The Assimp include directories
#  assimp_LIBRARIES     The libraries needed to use Assimp
#  assimp_DLL           DLL for Windows / MSVC 
#=============================================================================
# Copyright 2017 Matt Ryder
#=============================================================================
# v1.0: No idea if this is the right way to FIND_PACKAGE, but it works.

# Additional modules
include(FindPackageHandleStandardArgs)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(ASSIMP_ARCHITECTURE "64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(ASSIMP_ARCHITECTURE "32")
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

if(WIN32)
  set(ASSIMP_ROOT_DIR CACHE PATH "ASSIMP root directory")

  # Find path of each library
  find_path(ASSIMP_INCLUDE_DIR
    NAMES
      assimp/anim.h
    HINTS
      ${ASSIMP_ROOT_DIR}/include
  )

  if(MSVC12)
    set(ASSIMP_MSVC_VERSION "vc120")
  elseif(MSVC14)	
    set(ASSIMP_MSVC_VERSION "vc140")
  endif(MSVC12)

  if(MSVC12 OR MSVC14)
    find_path(ASSIMP_LIBRARY_DIR
      NAMES
        assimp-${ASSIMP_MSVC_VERSION}-mt.lib
      HINTS
        ${ASSIMP_ROOT_DIR}/lib${ASSIMP_ARCHITECTURE}
    )
    
    find_library(ASSIMP_LIBRARY_RELEASE assimp-${ASSIMP_MSVC_VERSION}-mt.lib  PATHS ${ASSIMP_LIBRARY_DIR})
    find_library(ASSIMP_LIBRARY_DEBUG   assimp-${ASSIMP_MSVC_VERSION}-mtd.lib PATHS ${ASSIMP_LIBRARY_DIR})
    
    set(ASSIMP_LIBRARY 
      optimized 	${ASSIMP_LIBRARY_RELEASE}
      debug		${ASSIMP_LIBRARY_DEBUG}
    )
    
    set(ASSIMP_LIBRARIES "ASSIMP_LIBRARY_RELEASE" "ASSIMP_LIBRARY_DEBUG")
  endif()

else(WIN32)
  find_path(
    assimp_INCLUDE_DIRS
    NAMES postprocess.h scene.h version.h config.h cimport.h
    PATHS /usr/include/assimp
  )

  find_library(
    assimp_LIBRARIES
    NAMES assimp
    PATHS /usr/lib/assimp
  )

  if (assimp_INCLUDE_DIRS AND assimp_LIBRARIES)
    SET(assimp_FOUND TRUE)
  ENDIF (assimp_INCLUDE_DIRS AND assimp_LIBRARIES)

  if (assimp_FOUND)
    return()
  else (assimp_FOUND)
    if (assimp_FIND_REQUIRED)
    message(FATAL_ERROR "Could not find asset importer library locally...")
    endif (assimp_FIND_REQUIRED)
  endif (assimp_FOUND)

endif(WIN32)

# Fall through to the direct download of the Assimp lib:
ExternalProject_Add(assimp
  GIT_REPOSITORY https://github.com/assimp/assimp
  GIT_TAG a8673d4828df5107186f49e5e4efa5316b727482
  CMAKE_ARGS
    -DASSIMP_BUILD_ASSIMP_TOOLS=OFF
    -DASSIMP_BUILD_TESTS=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/assimp
)
ExternalProject_Get_Property(assimp source_dir)
set(assimp_INCLUDE_DIRS ${source_dir}/include)

if(MSVC)
  set(assimp_LIBRARIES ${CMAKE_BINARY_DIR}/lib/assimp/lib/${CMAKE_STATIC_LIBRARY_PREFIX}assimp-${ASSIMP_MSVC_VERSION}-mt${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(assimp_DLL ${CMAKE_BINARY_DIR}/lib/assimp/bin/assimp-vc140-mt${CMAKE_SHARED_LIBRARY_SUFFIX})
elseif(UNIX)
  set(assimp_LIBRARIES ${CMAKE_BINARY_DIR}/lib/assimp/lib/${CMAKE_SHARED_LIBRARY_PREFIX}assimp${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()

# Hide some variables
mark_as_advanced(assimp_INCLUDE_DIRS assimp_LIBRARIES)

# Handle REQUIRD argument, define *_FOUND variable
find_package_handle_standard_args(assimp DEFAULT_MSG assimp_INCLUDE_DIRS assimp_LIBRARIES)