//
// Created by Piotr Chrusciel on 21.09.22.
//

#ifndef GAMEOFLIFECPLUS_OPENGLSHADERRENDERER_H
#define GAMEOFLIFECPLUS_OPENGLSHADERRENDERER_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "../../Game.h"
#include "../engine/EngineManager.h"

class OpenGLShaderRenderer : public Renderer {
private:
    Game* game;
    sf::RenderWindow* window;
    unsigned int resolution;
    std::vector<std::vector<bool>> state;
public:
    OpenGLShaderRenderer(unsigned int resolution, Game* game);
    ~OpenGLShaderRenderer();
    int init(unsigned int _size) override;
    void renderState(std::vector<std::vector<bool>> state) override;
};


#endif //GAMEOFLIFECPLUS_OPENGLSHADERRENDERER_H
