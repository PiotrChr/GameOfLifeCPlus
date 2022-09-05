//
// Created by Piotr Chrusciel on 03.09.22.
//

#ifndef GAMEOFLIFECPLUS_RENDERER_H
#define GAMEOFLIFECPLUS_RENDERER_H


class Renderer {
public:
    virtual void renderState(const std::vector<std::vector<bool>>& state) = 0;
    virtual int init() = 0;
};


#endif //GAMEOFLIFECPLUS_RENDERER_H
