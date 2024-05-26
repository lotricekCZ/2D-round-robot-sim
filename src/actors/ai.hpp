/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/

#include "vehicle.hpp"

#ifndef AI_HPP
#define AI_HPP

class ai: public vehicle
{
private:
	int patience; // number of retries before changing mind
public:
	ai(/* args */);
	ai(vehicle &);
	std::string info() override;
	~ai();
	using vehicle::render;

};


#endif