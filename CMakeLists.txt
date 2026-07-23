cmake_minimum_required(VERSION 3.20)

project(OpenGL_learning)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
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
	src/Shader.cpp
	src/mat.cpp
	src/Camera.cpp
	src/stb_image.cpp
	src/Texture.cpp
	src/Mesh.cpp
	src/PointLight.cpp
)

target_include_directories(OpenGL_learning PRIVATE
	include
	external/stb
)

target_link_libraries(OpenGL_learning PRIVATE
	glfw
	glad
)

add_custom_command(TARGET OpenGL_learning POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:OpenGL_learning>/shaders
)

add_custom_command(TARGET OpenGL_learning POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:OpenGL_learning>/textures
)

target_link_options(OpenGL_learning PRIVATE
	-static
	-static-libgcc
	-static-libstdc++
)