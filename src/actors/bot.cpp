/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */

#include "bot.hpp"

bot::bot() : vehicle()
{
    _rotation = (random() % 1000) / 1000.0f;
}

bot::bot(vehicle &v) : vehicle(v)
{
    _rotation = (random() % 1000) / 1000.0f;
}

bot::~bot()
{
}

std::string bot::info()
{
    return "bot";
}