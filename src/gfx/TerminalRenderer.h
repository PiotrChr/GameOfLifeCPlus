//
// Created by Piotr Chrusciel on 01.09.22.
//

#include <vector>
#include "Renderer.h"

#ifndef GAMEOFLIFECPLUS_TERMINALRENDERER_H
#define GAMEOFLIFECPLUS_TERMINALRENDERER_H


class TerminalRenderer: public Renderer {
public:
    void renderState(const std::vector<std::vector<bool>>& state) override;
    int init() override;
};


#endif //GAMEOFLIFECPLUS_TERMINALRENDERER_H
