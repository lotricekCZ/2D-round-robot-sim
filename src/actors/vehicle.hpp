/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */
#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <QOpenGLFunctions>
#include <cinttypes>
#include <variant>
#include <vector>
#include "../shapes/TCircle.hpp"
#include "../shapes/TVector.hpp"
#include "../renderable/renderable.hpp"

class vehicle : public renderable, public Circle2D
{
private:
	// overall number of polygons circle will have
	const uint16_t poly_count = 32;
	const float radius = 0.1;
	static GLuint texture;
public:
	vehicle(/* args */);
	~vehicle();
	
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