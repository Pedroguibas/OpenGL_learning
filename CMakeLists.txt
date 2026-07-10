cmake_minimum_required(VERSION 3.20)

project(OpenGL_learning)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/glfw)

add_library(glad
	external/glad/src/gl.c
)

target_include_directories(glad PUBLIC
	external/glad/include
)

add_executable(OpenGL_learning
	src/main.cpp
)

target_link_libraries(OpenGL_learning PRIVATE
	glfw
	glad
)