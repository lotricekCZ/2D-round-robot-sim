#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "../renderable/renderable.hpp"
#include "../shapes/TCircle.hpp"

class player: public renderable, public Circle2D
{
private:
    /* data */
public:
    void render(plane &);
    player(/* args */);
    ~player();
};


#endif