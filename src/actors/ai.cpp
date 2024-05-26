/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/

#include "ai.hpp"

ai::ai() : vehicle()
{
    patience = 255 + random() % 1024;
}

ai::ai(vehicle &v): vehicle(v)
{
    patience = 255 + random() % 1024;
}

ai::~ai()
{
}

std::string ai::info()
{
	return "ai";
}