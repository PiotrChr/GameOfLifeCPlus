//
// Created by Piotr Chrusciel on 01.09.22.
//
#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <tuple>
#include "Renderer.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "shader/Shader.h"
#include "../Game.h"

#ifndef GAMEOFLIFECPLUS_OPENGLRENDERER_H
#define GAMEOFLIFECPLUS_OPENGLRENDERER_H

class Cell {
public:
    Cell(VAO* vao, VBO* vbo, unsigned int x, unsigned int y);
    VAO* vao;
    VBO* vbo;
    unsigned int x;
    unsigned int y;
    void draw();
};

class OpenGLRenderer : public Renderer {
private:
    GLFWwindow* window;
    unsigned int size;
    unsigned int resolution;
    float cellSize;
    std::vector<std::vector<Cell*>> grid;
    std::vector<std::vector<bool>> state;
    std::vector<std::vector<Cell*>> prepareGrid();
    Cell* newCell(unsigned int x, unsigned int y);
    static std::tuple<VAO*, VBO*> makeVao(GLfloat* vertices, size_t vert_size);
    Game* game;
    static void initOpenGL();
public:
    OpenGLRenderer(unsigned int resolution, Game* game);
    ~OpenGLRenderer();
    int init(unsigned int _size) override;
    void renderState(std::vector<std::vector<bool>> state) override;
};


#endif //GAMEOFLIFECPLUS_OPENGLRENDERER_H
