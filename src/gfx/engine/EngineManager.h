//
// Created by Piotr Chrusciel on 22.09.22.
//

#ifndef GAMEOFLIFECPLUS_ENGINEMANAGER_H
#define GAMEOFLIFECPLUS_ENGINEMANAGER_H

#include <tuple>
#include <cmath>
#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class EngineManager {
public:
    static void initEngine();
    static GLFWwindow* createWindow(int width, int height, const char* title);
    static void clearBg(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    static void clearAndSwap(GLFWwindow* window);
    static bool shouldClose(GLFWwindow* window);
    static void destroy(GLFWwindow* window);
};


#endif //GAMEOFLIFECPLUS_ENGINEMANAGER_H
