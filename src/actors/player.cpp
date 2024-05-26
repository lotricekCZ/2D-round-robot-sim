/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */
#include "vehicle.hpp"
#include "player.hpp"

GLuint player::texture = -1;

player::player() : vehicle()
{
}

player::player(vehicle &v): vehicle(v)
{
}

player::~player()
{
}

std::string player::info()
{
	return "player";
}

void player::set_texture(GLuint id){
	player::texture = id;
}

GLuint player::get_texture(){
	return player::texture;
}