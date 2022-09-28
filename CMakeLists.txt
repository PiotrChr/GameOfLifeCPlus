cmake_minimum_required(VERSION 3.23)
project(GameOfLifeCplus)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

include_directories("includes")

add_executable(GameOfLifeCplus main.cpp src/Game.cpp src/Game.h src/GameManager.cpp src/GameManager.h src/gfx/renderer/TerminalRenderer.cpp src/gfx/renderer/TerminalRenderer.h src/gfx/renderer/OpenGLRenderer.cpp src/gfx/renderer/OpenGLRenderer.h src/dot.h src/gfx/renderer/Renderer.h libs/glad.c src/gfx/shader/Shader.cpp src/gfx/shader/Shader.h src/gfx/engine/VBO.cpp src/gfx/engine/VBO.h src/gfx/engine/EBO.cpp src/gfx/engine/EBO.h src/gfx/engine/VAO.cpp src/gfx/engine/VAO.h resources/shaders/default.frag resources/shaders/default.vert src/gfx/renderer/OpenGLShaderRenderer.cpp src/gfx/renderer/OpenGLShaderRenderer.h src/gfx/engine/EngineManager.cpp src/gfx/engine/EngineManager.h)

target_link_libraries(GameOfLifeCplus glfw)
target_link_libraries(GameOfLifeCplus OpenGL::GL)

set(RESOURCE_FILES
    resources/shaders/default.frag
    resources/shaders/default.vert)

set_target_properties(GameOfLifeCplus PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_FRAMEWORK_IDENTIFIER org.cmake.ExecutableTarget
        RESOURCE "${RESOURCE_FILES}")

#target_link_libraries(GameOfLifeCplus "/usr/local/Cellar/glfw/3.3.8/lib/libglfw.3.3.dylib")