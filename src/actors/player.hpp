/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "../renderable/renderable.hpp"
#include "vehicle.hpp"

class player : public vehicle
{
private:
	static GLuint texture;
public:
	std::string info() override;
	player(/* args */);
	player(vehicle &);
	// player(vehicle);
	~player(); // glBindTexture(GL_TEXTURE_2D, texture_id_bot);
	using vehicle::render;
	void set_texture(GLuint id) override;
	GLuint get_texture() override;
};

#endif