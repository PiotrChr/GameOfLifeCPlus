//
// Created by Piotr Chrusciel on 06.09.22.
//

#ifndef GAMEOFLIFECPLUS_VBO_H
#define GAMEOFLIFECPLUS_VBO_H

#include <glad/glad.h>

class VBO {
public:
    GLuint ID;
    VBO(GLfloat* vertices, GLsizeiptr size);

    void bind();
    void unbind();
    void destroy();
};


#endif //GAMEOFLIFECPLUS_VBO_H
