//
// Created by Piotr Chrusciel on 06.09.22.
//

#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

void VAO::linkVBO(VBO* VBO, GLuint layout) {
    VBO->bind();
    // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*) nullptr);
    // Enable the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(layout);
    VBO->unbind();
}

void VAO::bind() {
    glBindVertexArray(ID);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::destroy() {
    glDeleteVertexArrays(1, &ID);
}