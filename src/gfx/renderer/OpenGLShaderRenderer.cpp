//
// Created by Piotr Chrusciel on 21.09.22.
//

#include "OpenGLShaderRenderer.h"

OpenGLShaderRenderer::OpenGLShaderRenderer(unsigned int _resolution, Game* _game) {
    resolution = _resolution;
    game = _game;
}

int OpenGLShaderRenderer::init(unsigned int _size) {
//    EngineManager::initEngine();

//    window = EngineManager::createWindow(resolution, resolution, "Game of Life");
    //create the renderwindow and enable VSync. Else the thing will reach
    //blazing high FPS (10000+) at low resolutions
    window = new sf::RenderWindow(sf::VideoMode(resolution,resolution),"Game of Life GLSL");
    window->setVerticalSyncEnabled(true);
    //    window->setFramerateLimit(5);

    //used to calculate the scrolling offset
    bool drag=false;
    sf::Glsl::Vec2 current_offset;
    sf::Glsl::Vec2 dragOrigin;

    //we want to count the current generation...
    long long generation=0;

    float zoom=1.0;
    sf::Clock uptime;
    sf::Event event;

    //we use a simple Quad as canvas, that fills the whole window
    sf::VertexArray canvas(sf::Quads,4);
    canvas[0]=sf::Vertex(sf::Vector2f(0,0),sf::Color::White,sf::Vector2f(0,0));
    canvas[1]=sf::Vertex(sf::Vector2f(0,resolution),sf::Color::White,sf::Vector2f(0,resolution));
    canvas[2]=sf::Vertex(sf::Vector2f(resolution,resolution),sf::Color::White,sf::Vector2f(resolution,resolution));
    canvas[3]=sf::Vertex(sf::Vector2f(resolution,0),sf::Color::White,sf::Vector2f(resolution,0));

    //we need two Rendertextures to hold the current and the coming generation
    //Also we enable Repeated, so we have an "infinite" Grid
    auto *nextGen = new sf::RenderTexture;
    nextGen->create(resolution, resolution, sf::ContextSettings());
    nextGen->setRepeated(true);

    auto *currentGen = new sf::RenderTexture;
    currentGen->create(resolution, resolution, sf::ContextSettings());
    currentGen->setRepeated(true);

    //Init the current generation with a randowm pattern.
    //We can't access the RenderTextures Directly from here.
    //So let's create a new sf::Image first and fill it with data.
    auto *initState = new sf::Image;
    initState->create(resolution,resolution);
    for(unsigned int y=0; y<resolution; y++)
        for(unsigned int x=0; x<resolution; x++)
        {
            unsigned char color=(rand()%2)*255;
            initState->setPixel(x,y,sf::Color(color,color,color,255));
        }

    //Create a texture and copy the Image there. After this the texture is rendered to
    //the RenderTexture
    auto *upload = new sf::Texture;
    upload->loadFromImage(*initState);
    currentGen->draw(canvas,upload);
    currentGen->display();

    //We don't need the initial sf::Image and texture anymore. So we free up the memory.
    delete upload;
    delete initState;

    //load and compile neccesary shaders, also init the uniforms in the shaders
    sf::Shader shader;
    shader.loadFromFile("res/gof.vert","res/gof.frag");
    shader.setUniform("resolution",float(resolution));

    sf::Shader dispShader;
    dispShader.loadFromFile("res/gof.vert","res/gof_display.frag");
    dispShader.setUniform("zoom",zoom);

    //create some states, so SFML can bind shaders and Texture to OpenGL
    sf::RenderStates states;
    states.shader=&shader;
    states.texture=&currentGen->getTexture();

    sf::RenderStates dispStates;
    dispStates.shader=&dispShader;

    while(window->isOpen())
    {
        //Process window events.
        //You can adjust the zoom by the Mousewheel or scroll around while pressing
        //the left mousebutton
        while (window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::MouseWheelScrolled:
                    zoom+=event.mouseWheelScroll.delta*.1;
                    zoom=zoom<.25f?.25f:zoom;
                    dispShader.setUniform("zoom",zoom);
                    break;
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button==sf::Mouse::Left)
                    {
                        drag=true;
                        dragOrigin=sf::Glsl::Vec2(sf::Mouse::getPosition());
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if(event.mouseButton.button==sf::Mouse::Left)
                    {
                        drag=false;
                        dragOrigin=sf::Glsl::Vec2(0,0);
                    }
                    break;
                default:
                    break;

            }
        }

        //"Draw" the current generation to the next generation.
        //The Game of Life simulation is happening here.
        nextGen->draw(canvas,states);
        nextGen->display();

        //Now swap the pointers to the Renderbuffers, so we do not need to copy any
        //texture data around.
        sf::RenderTexture *swap=currentGen;
        currentGen=nextGen;
        nextGen=swap;

        //if the left mousebutton is pressed, we need to calculate the scrolling offset
        if(drag)
        {
            sf::Glsl::Vec2 offset;
            offset=sf::Glsl::Vec2(sf::Mouse::getPosition());
            offset=dragOrigin-offset;
            offset.y*=-1;
            offset.x/=resolution;
            offset.y/=resolution;
            current_offset+=offset;
            dragOrigin=sf::Glsl::Vec2(sf::Mouse::getPosition());
        }
        //Prepare the textures and uniforms, so they can be drawn to our window
        dispStates.texture=&currentGen->getTexture();
        dispShader.setUniform("offset",current_offset);

        //Now we can draw everything
        window->draw(canvas,dispStates);
        window->display();

        generation++;
    }

    //Clean up after yourself. ;)
    delete currentGen;
    delete nextGen;
    delete window;

    return 0;
}

OpenGLShaderRenderer::~OpenGLShaderRenderer() {
//    EngineManager::destroy(window);
}

void OpenGLShaderRenderer::renderState(std::vector<std::vector<bool>> _state) {
    state = _state;
}

