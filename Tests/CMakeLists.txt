cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(GibTest C CXX)

include(ExternalProject)
include(GoogleTest)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated)
endif()


set(TESTS_INCLUDE_DIRS
  ${PROJECT_SOURCE_DIR}/include;
  CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)

include_directories(${TESTS_INCLUDE_DIRS} ${GIBENGINE_INCLUDE_DIRS})

add_executable(GibTest
	# include/mocks/MockGraphicsApi.h
	include/EntityTest.h
	include/WorldDatabaseTest.h
	include/ControllerTest.h
	include/InputManagerTest.h
	include/FreeCameraTest.h
	include/LightBaseTest.h
	# include/MeshServiceTest.h
	include/AABBTest.h
	src/EntityTest.cpp
	src/WorldDatabaseTest.cpp
	src/ControllerTest.cpp
	src/InputManagerTest.cpp
	src/FreeCameraTest.cpp
	src/LightBaseTest.cpp
	#src/MeshServiceTest.cpp
	src/AABBTest.cpp)

target_link_libraries(GibTest GibEngine ${GTEST_BOTH_LIBRARIES})

add_dependencies(GibTest GibEngine)

gtest_add_tests(
	TARGET	GibTest
	TEST_LIST GibTestAll)