//
// Created by Piotr Chrusciel on 06.09.22.
//

#ifndef GAMEOFLIFECPLUS_EBO_H
#define GAMEOFLIFECPLUS_EBO_H

#include <glad/glad.h>

class EBO {
public:
    GLuint ID;
    EBO(GLuint* indices, GLsizeiptr size);

    void bind();
    void unbind();
    void destroy();
};


#endif //GAMEOFLIFECPLUS_EBO_H
