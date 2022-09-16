//
// Created by Piotr Chrusciel on 01.09.22.
//

#include "OpenGLRenderer.h"

const GLfloat box[] = {
        -0.5, 0.5, 0,
        -0.5, -0.5, 0,
        0.5, -0.5, 0,

        -0.5, 0.5, 0,
        0.5, 0.5, 0,
        0.5, -0.5, 0,
};

OpenGLRenderer::OpenGLRenderer(unsigned int _resolution, Game* _game) {
    resolution = _resolution;
    game = _game;

}

int OpenGLRenderer::init(unsigned int _size) {
    size = _size;
    cellSize = 1.0f / float(size);

    // Initialize GLFW
    if(!glfwInit()){
        throw std::runtime_error("Failed to init GLFW");
    }

    // Tell GLFW what version of OpenGL we are using
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Important for Mac os
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
    window = glfwCreateWindow(resolution, resolution, "Game of life", NULL, NULL);

    // Error check if the window fails to create
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to crate a window");
    }

    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();

    std::cout << "GLAD loaded" << std::endl;

    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, resolution, resolution);
    std::cout << "Viewport set" << std::endl;

    grid = prepareGrid();
    std::cout << "Grid ready" << std::endl;

    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("default.vert", "default.frag");
    shaderProgram.activate();
    std::cout << "Shaders loaded" << std::endl;

    while(!glfwWindowShouldClose(window)) {
        game->update();
        state = game->getState();
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use

        for (unsigned int col=0; col<size; col++) {
            for (unsigned int row=0; row<size; row++) {
                if (state[col][row]) {
                    grid[col][row].draw();
                }
            }
        }
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);

        // Take care of all GLFW events
        glfwPollEvents();
    }

    for (unsigned int col=0; col<size; col++) {
        for (unsigned int row=0; row<size; row++) {
            grid[col][row].vao.destroy();
            grid[col][row].vbo.destroy();
        }
    }

    // EBO1.destroy();
    shaderProgram.destroy();

    return 0;
}

std::tuple<VAO, VBO> OpenGLRenderer::makeVao(GLfloat vertices[18], size_t vert_size) {
    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(vertices, vert_size);
    // Generates Element Buffer Object and links it to indices
    // EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.linkVBO(VBO1, 0);

    VAO1.unbind();
    VBO1.unbind();

    return {VAO1, VBO1};
}

cell OpenGLRenderer::newCell(unsigned int y, unsigned int x) {
    GLfloat vertices[18];
    std::copy(std::begin(box), std::end(box), std::begin(vertices));

    for (int i=0; i<18; i++) {
        GLfloat _position;

        if (i % 3 == 0) {
            _position = float(x) * cellSize;
        } else if (i % 3 == 1) {
            _position = float(y) * cellSize;
        } else {
            continue;
        }

        if (vertices[i] < 0) {
            vertices[i] = _position * 2.f - 1.f;
        } else {
            vertices[i] = (_position + cellSize) * 2.f - 1.f;
        }

        std::cout << _position << std::endl;
    }

    auto [vao, vbo] = makeVao(vertices, sizeof(vertices));

    return cell { vao, vbo, x, y };
}

std::vector<std::vector<cell>> OpenGLRenderer::prepareGrid() {
    for (unsigned int row=0; row<size; row++) {
        std::vector<cell> grid_row;
        for (unsigned int col=0; col<size; col++) {
            cell new_cell = newCell(row, col);
            grid_row.push_back(new_cell);
        }
        grid.push_back(grid_row);
    }

    return grid;
}

OpenGLRenderer::~OpenGLRenderer() {
    // Delete window before ending the program
    glfwDestroyWindow(window);

    // Terminate GLFW before ending the program
    glfwTerminate();
}
void OpenGLRenderer::renderState(std::vector<std::vector<bool>> _state) {
    state = _state;
}

void cell::draw() {
    vao.bind();
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);
}
