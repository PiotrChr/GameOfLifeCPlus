//
// Created by Piotr Chrusciel on 01.09.22.
//

#include <vector>
#include "Renderer.h"
#include "../Game.h"

#ifndef GAMEOFLIFECPLUS_TERMINALRENDERER_H
#define GAMEOFLIFECPLUS_TERMINALRENDERER_H


class TerminalRenderer: public Renderer {
private:
    Game* game;
public:
    TerminalRenderer(Game* game);
    void renderState(std::vector<std::vector<bool>> state) override;
    int init(unsigned int _size) override;
};


#endif //GAMEOFLIFECPLUS_TERMINALRENDERER_H
