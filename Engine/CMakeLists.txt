cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(GibEngine C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GIBENGINE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

####################################################
#	PROJECT DEPENDENCIES
####################################################
include(ExternalProject)

find_package(glfw3 CONFIG REQUIRED)
find_package(Assimp CONFIG REQUIRED)

if(UNIX)
  string(REGEX REPLACE "assimp.lib" "libassimp.a" ASSIMP_LIBRARIES ${ASSIMP_LIBRARIES})
endif(UNIX)

find_package(Sqlite3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

find_path(CXXOPTS_INCLUDE_DIR cxxopts.hpp)
if(CXXOPTS_INCLUDE_DIR STREQUAL "CXXOPTS_INCLUDE_DIR-NOTFOUND")
  message(FATAL_ERROR "Could not find cxxopts")
endif()
list(APPEND GIBENGINE_INCLUDE_DIRS ${CXXOPTS_INCLUDE_DIR})

find_package(spdlog CONFIG REQUIRED)
# find_path(SPDLOG_INCLUDE_DIR spdlog/spdlog.h)
# if(SPDLOG_INCLUDE_DIR STREQUAL "SPDLOG_INCLUDE_DIR-NOTFOUND")
#   message(FATAL_ERROR "Could not find spdlog")
# endif()
# list(APPEND GIBENGINE_INCLUDE_DIRS ${SPDLOG_INCLUDE_DIR})

find_path(JSON11_INCLUDE_DIR json11.hpp)
if(JSON11_INCLUDE_DIR STREQUAL "JSON11_INCLUDE_DIR-NOTFOUND")
  message(FATAL_ERROR "Could not find json11")
endif()
list(APPEND GIBENGINE_INCLUDE_DIRS ${JSON11_INCLUDE_DIR})

find_library(JSON11_LIBRARY json11)
if(JSON11_LIBRARY STREQUAL "JSON11_LIBRARY-NOTFOUND")
  message(FATAL_ERROR "Could not find json11 library")
endif()

find_library(FMT_LIBRARY fmt)
if(FMT_LIBRARY STREQUAL "FMT_LIBRARY-NOTFOUND")
  message(FATAL_ERROR "Could not find fmt library")
endif()

set(GibEngine_VERSION_MAJOR 1)
set(GibEngine_VERSION_MINOR 0)
set(GibEngine_VERSION_PATCH 0)

add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE)

set(GIBENGINE_INCLUDE_DIRS ${GIBENGINE_INCLUDE_DIRS}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(SQLITE3PP_SRC
  include/sqlite3pp/sqlite3pp.h
  include/sqlite3pp/sqlite3ppext.h
  src/sqlite3pp/sqlite3pp.cpp
  src/sqlite3pp/sqlite3ppext.cpp)

# Split the engine src into respective namespaces for `source_group`ing
set(THIRDPARTY_INCLUDES
  include/stb/stb_image.h
  include/stb/stb_image_write.h
  include/GL/gl3w.h)

set(THIRDPARTY_SRC
  src/glfw/glfw_callback.cpp
  src/gl3w/gl3w.c
)

set(WORLD_INCLUDES
  include/world/Database.h
  include/world/DatabaseQuery.h
  include/world/DatabaseRecord.h)

set(WORLD_SRC
  src/world/Database.cpp)

set(INPUT_INCLUDES
  include/input/Controller.h
  include/input/InputManager.h)

set(INPUT_SRC
  src/input/Controller.cpp
  src/input/InputManager.cpp)

set(EVENT_INCLUDES
	include/event/IEvent.h
	include/event/BaseEvent.h
	include/event/OnTickEvent.h
	include/event/InputEvents.h
	include/event/EventManager.h)

set(EVENT_SRC
	src/event/BaseEvent.cpp
	src/event/EventManager.cpp)

set(FILESYSTEM_INCLUDES include/filesystem/IFileSystem.h)

if(WIN32)
  list(APPEND FILESYSTEM_INCLUDES include/filesystem/WindowsFileSystem.h)
  set(FILESYSTEM_SRC src/filesystem/WindowsFileSystem.cpp)
elseif(UNIX)
  list(APPEND FILESYSTEM_INCLUDES include/filesystem/UnixFileSystem.h)
  set(FILESYSTEM_SRC src/filesystem/UnixFileSystem.cpp)
endif()

set(RENDERER_INCLUDES
  include/renderer/api/IGraphicsApi.h
  include/renderer/api/GL420.h
  include/renderer/api/GLES3.h
  include/renderer/UniformBufferManager.h
  include/renderer/RenderPass.h
  include/renderer/Pipeline.h
  include/renderer/ForwardRenderPass.h
  include/renderer/SkyboxRenderPass.h
  include/renderer/DeferredGeometryPass.h
  include/renderer/DeferredLightingPass.h
  include/renderer/RenderToTexturePass.h
  include/renderer/SsaoPass.h
  include/renderer/Framebuffer.h)

set(RENDERER_SRC
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
  src/renderer/SsaoPass.cpp
  src/renderer/Framebuffer.cpp)

set(SCENE_INCLUDES
	include/scene/VisibleSet.h)

set(SCENE_SRC
	src/scene/VisibleSet.cpp)

set(ROOT_INCLUDES
  include/glfw/glfw_callback.h
  include/AABB.h
  include/CameraBase.h
  include/BaseEntity.h
  include/IEntity.h
  include/EnumFlags.h
  include/FreeCamera.h
  include/Game.h
  include/Logger.h
  include/Mesh.h
  include/MeshService.h
  include/Shader.h
  include/Skybox.h
  include/Texture.h
  include/LightBase.h
  include/PointLight.h)

set(ROOT_SRC
  src/AABB.cpp
  src/CameraBase.cpp
  src/BaseEntity.cpp
  src/FreeCamera.cpp
  src/Game.cpp
  src/Logger.cpp
  src/Mesh.cpp
  src/MeshService.cpp
  src/Shader.cpp
  src/Skybox.cpp
  src/Texture.cpp
  src/LightBase.cpp
  src/PointLight.cpp)

add_library(GibEngine
  ${SQLITE3PP_SRC}
  ${THIRDPARTY_INCLUDES}
  ${THIRDPARTY_SRC}
  ${EVENT_INCLUDES}
  ${EVENT_SRC}
  ${WORLD_INCLUDES}
  ${WORLD_SRC}
  ${FILESYSTEM_INCLUDES}
  ${FILESYSTEM_SRC}
  ${INPUT_INCLUDES}
  ${INPUT_SRC}
  ${SCENE_INCLUDES}
  ${SCENE_SRC}
  ${RENDERER_INCLUDES}
  ${RENDERER_SRC}
  ${ROOT_INCLUDES}
  ${ROOT_SRC})

# Setup source_groups
source_group("Header Files" FILES ${ROOT_INCLUDES})
source_group("Header Files\\ThirdParty" FILES ${THIRDPARTY_INCLUDES})
source_group("Header Files\\World" FILES ${WORLD_INCLUDES})
source_group("Header Files\\Input" FILES ${INPUT_INCLUDES})
source_group("Header Files\\Renderer" FILES ${RENDERER_INCLUDES})
source_group("Header Files\\FileSystem" FILES ${FILESYSTEM_INCLUDES})
source_group("Header Files\\Scene" FILES ${SCENE_INCLUDES})
source_group("Header Files\\Event" FILES ${EVENT_INCLUDES})
source_group("Source Files" FILES ${ROOT_SRC})
source_group("Source Files\\ThirdParty" FILES ${THIRDPARTY_SRC})
source_group("Source Files\\ThirdParty\\SQLite3pp" FILES ${SQLITE3PP_SRC})
source_group("Source Files\\Event" FILES ${EVENT_SRC})
source_group("Source Files\\World" FILES ${WORLD_SRC})
source_group("Source Files\\Input" FILES ${INPUT_SRC})
source_group("Source Files\\Scene" FILES ${SCENE_SRC})
source_group("Source Files\\Renderer" FILES ${RENDERER_SRC})
source_group("Source Files\\FileSystem" FILES ${FILESYSTEM_SRC})

target_include_directories(GibEngine PUBLIC ${GIBENGINE_INCLUDE_DIRS})

set(GIBENGINE_LIBRARIES ${ASSIMP_LIBRARIES} glm glfw sqlite3 spdlog::spdlog ${FMT_LIBRARY} ${JSON11_LIBRARY})

if(WIN32)
 set(APPEND GIBENGINE_LIBRARIES opengl32)
elseif(UNIX)
 set(APPEND GIBENGINE_LIBRARIES dl pthread)
endif()

target_link_libraries(GibEngine PRIVATE ${GIBENGINE_LIBRARIES})

#add_dependencies(GibEngine glm glfw spdlog cxxopts json11 sqlite3)