cmake_minimum_required(VERSION 3.10)
project(LearnGL)
cmake_policy(SET CMP0072 NEW)

set(APP_NAME hello)

set(IMGUI_SOURCES
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_widgets.cpp
)

set(IMGUI_DIR vendor/imgui)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ..)

add_executable(hello
    vendor/stb_image.h
    vendor/glad/glad.h
    vendor/glad/glad.c
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp
    src/include/GlDeps.hpp
    src/include/Utils.h
    src/include/Mesh.hpp
    src/include/Shader.hpp
    src/include/ShaderProgram.hpp
    src/include/Camera.hpp
    src/include/App.hpp
    src/include/Primitives.hpp
    src/include/GameObject.hpp
    
    src/include/SnakeGame/Field.hpp
    src/include/SnakeGame.hpp

    src/Utils.cpp
    src/Mesh.cpp
    src/ShaderProgram.cpp
    src/Shader.cpp
    src/App.cpp
    
    src/SnakeGame/SnakeGame.cpp

    src/hello.cpp
)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(hello glfw OpenGL::GL)

add_custom_command(TARGET hello POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders
                ${CMAKE_CURRENT_BINARY_DIR}/shaders)