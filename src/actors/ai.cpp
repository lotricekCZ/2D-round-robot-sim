/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/

#include "ai.hpp"

ai::ai() : vehicle()
{
}

ai::ai(vehicle &v): vehicle(v)
{
}

ai::~ai()
{
}

std::string ai::info()
{
	return "ai";
}