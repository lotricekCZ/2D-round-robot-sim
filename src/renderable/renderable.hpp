/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <vector>
#include <cinttypes>

using plane = std::vector<std::vector<uint8_t>>;

class renderable
{
private:
    /* data */
public:
    renderable(/* args */);
    ~renderable();
    virtual void render(plane &);
};

#endif