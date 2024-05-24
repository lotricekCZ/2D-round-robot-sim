/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */
#include "renderer.hpp"
#include "renderable.hpp"
#include <algorithm>
#include <execution>

/**
 * @brief Constructs a new renderer object.
 *
 * Initializes a new renderer instance.
 */
renderer::renderer(/* args */)
{
}

/**
 * @brief Destroys the renderer object.
 *
 * Cleans up resources associated with the renderer instance.
 */
renderer::~renderer()
{
}

/**
 * @brief Adds a renderable object to the renderer.
 *
 * Adds a renderable object to the collection of objects managed by the renderer.
 *
 * @param object A shared pointer to the renderable object to be added.
 */
void renderer::add(std::shared_ptr<renderable> object)
{
    objects.push_back(std::move(object));
}

/**
 * @brief Renders all the renderable objects managed by the renderer.
 *
 * Renders all the renderable objects managed by the renderer concurrently.
 * This function iterates over the objects and calls their render() method in parallel.
 */
void renderer::render()
{
    std::for_each(std::execution::par, objects.begin(), objects.end(),
                  [&](auto &o)
                  { o->render(); });
}


std::optional<std::shared_ptr<renderable>> renderer::get_by_id(uint32_t id){
    for(auto o: objects)
        if(o->id() == id)
            return o;
    return {};
}


bool renderer::erase_by_id(uint32_t id){
    for (std::vector<std::shared_ptr<renderable>>::iterator it = objects.begin(); it != objects.end(); it++)
        if((*it)->id() == id){
            objects.erase(it);
            return true;
        }
    return false;
}