//
// Created by Piotr Chrusciel on 01.09.22.
//

#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

#ifndef GAMEOFLIFECPLUS_GAME_H
#define GAMEOFLIFECPLUS_GAME_H


class Game {
private:
    std::vector<std::vector<bool>> state;
    std::vector<std::vector<bool>> newState;
    unsigned int size;
    unsigned int checkNeighbours(unsigned int i, unsigned int j);
public:
    Game(unsigned int size, std::vector<std::vector<bool>> initialGameState);
    void update();
    std::vector<std::vector<bool>> getState();
};


#endif //GAMEOFLIFECPLUS_GAME_H
