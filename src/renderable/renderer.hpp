/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <cinttypes>
#include <vector>
#include <memory>
#include "renderable.hpp"
#include "../actors/vehicle.hpp"
#include "../actors/obstacle.hpp"

class renderer
{
protected:
    friend class serializer;
    // friend class behaviour;
    std::vector<std::shared_ptr<renderable>> objects;
public:
    renderer(/* args */);
    ~renderer();
    void render();
    void add(std::shared_ptr<renderable> object);
};

#endif