# Copyright (C) 2007-2009 LuaDist.
# Created by Peter Kapec <kapecp@gmail.com>
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the COPYRIGHT file distributed with LuaDist.
#
# SQLITE3_INCLUDE_DIRS	- where to find sqlite3.h, etc.
# SQLITE3_LIBRARIES	- List of libraries when using sqlite.
# SQLITE3_FOUND	- True if sqlite found.

# Look for the header file.
FIND_PATH(SQLITE3_INCLUDE_DIRS NAMES sqlite3.h)

# Look for the library.
FIND_LIBRARY(SQLITE3_LIBRARIES NAMES sqlite)

# Copy the results to the output variables.
IF(SQLITE3_FOUND)
ELSE(SQLITE3_FOUND)
  set(SQLITE_INSTALL_DIR ${CMAKE_BINARY_DIR}/lib/sqlite3)

  ExternalProject_Add(sqlite3
    GIT_REPOSITORY https://github.com/alex85k/sqlite3-cmake
    GIT_TAG 9564ab3bda829ac7d29613f7ae703f3bd77f76b8
    CMAKE_ARGS
      -DCMAKE_INSTALL_PREFIX=${SQLITE_INSTALL_DIR}
  )

  set(SQLITE3_INCLUDE_DIRS ${SQLITE_INSTALL_DIR}/include)

  if(MSVC)
    set(SQLITE3_LIBRARIES ${SQLITE_INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}sqlite3${CMAKE_STATIC_LIBRARY_SUFFIX})
  elseif(UNIX)
    set(SQLITE3_LIBRARIES ${SQLITE_INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}sqlite3${CMAKE_STATIC_LIBRARY_SUFFIX})
  endif()
ENDIF(SQLITE3_FOUND)

# Handle the QUIETLY and REQUIRED arguments and set SQLITE3_FOUND to TRUE if all listed variables are TRUE.
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SQLITE3 DEFAULT_MSG SQLITE3_LIBRARIES SQLITE3_INCLUDE_DIRS)

MARK_AS_ADVANCED(SQLITE3_INCLUDE_DIRS SQLITE3_LIBRARIES)