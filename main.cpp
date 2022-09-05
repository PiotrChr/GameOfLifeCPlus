#include <iostream>
#include <sstream>
#include "src/GameManager.h"


const std::string commands[4] = {
        "-size",
        "-random",
        "-file",
        "-gfx"
};

int main(int argc, char *argv[]) {
    bool random = false;
    unsigned int size = 100;
    std::string filePath;
    bool withGfx = false;

    if (argc==1) {
        std::cout << "Error: Missing required arguments" << std::endl;
        return 1;
    }

    std::cout << argv[0] << std::endl;

    for (int i=0; i<argc; i++) {
        if (argv[i] == commands[0]) {
            unsigned int _size;
            std::istringstream iss( argv[i+1] );
            iss >> size;
        }
        if (argv[i] == commands[1]) {
            random = true;
        }
        if (argv[i] == commands[2]) {
            filePath = *argv[i+1];
        }
        if (argv[i] == commands[3]) {
            withGfx = true;
        }
    }

    if (!random && filePath.empty()) {
        std::cout << "Error: Either -random or -file has to be set." << std::endl;
        return 1;
    }

    try {
        auto *gameManager = new GameManager(size, random, filePath, withGfx);
        gameManager->start();
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
