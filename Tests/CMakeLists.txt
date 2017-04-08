cmake_minimum_required(VERSION 2.6)
project(Tests CXX)

include(ExternalProject)

# Google Test
set(GTEST_BUILD_DIR ${CMAKE_BINARY_DIR}/lib/googletest)
ExternalProject_Add(googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG ec44c6c1675c25b9827aacd08c02433cccde7780
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${GTEST_BUILD_DIR}
)
ExternalProject_Get_Property(googletest source_dir)
set(GOOGLETEST_INCLUDE_DIR ${source_dir}/googletest/include)
set(GOOGLEMOCK_INCLUDE_DIR ${source_dir}/googlemock/include)

set(GOOGLETEST_LIB_DIR ${GTEST_BUILD_DIR}/lib)

set(TESTS_INCLUDE_DIRS
  ${PROJECT_SOURCE_DIR}/include
  ${GOOGLETEST_INCLUDE_DIR}
  ${GOOGLEMOCK_INCLUDE_DIR}
  ${ENGINE_INCLUDE_DIRS}
  CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)

include_directories(${TESTS_INCLUDE_DIRS})

link_directories(${GOOGLETEST_LIB_DIR})

add_executable(Tests
  include/FileTest.h
  src/FileTest.cpp
  include/FreeCameraTest.h
  src/FreeCameraTest.cpp
  include/Main.h
  src/Main.cpp)

target_link_libraries(Tests gtest GibEngine)

add_dependencies(Tests GibEngine googletest)

add_test(
    NAME all
    COMMAND $<TARGET_FILE:Tests>
    )