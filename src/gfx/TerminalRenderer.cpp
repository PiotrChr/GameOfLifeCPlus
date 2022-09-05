//
// Created by Piotr Chrusciel on 01.09.22.
//

#include "TerminalRenderer.h"
#include <iostream>

int TerminalRenderer::init() {
    return 0;
}

void TerminalRenderer::renderState(const std::vector<std::vector<bool>>& state) {
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