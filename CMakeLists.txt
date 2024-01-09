cmake_minimum_required(VERSION 3.10)
project(LearnGL)
cmake_policy(SET CMP0072 NEW)

add_executable(hello
    vendor/stb_image.h
    vendor/glad/glad.h
    vendor/glad/glad.c
    src/include/Shader.hpp
    src/include/ShaderProgram.hpp
    src/include/Camera.hpp

    src/ShaderProgram.cpp
    src/Shader.cpp
    src/hello.cpp
)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(hello glfw OpenGL::GL)

add_custom_command(TARGET hello POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders
                ${CMAKE_CURRENT_BINARY_DIR}/shaders)