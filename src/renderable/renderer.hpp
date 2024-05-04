/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <cinttypes>
#include <array>
#include <vector>
#include "renderable.hpp"

using plane = std::vector<std::vector<uint8_t>>;

class renderer
{
private:
    static uint16_t width;
    static uint16_t height;
    plane viewport;
public:
    renderer(/* args */);
    ~renderer();
};

#endif