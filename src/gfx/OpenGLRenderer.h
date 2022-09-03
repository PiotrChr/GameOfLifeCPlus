//
// Created by Piotr Chrusciel on 01.09.22.
//
#include <vector>
#include <iostream>
#include "Renderer.h"

#ifndef GAMEOFLIFECPLUS_OPENGLRENDERER_H
#define GAMEOFLIFECPLUS_OPENGLRENDERER_H


class OpenGLRenderer : public Renderer {
public:
    void renderState(const std::vector<std::vector<bool>>& state) override;
};


#endif //GAMEOFLIFECPLUS_OPENGLRENDERER_H
