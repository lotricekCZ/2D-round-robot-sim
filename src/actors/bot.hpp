/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/

#include "vehicle.hpp"
#include <chrono>

#ifndef BOT_HPP
#define BOT_HPP

class bot: public vehicle
{
private:
public:
	bot(/* args */);
	bot(vehicle &);
	std::string info() override;
	~bot();
	using vehicle::render;

};


#endif