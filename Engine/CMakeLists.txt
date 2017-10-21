cmake_minimum_required(VERSION 2.6)
project(GibEngine C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ENGINE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

if(UNIX)
  set(LINK_TARGETS pthread)
endif()

####################################################
#	PROJECT DEPENDENCIES
####################################################
include(ExternalProject)
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
list(APPEND ENGINE_INCLUDE_DIRS ${source_dir}/include)

if(MSVC)
  set(GLFW_LIBRARY ${CMAKE_BINARY_DIR}/lib/glfw/lib/${CMAKE_STATIC_LIBRARY_PREFIX}glfw3dll${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(GLFW_DLL ${CMAKE_BINARY_DIR}/lib/glfw/lib/glfw3${CMAKE_SHARED_LIBRARY_SUFFIX})
elseif(UNIX)
  set(GLFW_LIBRARY ${CMAKE_BINARY_DIR}/lib/glfw/lib/${CMAKE_SHARED_LIBRARY_PREFIX}glfw${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()

LIST(APPEND LINK_TARGETS ${GLFW_LIBRARY})

ExternalProject_Add(spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog
  GIT_TAG 93d84e5d594b15be0abef4998cdd1a5be72db476
  CMAKE_ARGS
    -DSPDLOG_BUILD_TESTING=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/spdlog
)
ExternalProject_Get_Property(spdlog source_dir)
list(APPEND ENGINE_INCLUDE_DIRS ${source_dir}/include)

ExternalProject_Add(cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts
  GIT_TAG 0b7686949d01f6475cc13ba0693725aefb76fc0c
  CMAKE_ARGS
    -DCXXOPTS_BUILD_EXAMPLES=OFF
    -DCXXOPTS_BUILD_TESTS=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/cxxopts
)
ExternalProject_Get_Property(cxxopts source_dir)
list(APPEND ENGINE_INCLUDE_DIRS ${source_dir}/include)

ExternalProject_Add(glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG 5dcc56489e1b66dfd5bca751fa9b8dc68059e008
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/glm
)
ExternalProject_Get_Property(glm source_dir)
list(APPEND ENGINE_INCLUDE_DIRS ${source_dir})

ExternalProject_Add(assimp
  GIT_REPOSITORY https://github.com/assimp/assimp
  GIT_TAG a8673d4828df5107186f49e5e4efa5316b727482
  CMAKE_ARGS
    -DASSIMP_BUILD_ASSIMP_TOOLS=OFF
    -DASSIMP_BUILD_TESTS=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/assimp
)
ExternalProject_Get_Property(assimp source_dir)
list(APPEND ENGINE_INCLUDE_DIRS ${source_dir}/include)

if(MSVC)
  set(ASSIMP_LIBRARY ${CMAKE_BINARY_DIR}/lib/assimp/lib/${CMAKE_STATIC_LIBRARY_PREFIX}assimp-vc140-mt${CMAKE_STATIC_LIBRARY_SUFFIX})
  set(ASSIMP_DLL ${CMAKE_BINARY_DIR}/lib/assimp/bin/assimp-vc140-mt${CMAKE_SHARED_LIBRARY_SUFFIX})
elseif(UNIX)
  set(ASSIMP_LIBRARY ${CMAKE_BINARY_DIR}/lib/assimp/lib/${CMAKE_SHARED_LIBRARY_PREFIX}assimp${CMAKE_SHARED_LIBRARY_SUFFIX})
endif()

LIST(APPEND LINK_TARGETS ${ASSIMP_LIBRARY})

set(GibEngine_VERSION_MAJOR 1)
set(GibEngine_VERSION_MINOR 0)
set(GibEngine_VERSION_PATCH 0)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

set(ENGINE_INCLUDE_DIRS ${ENGINE_INCLUDE_DIRS}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

include_directories(${ENGINE_INCLUDE_DIRS})

set(SOURCE_TREE
  include/stb/stb_image.h
  include/stb/stb_image_write.h
  include/CameraBase.h
  include/Entity.h
  include/File.h
  include/FreeCamera.h
  include/Game.h
  include/Logger.h
  include/Mesh.h
  include/Model.h
  include/Shader.h
  include/Skybox.h
  include/Texture.h

  include/LightBase.h
  include/PointLight.h

  include/input/Controller.h
  include/input/InputManager.h

  include/renderer/api/IGraphicsApi.h
  include/renderer/api/GL420.h
  include/renderer/api/GLES3.h
  include/renderer/UniformBufferManager.h
  include/renderer/RenderPassType.h
  include/renderer/RenderPass.h
  include/renderer/Pipeline.h
  include/renderer/ForwardRenderPass.h
  include/renderer/SkyboxRenderPass.h
  include/renderer/DeferredGeometryPass.h
  include/renderer/DeferredLightingPass.h
  include/renderer/RenderToTexturePass.h
  include/renderer/Framebuffer.h
  include/glfw/glfw_callback.h

  src/glfw/glfw_callback.cpp
  src/gl3w/gl3w.c
  src/CameraBase.cpp
  src/Entity.cpp
  src/File.cpp
  src/FreeCamera.cpp
  src/Game.cpp
  src/Logger.cpp
  src/Mesh.cpp
  src/Model.cpp
  src/Shader.cpp
  src/Skybox.cpp
  src/Texture.cpp

  src/LightBase.cpp
  src/PointLight.cpp

  src/input/Controller.cpp
  src/input/InputManager.cpp

  src/renderer/api/GLES3.cpp
  src/renderer/api/GL420.cpp
  src/renderer/UniformBufferManager.cpp
  src/renderer/Pipeline.cpp
  src/renderer/RenderPass.cpp
  src/renderer/ForwardRenderPass.cpp
  src/renderer/SkyboxRenderPass.cpp
  src/renderer/DeferredGeometryPass.cpp
  src/renderer/DeferredLightingPass.cpp
  src/renderer/RenderToTexturePass.cpp
  
  src/renderer/Framebuffer.cpp)

add_library(GibEngine ${SOURCE_TREE})

if(WIN32)
  LIST(APPEND LINK_TARGETS opengl32)
elseif(UNIX)
  LIST(APPEND LINK_TARGETS dl)
endif()

target_link_libraries(GibEngine ${LINK_TARGETS})

add_dependencies(GibEngine assimp glm glfw spdlog cxxopts)

if(MSVC)
	add_custom_command(TARGET GibEngine POST_BUILD
					   COMMAND ${CMAKE_COMMAND} -E copy_if_different
					   ${GLFW_DLL}
					   $<TARGET_FILE_DIR:GibEngine>)

	add_custom_command(TARGET GibEngine POST_BUILD
					   COMMAND ${CMAKE_COMMAND} -E copy_if_different
					   ${ASSIMP_DLL}
					   $<TARGET_FILE_DIR:GibEngine>)
endif()