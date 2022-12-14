//
// Created by Piotr Chrusciel on 01.09.22.
//
#include "GameManager.h"

GameManager::GameManager(
        unsigned int _size,
        bool random,
        const std::string& filePath,
        bool withGfx,
        bool withShaders,
        unsigned int resolution
) {
    size = _size;

    std::vector<std::vector<bool>> initialGameState;

    if (random) {
        generate_random(initialGameState);
    }

    game = new Game(size, initialGameState);

    if (withGfx) {
        renderer = new OpenGLRenderer(resolution, game);
    } else if (withShaders) {
        renderer = new OpenGLShaderRenderer(resolution, game);
    } else {
        renderer = new TerminalRenderer(game);
    }

}

void GameManager::start() {
    try {
        renderer->init(size);
    } catch (std::exception& e) {
        throw std::runtime_error("Failed to initialize renderer: " + std::string(e.what()));
    }
}

void GameManager::generate_random(std::vector<std::vector<bool>> &initialGameState) {
    std::default_random_engine defEngine;
    std::uniform_int_distribution<int> random_alive(0,100);

    for (int i=0; i<size; i++) {
        std::vector<bool> row;

        for (int j=0; j<size; j++) {

            if (random_alive(defEngine) > 100 - DENSITY) {
                row.push_back(true);
            } else {
                row.push_back(false);
            }
        }
        initialGameState.push_back(row);
    }
}