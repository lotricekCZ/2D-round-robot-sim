/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <cinttypes>
#include <array>
#include <vector>
#include "renderable.hpp"


class renderer
{
protected:
    static uint16_t width;
    static uint16_t height;
    friend class renderable;
public:
    renderer(/* args */);
    ~renderer();
    void render();
};

#endif