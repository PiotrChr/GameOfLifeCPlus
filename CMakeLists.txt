cmake_minimum_required(VERSION 3.23)
project(GameOfLifeCplus)

set(CMAKE_CXX_STANDARD 14)

add_executable(GameOfLifeCplus main.cpp src/Game.cpp src/Game.h src/GameManager.cpp src/GameManager.h src/gfx/TerminalRenderer.cpp src/gfx/TerminalRenderer.h src/gfx/OpenGLRenderer.cpp src/gfx/OpenGLRenderer.h src/dot.h src/gfx/Renderer.h)
