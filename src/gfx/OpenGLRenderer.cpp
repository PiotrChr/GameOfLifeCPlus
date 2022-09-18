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

void OpenGLRenderer::initOpenGL() {
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

int OpenGLRenderer::init(unsigned int _size) {
    size = _size;
    cellSize = 2.0f / float(size);
    GLsizei width;
    GLsizei height;
    // Initialize GLFW
    initOpenGL();

    window = glfwCreateWindow(resolution, resolution, "Game of life", NULL, NULL);

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

    grid = prepareGrid();

    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("default.vert", "default.frag");
    shaderProgram.activate();

    while(!glfwWindowShouldClose(window)) {
        game->update();
        state = game->getState();
        // Specify the color of the background
        glClearColor(0, 0, 0, 1);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use

        // Draw all the living cells
        for (unsigned int col=0; col<size; col++) {
            for (unsigned int row=0; row<size; row++) {
                if (state[col][row]) {
                    grid[col][row]->draw();
                }
            }
        }

//        grid[size-1][size-1]->draw();
//
//        grid[size-1][size-3]->draw();

        // Take care of all GLFW events
        glfwPollEvents();
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
    }

    for (unsigned int col=0; col<size; col++) {
        for (unsigned int row=0; row<size; row++) {
            grid[col][row]->vao->destroy();
            grid[col][row]->vbo->destroy();
        }
    }

    // EBO1.destroy();
    shaderProgram.destroy();

    return 0;
}

std::tuple<VAO*, VBO*> OpenGLRenderer::makeVao(GLfloat* vertices, size_t vert_size) {
    // Generates Vertex Buffer Object and links it to vertices
    VBO* VBO1 = new VBO(vertices, vert_size);

    // Links VBO to VAO

    // Generates Vertex Array Object and binds it
    VAO* VAO1 = new VAO;
    VAO1->bind();

    VAO1->linkVBO(VBO1, 0);

    VAO1->unbind();
    VBO1->unbind();

    return {VAO1, VBO1};
}

Cell* OpenGLRenderer::newCell(unsigned int x, unsigned int y) {
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
            _position = _position - 1.f;
        } else {
            _position = (_position + cellSize) - 1.f;
        }

        vertices[i] = _position;
    }

    auto [vao, vbo] = makeVao(vertices, sizeof(vertices));

    return new Cell(vao, vbo, x, y);
}

std::vector<std::vector<Cell*>> OpenGLRenderer::prepareGrid() {
    for (unsigned int row=0; row<size; row++) {
        std::vector<Cell*> grid_row;
        for (unsigned int col=0; col<size; col++) {
            Cell* new_cell = newCell(col, row);
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

Cell::Cell(VAO* _vao, VBO* _vbo, unsigned int _x, unsigned int _y) {
    vao = _vao;
    vbo = _vbo;
    x = _x;
    y = _y;
}

void Cell::draw() {
    vao->bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
