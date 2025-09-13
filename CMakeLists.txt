cmake_minimum_required(VERSION 3.10)
project(GameBoy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
	${CMAKE_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp
)

source_group(TREE ${CMAKE_SOURCE_DIR}/src/ PREFIX "Source Files" FILES ${SOURCES})
source_group(TREE ${CMAKE_SOURCE_DIR}/src/ PREFIX "Header Files" FILES ${HEADERS})

add_executable(GameBoy ${SOURCES} ${HEADERS})

target_include_directories(GameBoy PRIVATE
	src
)

add_library(imgui STATIC 
	dep/imgui/imgui.cpp
	dep/imgui/imgui_demo.cpp
	dep/imgui/imgui_draw.cpp
	dep/imgui/imgui_tables.cpp
	dep/imgui/imgui_widgets.cpp
	dep/imgui/backends/imgui_impl_sdl3.cpp
	dep/imgui/backends/imgui_impl_sdlrenderer3.cpp
)

target_include_directories(imgui PUBLIC
	dep/imgui
	dep/imgui/backends
)

add_subdirectory(dep/sdl)

target_link_libraries(imgui PUBLIC SDL3::SDL3)

target_link_libraries(GameBoy PRIVATE imgui)