/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */
#include "vehicle.hpp"
#include <cassert>
#include <QOpenGLFunctions>
bool vehicle::texture_loaded = false;

vehicle::vehicle(/* args */) : Circle2D(0.1)
{
}

vehicle::~vehicle()
{
}

void vehicle::render()
{
	assert((vehicle::poly_count % 8) == 0);
	auto point_center = this->center();
	auto center = point_center.point();
	std::vector<std::array<float, 2>> vtx(vehicle::poly_count);

	glColor3f(colors[0] / 255.0f, colors[1] / 255.0f, colors[2] / 255.0f);
	// glBegin(GL_LINE_LOOP);
	glBegin(GL_POLYGON);
	// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	// glEnableVertexAttribArray(2);
	for (size_t i = 0; i < vehicle::poly_count; i++)
	{
		auto o = (this->at((float)(i) / ((float)vehicle::poly_count)) - point_center).point();
		
		glVertex2f(center[0] + o[0], center[1] + o[1]); // not the most optimal approach, I could've done that with just an 1/8 of a points
		
		glTexCoord2f(0.5 + o[0] / (this->radius * 2.f), 0.5f + o[1] / (this->radius * 2.f)); // not the most optimal approach, I could've done that with just an 1/8 of a points
	}
	// glDisableVertexAttribArray(2);
	glEnd();
}

void vehicle::move(float dx, float dy)
{
	this->rotate(dx);
	auto vec = Vect2D(this->center(), this->at(_rotation)) / 10 * dy;
	this->reposition(vec.d(0), vec.d(1));
}

Point2D vehicle::predict(float dx, float dy)
{
	float rotation = _rotation + dx;
	return ((Vect2D(this->center(), this->at(_rotation)) / 10 * dy)).get_point();
}

void vehicle::place(float x, float y)
{
	Circle2D::place(x, y);
}

void vehicle::rotate(float a)
{
	_rotation += a;
	_rotation -= floor(_rotation);
}

std::string vehicle::info()
{
	return "vehicle";
}

Point2D vehicle::center()
{
	return Circle2D::center(*this);
}

std::variant<Circle2D, std::vector<Segment>> vehicle::formula()
{
	return (Circle2D) * this;
};