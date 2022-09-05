cmake_minimum_required(VERSION 3.23)
project(GameOfLifeCplus)

set(CMAKE_CXX_STANDARD 14)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories("includes")

add_executable(GameOfLifeCplus main.cpp src/Game.cpp src/Game.h src/GameManager.cpp src/GameManager.h src/gfx/TerminalRenderer.cpp src/gfx/TerminalRenderer.h src/gfx/OpenGLRenderer.cpp src/gfx/OpenGLRenderer.h src/dot.h src/gfx/Renderer.h libs/glad.c)

target_link_libraries(GameOfLifeCplus glfw)
target_link_libraries(GameOfLifeCplus OpenGL::GL)


#target_link_libraries(GameOfLifeCplus "/usr/local/Cellar/glfw/3.3.8/lib/libglfw.3.3.dylib")