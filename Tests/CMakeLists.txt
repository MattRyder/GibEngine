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
  GIT_TAG 6c73adfc03e277f55cb1e4947b3a5e6c5ff4fe46
  CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${GTEST_BUILD_DIR}
	-DBUILD_SHARED_LIBS=ON
)

set(GOOGLETEST_INCLUDE_DIR ${GTEST_BUILD_DIR}/include)
set(GOOGLETEST_LIB_DIR ${GTEST_BUILD_DIR}/lib)

if(MSVC)
  set(GTEST_DLL ${CMAKE_BINARY_DIR}/lib/googletest/bin/gtestd${CMAKE_SHARED_LIBRARY_SUFFIX})
  set(GMOCK_DLL ${CMAKE_BINARY_DIR}/lib/googletest/bin/gmockd${CMAKE_SHARED_LIBRARY_SUFFIX})

  set(GTEST_LIBS gtestd gmockd)
else()
  set(GTEST_LIBS gtest gmock)
endif()

set(TESTS_INCLUDE_DIRS
  ${PROJECT_SOURCE_DIR}/include;
  ${GOOGLETEST_INCLUDE_DIR};
  CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE
)

include_directories(${TESTS_INCLUDE_DIRS} ${GIBENGINE_INCLUDE_DIRS})

link_directories(${GOOGLETEST_LIB_DIR})

set(SOURCE_TREE
	include/mocks/MockGraphicsApi.h
	include/EntityTest.h
	include/WorldDatabaseTest.h
	include/ControllerTest.h
	include/InputManagerTest.h
	include/FreeCameraTest.h
	include/LightBaseTest.h
	include/MeshServiceTest.h
	include/SceneNodeTest.h
	include/AABBTest.h
	include/Main.h
	src/EntityTest.cpp
	src/WorldDatabaseTest.cpp
	src/ControllerTest.cpp
	src/InputManagerTest.cpp
	src/FreeCameraTest.cpp
	src/LightBaseTest.cpp
	src/MeshServiceTest.cpp
	src/SceneNodeTest.cpp
	src/AABBTest.cpp
	src/Main.cpp)

if(WIN32)
  list(APPEND SOURCE_TREE
	include/WindowsFileSystemTest.h
	src/WindowsFileSystemTest.cpp)
elseif(UNIX)
	list(APPEND SOURCE_TREE
		include/UnixFileSystemTest.h
		src/UnixFileSystemTest.cpp)
endif()


add_executable(GibTest ${SOURCE_TREE})
target_compile_definitions(GibTest PRIVATE -DGTEST_LINKED_AS_SHARED_LIBRARY)

target_link_libraries(GibTest GibEngine ${GTEST_LIBS})

add_dependencies(GibTest GibEngine googletest)

if(MSVC)
	add_custom_command(TARGET GibTest POST_BUILD
					   COMMAND ${CMAKE_COMMAND} -E copy_if_different
					   ${GTEST_DLL}
					   $<TARGET_FILE_DIR:GibEngine>)

	add_custom_command(TARGET GibTest POST_BUILD
					   COMMAND ${CMAKE_COMMAND} -E copy_if_different
					   ${GMOCK_DLL}
					   $<TARGET_FILE_DIR:GibEngine>)
endif()

add_test(
    NAME all
    COMMAND $<TARGET_FILE:GibTest>
    )

