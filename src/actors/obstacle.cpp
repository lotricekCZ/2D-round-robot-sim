/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */

#ifndef M_SQRT1_2f
#define M_SQRT1_2f 0.70710678118654752440f
#endif

#include "obstacle.hpp"
#include <cmath>
obstacle::obstacle(/* args */) : renderable()
{
	place();
}

obstacle::~obstacle()
{
}

void obstacle::render()
{
	glColor3f(colors[0] / 255.0f, colors[1] / 255.0f, colors[2] / 255.0f);
	glBegin(GL_QUADS);
	for (auto i : bounds)
	{
		auto o = i.point();
		glVertex2f(o[0], o[1]); // not the most optimal approach, I could've done that with just an 1/8 of a points
	}
	glEnd();
}

void obstacle::move(float dx, float dy)
{
	auto o = obstacle_center.point();
	o[0] += dx;
	o[1] += dy;
	place(o[0], o[1]);
}

void obstacle::place(float x, float y)
{
	obstacle_center.point(std::array<float, 2>{x, y});
	for (size_t i = 0; i < bounds.size(); i++)
	{
		bounds.at(i) = Circle2D(edge_size * M_SQRT1_2f, obstacle_center).at((i * 0.25) + 0.125 + _rotation);
	}
}

void obstacle::rotate(float a)
{
	_rotation += a;
	_rotation -= floor(_rotation);
	move(0, 0);
}

std::string obstacle::info()
{
	return "obstacle";
}

Point2D obstacle::center()
{
	return obstacle_center;
}

std::variant<Circle2D, std::vector<Segment>> obstacle::formula()
{
	std::vector<Segment> ret;
	for (size_t i = 0; i < bounds.size(); i++)
	{
		ret.emplace_back(bounds.at(i), bounds.at((i + 1) % bounds.size()));
	}
	return ret;
};

Point2D obstacle::predict(float dx, float dy)
{
	return obstacle_center + Point2D(dx, dy);
};

void obstacle::set_texture(GLuint id)
{
}

GLuint obstacle::get_texture()
{
	return -1;
}