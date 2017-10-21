cmake_minimum_required(VERSION 2.6)
project(GibTest C CXX)

include(ExternalProject)

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated)
endif()

# Google Test
set(GTEST_BUILD_DIR ${CMAKE_BINARY_DIR}/lib/googletest)
ExternalProject_Add(googletest
  GIT_REPOSITORY https://github.com/google/googletest
  GIT_TAG ec44c6c1675c25b9827aacd08c02433cccde7780
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${GTEST_BUILD_DIR}
	-DBUILD_SHARED_LIBS=ON
)

set(GOOGLETEST_INCLUDE_DIR ${GTEST_BUILD_DIR}/include)
set(GOOGLETEST_LIB_DIR ${GTEST_BUILD_DIR}/lib)

if(MSVC)
  set(GTEST_DLL ${CMAKE_BINARY_DIR}/lib/googletest/lib/gtest${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()


set(TESTS_INCLUDE_DIRS
  ${PROJECT_SOURCE_DIR}/include;
  ${GOOGLETEST_INCLUDE_DIR};
  CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)

include_directories(${TESTS_INCLUDE_DIRS} ${ENGINE_INCLUDE_DIRS})

link_directories(${GOOGLETEST_LIB_DIR})

add_executable(GibTest
	include/EntityTest.h
	src/EntityTest.cpp

	include/FileTest.h
	src/FileTest.cpp

	include/ControllerTest.h
	src/ControllerTest.cpp

	include/InputManagerTest.h
	src/InputManagerTest.cpp

	include/FreeCameraTest.h
	src/FreeCameraTest.cpp

	include/Main.h
	src/Main.cpp)

target_link_libraries(GibTest GibEngine gtest)

add_dependencies(GibTest GibEngine googletest)

add_test(
    NAME all
    COMMAND $<TARGET_FILE:GibTest>
    )

if(MSVC)
	add_custom_command(TARGET GibTest POST_BUILD
					   COMMAND ${CMAKE_COMMAND} -E copy_if_different
					   ${GTEST_DLL}
					   $<TARGET_FILE_DIR:GibEngine>)
endif()