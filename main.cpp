#include <iostream>
#include <sstream>
#include "src/GameManager.h"


const std::string commands[5] = {
        "--size",
        "-random",
        "--file",
        "-gfx",
        "--res"
};

int main(int argc, char *argv[]) {
    bool random = false;
    unsigned int size = 100;
    std::string filePath;
    bool withGfx = false;
    unsigned int resolution = 1000;

    if (argc==1) {
        std::cout << "Error: Missing required arguments" << std::endl;
        return 1;
    }

    std::cout << argv[0] << std::endl;

    for (int i=0; i<argc; i++) {
        if (argv[i] == commands[0]) {
            std::istringstream iss( argv[i+1] );
            iss >> size;
            std::cout << "Setting size to: " << size << std::endl;
        }
        if (argv[i] == commands[1]) {
            std::cout << "Generating random map. " << std::endl;
            random = true;
        }
        if (argv[i] == commands[2]) {
            filePath = *argv[i+1];
            std::cout << "Opening a map: " << filePath << std::endl;
        }
        if (argv[i] == commands[3]) {
            std::cout << "Running with OpenGL. " << std::endl;
            withGfx = true;
        }
        if (argv[i] == commands[4]) {
            std::istringstream iss( argv[i+1] );
            iss >> resolution;
            std::cout << "Setting resolution to: " << resolution << std::endl;
        }

    }

    if (!random && filePath.empty()) {
        std::cout << "Error: Either -random or -file has to be set." << std::endl;
        return 1;
    }

    try {
        auto *gameManager = new GameManager(size, random, filePath, withGfx, resolution);
        gameManager->start();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
