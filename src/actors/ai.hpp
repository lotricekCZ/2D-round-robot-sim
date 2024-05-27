/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/

#include "bot.hpp"
#include "../renderable/renderable.hpp"

#include <chrono>
#include <memory>

#ifndef AI_HPP
#define AI_HPP

class ai
{
private:
	int patience; // number of retries before changing mind
public:
	struct {
		float dx = 0;
		float dy = 0;
		std::chrono::time_point<std::chrono::steady_clock> next_change;
	} controls;
	std::shared_ptr<renderable> attached;
	ai(/* args */);
	void attach(std::shared_ptr<renderable> &);
	void steer();
	~ai();
};


#endif