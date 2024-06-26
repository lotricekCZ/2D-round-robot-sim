/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */
#include "../renderable/renderable.hpp"
#include "../shapes/Segment.hpp"
#include "../shapes/TPoint.hpp"
#include <array>
#include <string>
#include <variant>
#include <vector>
#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

class obstacle : public renderable
{
private:
	float edge_size = 0.2;
	Point2D obstacle_center;

public:
	std::array<Point2D, 4> bounds;
	obstacle(/* args */);
	~obstacle();
	std::string info() override;
	void render() override;
	void place(float x = 0, float y = 0) override;
	void rotate(float a = 0) override;
	void move(float dx = 0, float dy = 0) override;
	Point2D predict(float dx, float dy) override;
	std::variant<Circle2D, std::vector<Segment>> formula() override;
	Point2D center() override;
	void set_texture(GLuint id) override;
	GLuint get_texture() override;
};

#endif