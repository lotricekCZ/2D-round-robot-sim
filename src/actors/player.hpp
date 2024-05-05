/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "../renderable/renderable.hpp"
#include "vehicle.hpp"

class player: public vehicle
{
private:
    /* data */
public:
    std::string info() override;
    player(/* args */);
    ~player();
};


#endif