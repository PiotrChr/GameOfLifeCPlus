//
// Created by Piotr Chrusciel on 06.09.22.
//

#include "EBO.h"

EBO::EBO(GLuint *indices, GLsizeiptr size) {
    glGenBuffers(1, &ID);
    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    // Introduce the vertices into the VBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::destroy() {
    glDeleteBuffers(1, &ID);
}