/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */
#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <typeinfo>
#include <vector>
#include <variant>
#include <cinttypes>
#include "../shapes/Segment.hpp"
#include "../shapes/TPoint.hpp"
#include "../shapes/TVector.hpp"

#include <QOpenGLFunctions>

class renderable
{
private:
	static uint32_t ID_incrementor;

protected:
	enum
	{
		vehicle,
		obstacle
	};
	union
	{
		uint32_t ID : 24; // unique identifier
		uint8_t colors[3];
	};
	float _rotation = 0;

public:
	static void reset();
	renderable(/* args */);
	~renderable();
	uint32_t id() { return ID; };
	float rotation() { return _rotation; };
	void set_rotation(float rot) { _rotation = rot; };
	virtual std::string info() = 0;
	virtual void render() = 0;
	Vect2D distance(renderable &r);
	Vect2D distance(Point2D p);
	Points2D intersection(renderable &r);
	virtual Point2D predict(float dx, float dy) = 0;
	virtual std::variant<Circle2D, std::vector<Segment>> formula() = 0;
	virtual void move(float dx, float dy) = 0;
	virtual void place(float x = 0, float y = 0) = 0;
	virtual void rotate(float a = 0) = 0;
	virtual Point2D center() = 0;
};

#endif