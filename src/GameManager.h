//
// Created by Piotr Chrusciel on 01.09.22.
//
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <stdexcept>
#include "Game.h"
#include "gfx/Renderer.h"
#include "gfx/TerminalRenderer.h"
#include "gfx/OpenGLRenderer.h"

#define DENSITY 50
#define DEFAULT_DELAY 50

#ifndef GAMEOFLIFECPLUS_GAMEMANAGER_H
#define GAMEOFLIFECPLUS_GAMEMANAGER_H

class GameManager {
private:
    unsigned int size;
    Game *game;
    Renderer *renderer;
public:
    GameManager(unsigned int _size, bool _random, const std::string& _filePath, bool withGfx, unsigned int resolution);
    void start();
    void generate_random(std::vector<std::vector<bool>> &initialGameState);
};


#endif //GAMEOFLIFECPLUS_GAMEMANAGER_H
