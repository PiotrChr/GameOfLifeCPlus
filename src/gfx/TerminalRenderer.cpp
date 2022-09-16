//
// Created by Piotr Chrusciel on 01.09.22.
//

#include "TerminalRenderer.h"
#include <iostream>

TerminalRenderer::TerminalRenderer(Game* _game) {
    game = _game;
}

int TerminalRenderer::init(unsigned int _size) {
    renderState(game->getState());

    while(true) {
        renderState(game->getState());
    }
}

void TerminalRenderer::renderState(std::vector<std::vector<bool>> state) {
    system("clear");
    std::cout << "\n";

    for (const std::vector<bool>& row : state) {
        for (bool alive : row) {
            if (alive) {
                std::cout << "  *";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << "\n";
    }

}