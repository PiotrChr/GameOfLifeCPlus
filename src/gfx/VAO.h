//
// Created by Piotr Chrusciel on 06.09.22.
//

#ifndef GAMEOFLIFECPLUS_VAO_H
#define GAMEOFLIFECPLUS_VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
    GLuint ID;
    VAO();

    void linkVBO(VBO* VBO, GLuint layout);
    void bind();
    void unbind();
    void destroy();
};


#endif //GAMEOFLIFECPLUS_VAO_H
