/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */
#include "vehicle.hpp"
#include "player.hpp"

player::player() : vehicle()
{
}

player::player(vehicle &v): vehicle(v)
{
}

player::player(vehicle v): vehicle(v)
{
}

player::~player()
{
}

std::string player::info()
{
    return "player";
}