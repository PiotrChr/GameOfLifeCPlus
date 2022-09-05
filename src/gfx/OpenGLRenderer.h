//
// Created by Piotr Chrusciel on 01.09.22.
//
#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"

#ifndef GAMEOFLIFECPLUS_OPENGLRENDERER_H
#define GAMEOFLIFECPLUS_OPENGLRENDERER_H


class OpenGLRenderer : public Renderer {
private:
    GLFWwindow* window;
public:
    OpenGLRenderer();
    ~OpenGLRenderer();
    int init() override;
    void renderState(const std::vector<std::vector<bool>>& state) override;
};


#endif //GAMEOFLIFECPLUS_OPENGLRENDERER_H
