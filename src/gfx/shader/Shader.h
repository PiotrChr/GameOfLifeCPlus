//
// Created by Piotr Chrusciel on 05.09.22.
//

#ifndef GAMEOFLIFECPLUS_SHADER_H
#define GAMEOFLIFECPLUS_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader {
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);
    void activate();
    void destroy();
};


#endif //GAMEOFLIFECPLUS_SHADER_H
