#include "Segment.hpp"
#include <variant>
#include <type_traits>
#include <cmath>
#include <cinttypes>

Segment::Segment(const Circle2D &formula, const std::array<float, 2> &range)
{
	this->assign_formula(formula);
	this->assign_range(range);
}
Segment::Segment(const Line2D &formula, const std::array<float, 2> &range)
{
	this->assign_formula(formula);
	this->assign_range(range);
}

Segment::~Segment()
{
}

void Segment::assign_range(const std::array<float, 2> &range)
{
	this->range = range;
}

void Segment::assign_formula(const Line2D &formula)
{
	this->formula = formula;
}

void Segment::assign_formula(const Circle2D &formula)
{
	this->formula = formula;
}

Points2D Segment::intersection(Segment &first, Segment &second)
{
}

Points2D Segment::intersection(Segment &segment, Line2D &line)
{
}

Points2D Segment::intersection(Segment &segment, Circle2D &circle)
{
}

Points2D Segment::intersection(Segment &segment)
{
}

Points2D Segment::intersection(Line2D &line)
{
}

Points2D Segment::intersection(Circle2D &circle)
{
}

float Segment::distance(Segment &first, Segment &second)
{
}

float Segment::distance(Segment &segment, Line2D &line)
{
}

float Segment::distance(Segment &segment, Circle2D &circle)
{
}

float Segment::distance(Segment &segment, Point2D &point)
{
}

float Segment::distance(Segment &segment)
{
}
float Segment::distance(Line2D &line)
{
}
float Segment::distance(Circle2D &circle)
{
}
float Segment::distance(Point2D &point)
{
	return Segment::distance(*this, point);
}

Line2D Segment::bisector(Segment &segment)
{
}

Line2D Segment::bisector()
{
	return Segment::bisector(*this);
}

bool Segment::is_on(Segment &segment, Point2D &point)
{
	enum type
	{
		circle,
		line
	};
	std::variant<Circle2D, Line2D> formula = segment.get_formula();
	switch (formula.index())
	{
	case type::circle:
	{
		Circle2D circ = std::get<type::circle>(formula);
		if (!circ.is_on(point))
			return false;
		auto diff = Point2D(point - circ.center()).point();
		float angle = std::atan2((float)diff.at(1), (float)diff.at(0)) / (2 * M_PI) + ((float)diff.at(1) < 0) * 2;
		return (segment.range.at(0) <= angle && angle <= segment.range.at(1));
	}
	case type::line:
	{
		break;
	}
	}
}
bool Segment::is_on(Point2D &point)
{
	return Segment::is_on(*this, point);
}

std::variant<Circle2D, Line2D> Segment::get_formula()
{
	return std::visit([](auto &&arg) -> std::variant<Circle2D, Line2D>
					  { 
		using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
            throw std::runtime_error("std::monostate detected, runtime rejected.");
        } else {
            return arg;
        } },
					  this->formula);
}