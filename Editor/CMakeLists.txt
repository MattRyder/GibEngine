cmake_minimum_required(VERSION 2.6)
project(Editor CXX)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

if(UNIX)
	find_package(GTK3 REQUIRED)
	if(GTK3_FOUND)
		include_directories(${GTK3_INCLUDE_DIRS})
	endif()
endif()

set(EDITOR_INCLUDE_DIRS
  ${PROJECT_SOURCE_DIR}/include
  ${ENGINE_INCLUDE_DIRS}
  CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

include_directories(${EDITOR_INCLUDE_DIRS})

file(GLOB_RECURSE SHADER_FILES ${CMAKE_SOURCE_DIR}/Assets/Shaders/*.glsl)

include_directories("thirdparty/imgui/")
file(
	GLOB IMGUI_FILES
		"thirdparty/imgui/imgui.cpp"
		"thirdparty/imgui/imgui_draw.cpp"
		"thirdparty/imgui/imgui_demo.cpp"
		"thirdparty/imgui/imgui_dock.cpp"
		"thirdparty/imgui/imgui_impl_glfw_gl3.cpp"
		"thirdparty/imgui/*.h"
)
source_group(ImGui FILES ${IMGUI_FILES})

include_directories("thirdparty/simpleini")
file(
	GLOB SIMPLEINI_FILES
	"thirdparty/simpleini/ConvertUTF.h"
	"thirdparty/simpleini/ConvertUTF.c"
	"thirdparty/simpleini/SimpleIni.h")
source_group(SimpleIni FILES ${SIMPLEINI_FILES})

include_directories("thirdparty/nativefiledialog")
file(
	GLOB NFD_FILES
	"thirdparty/nativefiledialog/nfd_common.c"
	"thirdparty/nativefiledialog/nfd_gtk.c"
	"thirdparty/nativefiledialog/nfd_win.cpp"
	"thirdparty/nativefiledialog/nfs_cocoa.m"
	"thirdparty/nativefiledialog/*.h")
source_group(NativeFileDialog FILES ${NFD_FILES})

file(
	GLOB COMPONENT_FILES
		include/components/IComponent.h
		include/components/Menubar.h
		include/components/Dock.h
		src/components/Dock.cpp
		src/components/Menubar.cpp
)

add_executable(GibEditor
  ${SIMPLEINI_FILES}
  ${IMGUI_FILES}
  ${NFD_FILES}
  ${COMPONENT_FILES}
  include/Observer.h
  include/UnixDirectoryChangeObserver.h
  include/WindowsDirectoryChangeObserver.h
  include/Editor.h
  include/Main.h
  
  src/UnixDirectoryChangeObserver.cpp
  src/WindowsDirectoryChangeObserver.cpp
  src/Editor.cpp
  src/Main.cpp
  ${SHADER_FILES})

source_group("Shaders" FILES ${SHADER_FILES})
source_group("Components" FILES ${COMPONENT_FILES})

target_link_libraries(GibEditor GibEngine ${GTK3_LIBRARIES})

add_custom_command(TARGET GibEditor PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:GibEditor>/Assets)

add_dependencies(GibEditor GibEngine)