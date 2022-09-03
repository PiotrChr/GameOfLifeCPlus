//
// Created by Piotr Chrusciel on 01.09.22.
//

#include "Game.h"

Game::Game(unsigned int _size, std::vector<std::vector<bool>> initialState) {
    size = _size;
    state = initialState;
    newState = initialState;
}

std::vector<std::vector<bool>> Game::getState() {
    return newState;
}

unsigned int Game::checkNeighbours(unsigned int i, unsigned int j) {
    unsigned int neighbours = 0;

    for (unsigned int x= std::max((int)i-1, 0); x<std::min((int)i+2, (int)state.size()-1); x++) {
        for (unsigned int y=std::max((int)j-1, 0); y<std::min((int)j+2, (int)state.size()-1); y++) {
            if (state[x][y] && !(i==x && j==y)) neighbours++;
        }
    }

    return neighbours;
}

void Game::update() {
    // Using a for loop with index
    for(std::size_t i = 0; i < state.size(); ++i) {
        for(std::size_t j = 0; j < state.size(); ++j) {
            unsigned int neighbours = checkNeighbours(i, j);

            if (state[i][j]) {
                if (neighbours == 3 || neighbours == 2) {
                    newState[i][j] = true;
                } else {
                    newState[i][j] = false;
                }
            } else {
                if (neighbours != 3) {
                    newState[i][j] = false;
                } else {
                    newState[i][j] = true;
                }
            }
        }
    }

    state = newState;
}

