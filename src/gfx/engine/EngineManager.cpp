//
// Created by Piotr Chrusciel on 22.09.22.
//

#include "EngineManager.h"

void EngineManager::initEngine() {
    if(!glfwInit()){
        throw std::runtime_error("Failed to init GLFW");
    }

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Important for Mac os
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

GLFWwindow* EngineManager::createWindow(int width, int height,const char* title) {
    GLFWwindow* window= glfwCreateWindow(width, height, title, NULL, NULL);

    // Error check if the window fails to create
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to crate a window");
    }

    glfwGetFramebufferSize(window, &width, &height);
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);
    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, width, height);

    return window;
}

void EngineManager::clearBg(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    // Specify the color of the background
    glClearColor(r, g, b, a);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
}

void EngineManager::clearAndSwap(GLFWwindow* window) {
    // Take care of all GLFW events
    glfwPollEvents();
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);
}

bool EngineManager::shouldClose(GLFWwindow* window) {
    return glfwWindowShouldClose(window);
}

void EngineManager::destroy(GLFWwindow *window) {
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
}
