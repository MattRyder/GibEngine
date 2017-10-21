cmake_minimum_required(VERSION 2.6)
project(Editor CXX)

set(EDITOR_INCLUDE_DIRS
  ${PROJECT_SOURCE_DIR}/include
  ${ENGINE_INCLUDE_DIRS}
  CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

include_directories(${EDITOR_INCLUDE_DIRS})

file(GLOB_RECURSE SHADER_FILES ${CMAKE_SOURCE_DIR}/Assets/Shaders/*.glsl)

include_directories("imgui/" "imgui/examples/opengl3_example/")
file(
	GLOB IMGUI_FILES
		"imgui/imgui.cpp"
		"imgui/imgui_draw.cpp"
    "imgui/imgui_demo.cpp"
    "imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp"
    "imgui/examples/opengl3_example/imgui_impl_glfw_gl3.h"
		"imgui/*.h"
)
source_group(ImGui FILES ${IMGUI_FILES})

add_executable(GibEditor
  ${IMGUI_FILES}
  include/Editor.h
  include/Main.h
  src/Editor.cpp
  src/Main.cpp
  ${SHADER_FILES})

source_group("Shaders" FILES ${SHADER_FILES})

target_link_libraries(GibEditor GibEngine)

add_custom_command(TARGET GibEditor PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/Assets $<TARGET_FILE_DIR:GibEditor>/Assets)

add_dependencies(GibEditor GibEngine)