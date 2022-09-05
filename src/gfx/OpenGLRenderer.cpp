//
// Created by Piotr Chrusciel on 01.09.22.
//

#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer() {

}

int OpenGLRenderer::init() {
    if(!glfwInit()){
        throw std::runtime_error("Failed to init GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(800, 800, "Game of life", NULL, NULL);

    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to crate a window");
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    return 0;
}

OpenGLRenderer::~OpenGLRenderer() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
void OpenGLRenderer::renderState(const std::vector<std::vector<bool>>& state) {
    std::cout << "not implemented" << std::endl;
}
