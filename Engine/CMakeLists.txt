cmake_minimum_required(VERSION 2.6)
project(GibEngine C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GIBENGINE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

if(UNIX)
  set(GIBENGINE_LIBRARIES pthread)
endif()

####################################################
#	PROJECT DEPENDENCIES
####################################################
include(ExternalProject)

find_package(Glfw REQUIRED)
if(GLFW_FOUND)
  list(APPEND GIBENGINE_INCLUDE_DIRS ${GLFW_INCLUDE_DIRS})
  list(APPEND GIBENGINE_LIBRARIES ${GLFW_LIBRARIES})
endif()

find_package(Spdlog REQUIRED)
if(SPDLOG_FOUND)
  list(APPEND GIBENGINE_INCLUDE_DIRS ${SPDLOG_INCLUDE_DIRS})
endif()

find_package(Cxxopts REQUIRED)
if(CXXOPTS_FOUND)
  list(APPEND GIBENGINE_INCLUDE_DIRS ${CXXOPTS_INCLUDE_DIRS})
endif()

find_package(Glm REQUIRED)
if(GLM_FOUND)
  list(APPEND GIBENGINE_INCLUDE_DIRS ${GLM_INCLUDE_DIRS})
endif()

find_package(Assimp REQUIRED)
if(ASSIMP_FOUND)
  list(APPEND GIBENGINE_INCLUDE_DIRS ${ASSIMP_INCLUDE_DIRS})
  list(APPEND GIBENGINE_LIBRARIES ${ASSIMP_LIBRARIES})
endif()

set(GibEngine_VERSION_MAJOR 1)
set(GibEngine_VERSION_MINOR 0)
set(GibEngine_VERSION_PATCH 0)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

set(GIBENGINE_INCLUDE_DIRS ${GIBENGINE_INCLUDE_DIRS}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

include_directories(${GIBENGINE_INCLUDE_DIRS})

set(SQLITE3PP_SRC
  include/sqlite3pp/sqlite3.h
  include/sqlite3pp/sqlite3pp.h
  include/sqlite3pp/sqlite3ppext.h
  src/sqlite3pp/sqlite3.c
  src/sqlite3pp/sqlite3pp.cpp
  src/sqlite3pp/sqlite3ppext.cpp)

include_directories(include/sqlite3pp/)

set(SOURCE_TREE
  ${SQLITE3PP_SRC}
  include/GL/gl3w.h
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
  include/world/Database.h
  include/world/DatabaseQuery.h
  include/world/DatabaseEntity.h
  include/world/World.h
  include/world/Level.h
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
  src/world/Database.cpp
  src/world/DatabaseEntity.cpp
  src/world/World.cpp
  src/world/Level.cpp
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
  LIST(APPEND GIBENGINE_LIBRARIES opengl32)
elseif(UNIX)
  LIST(APPEND GIBENGINE_LIBRARIES dl)
endif()

target_link_libraries(GibEngine ${GIBENGINE_LIBRARIES})

add_dependencies(GibEngine assimp glm glfw spdlog cxxopts)

if(MSVC)
  if(GLFW_FOUND)
    add_custom_command(TARGET GibEngine POST_BUILD
              COMMAND ${CMAKE_COMMAND} -E copy_if_different
              ${GLFW_DLL}
              $<TARGET_FILE_DIR:GibEngine>)
  endif()

  if(ASSIMP_FOUND)
    add_custom_command(TARGET GibEngine POST_BUILD
              COMMAND ${CMAKE_COMMAND} -E copy_if_different
              ${ASSIMP_DLL}
              $<TARGET_FILE_DIR:GibEngine>)
  endif()
endif()