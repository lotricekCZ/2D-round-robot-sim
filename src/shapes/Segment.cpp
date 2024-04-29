#include "Segment.hpp"
#include "TVector.hpp"
#include <variant>
#include <optional>
#include <type_traits>
#include <cmath>
#include <execution>
#include <cinttypes>

/**
 * @brief Constructs a segment from a circle formula and range.
 *
 * @param formula Circle2D formula defining the segment.
 * @param range Range of the segment.
 */
Segment::Segment(const Circle2D &formula, const std::array<float, 2> &range)
{
	this->assign_formula(formula);
	this->assign_range(range);
}

/**
 * @brief Constructs a segment from a line formula and range.
 *
 * @param formula Line2D formula defining the segment.
 * @param range Range of the segment.
 */
Segment::Segment(const Line2D &formula, const std::array<float, 2> &range)
{
	this->assign_formula(formula);
	this->assign_range(range);
}

/**
 * @brief Constructs a segment from start and end points.
 *
 * @param start Starting point of the segment.
 * @param end Ending point of the segment.
 */
Segment::Segment(const Point2D &start, const Point2D &end)
{
	Line2D line(start, end);
	this->assign_formula(line);
	this->assign_range({0, Point2D::distance(start, end) / Vect2D::length(Vect2D(start, end).normalise())});
}

/**
 * @brief Destroys the segment object.
 */
Segment::~Segment()
{
}

/**
 * @brief Assigns the range of the segment.
 *
 * @param range Range of the segment.
 */
void Segment::assign_range(const std::array<float, 2> &range)
{
	this->range = range;
}

/**
 * @brief Assigns the formula of the segment as a line.
 *
 * @param formula Line2D formula of the segment.
 */
void Segment::assign_formula(const Line2D &formula)
{
	this->formula = formula;
}

/**
 * @brief Assigns the formula of the segment as a circle.
 *
 * @param formula Circle2D formula of the segment.
 */
void Segment::assign_formula(const Circle2D &formula)
{
	this->formula = formula;
}

/**
 * @brief Finds the intersection points between two segments.
 *
 * @param first First segment.
 * @param second Second segment.
 * @return Intersection points between the two segments.
 */
Points2D Segment::intersection(const Segment &first, const Segment &second)
{
	Points2D ret;

	return ret;
}

/**
 * @brief Finds the intersection points between a segment and a line.
 *
 * @param segment Segment to intersect with the line.
 * @param line Line to intersect with the segment.
 * @return Intersection points between the segment and the line.
 */
Points2D Segment::intersection(const Segment &segment, const Line2D &line)
{
	Points2D ret;
	auto formula = segment.get_formula();
	switch (formula.index())
	{
	case type::circle:
	{
		ret = Circle2D::intersection(std::get<type::circle>(formula), line);
		break;
	}
	case type::line:
	{
		auto point = Line2D::intersection(std::get<type::line>(formula), line);
		if (point)
			ret.push_back(point.value());
		break;
	}
	}

	std::remove_if(std::execution::par_unseq, ret.begin(), ret.end(), [&](auto &point) -> bool
				   { return !segment.is_on(point); });

	return ret;
}

/**
 * @brief Computes the intersection points between a segment and a circle.
 *
 * This method computes the intersection points between the specified segment and circle.
 *
 * @param segment The segment.
 * @param circle The circle.
 * @return Points2D The intersection points.
 */
Points2D Segment::intersection(const Segment &segment, const Circle2D &circle)
{
	Points2D ret;
	auto formula = segment.get_formula();
	switch (formula.index())
	{
	case type::circle:
	{
		ret = Circle2D::intersection(std::get<type::circle>(formula), circle);
		break;
	}
	case type::line:
	{
		ret = Circle2D::intersection(circle, std::get<type::line>(formula));
		break;
	}
	}
	std::remove_if(std::execution::par_unseq, ret.begin(), ret.end(), [&](auto &point) -> bool
				   { return !segment.is_on(point); });
	return ret;
}

/**
 * @brief Computes the intersection points between two segments.
 *
 * This method computes the intersection points between the two specified segments.
 *
 * @param segment The first segment.
 * @return Points2D The intersection points.
 */
Points2D Segment::intersection(const Segment &segment)
{
	return Segment::intersection(*this, segment);
}

/**
 * @brief Computes the intersection points between a segment and a line.
 *
 * This method computes the intersection points between the specified segment and line.
 *
 * @param line The line.
 * @return Points2D The intersection points.
 */
Points2D Segment::intersection(const Line2D &line)
{
	return Segment::intersection(*this, line);
}

/**
 * @brief Computes the intersection points between a segment and a circle.
 *
 * This method computes the intersection points between the specified segment and circle.
 *
 * @param circle The circle.
 * @return Points2D The intersection points.
 */
Points2D Segment::intersection(const Circle2D &circle)
{
	return Segment::intersection(*this, circle);
}

float Segment::distance(const Segment &first, const Segment &second)
{
}

float Segment::distance(const Segment &segment, const Line2D &line)
{
	auto formula = segment.get_formula();
	switch (formula.index())
	{
	case type::circle:
	{
		Circle2D::intersection(std::get<type::circle>(formula), circle);
		break;
	}
	case type::line:
	{
		auto inter = std::get<type::line>(formula).intersection(line);
		if (inter && segment.is_on(inter.value()))
			return 0;
		Points2D c = {Segment::at(segment, segment.range.at(0)).value(), Segment::at(segment, segment.range.at(1)).value()};
		return std::min(static_cast<Line2D>(line).distance(c.at(0)), static_cast<Line2D>(line).distance(c.at(1)));
	}
	}

	return std::numeric_limits<float>::infinity();
}

float Segment::distance(const Segment &segment, const Circle2D &circle)
{
}

float Segment::distance(const Segment &segment, const Point2D &point)
{
}

float Segment::distance(Segment &segment)
{
	return Segment::distance(*this, segment);
}
float Segment::distance(Line2D &line)
{
	return Segment::distance(*this, line);
}
float Segment::distance(Circle2D &circle)
{
	return Segment::distance(*this, circle);
}

float Segment::distance(Point2D &point)
{
	return Segment::distance(*this, point);
}

Line2D Segment::bisector(Segment &segment)
{
	auto formula = segment.get_formula();
	switch (formula.index())
	{
	case type::circle:
	{
		return Line2D(std::get<type::circle>(formula).center(),
					  (segment.at(segment.range.at(0)).value() + segment.at(segment.range.at(1)).value()) / 2);
	}
	case type::line:
	{
		auto l = std::get<type::line>(formula).get_point().point();
		return Line2D(Vect2D(l.at(1), -l.at(0)), (segment.at(segment.range.at(0)).value() + segment.at(segment.range.at(1)).value()) / 2);
	}
	}
}

Line2D Segment::bisector()
{
	return Segment::bisector(*this);
}

/**
 * @brief Checks if a point lies on a segment.
 *
 * This method checks if the specified point lies on the specified segment.
 *
 * @param segment The segment.
 * @param point The point.
 * @return true if the point lies on the segment, false otherwise.
 */
bool Segment::is_on(const Segment &segment, const Point2D &point)
{
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
		Line2D line = std::get<type::line>(formula);
		return line.is_on(point) && (((line.get_origin()).distance(line.at(segment.range.at(1)))) - (line.at(segment.range.at(1)).distance(point) + line.get_origin().distance(point)) <= std::numeric_limits<float>::epsilon() * 2048);
	}
	}
}

/**
 * @brief Checks if a point lies on this segment.
 *
 * This method checks if the specified point lies on this segment.
 *
 * @param point The point.
 * @return true if the point lies on this segment, false otherwise.
 */
bool Segment::is_on(const Point2D &point) const
{
	return Segment::is_on(*this, point);
}

/**
 * @brief Retrieves the formula (either circle or line) of the segment.
 *
 * This method retrieves the formula (either circle or line) of the segment.
 *
 * @return std::variant<Circle2D, Line2D> The formula of the segment.
 */
std::variant<Circle2D, Line2D> Segment::get_formula() const
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

/**
 * @brief Generates a string representation of the segment.
 *
 * This method generates a string representation of the specified segment.
 *
 * @param segment The segment.
 * @return std::string The string representation of the segment.
 */
std::string Segment::print(Segment &segment)
{
	std::stringstream ss;
	std::variant<Circle2D, Line2D> formula = segment.get_formula();
	switch (formula.index())
	{
	case type::circle:
	{
		ss << Circle2D::print(std::get<type::circle>(formula));
		break;
	}
	case type::line:
	{
		ss << Line2D::print(std::get<type::line>(formula));
		break;
	}
	}
	ss << "\n(" << segment.range.at(0) << " <= t <= " << segment.range.at(1) << ")";
	return ss.str();
}

/**
 * @brief Generates a string representation of this segment.
 *
 * This method generates a string representation of this segment.
 *
 * @return std::string The string representation of this segment.
 */
std::string Segment::print()
{
	return Segment::print(*this);
}

std::optional<Point2D> Segment::at(Segment segment, float parameter)
{
	std::variant<Circle2D, Line2D> formula = segment.get_formula();
	switch (formula.index())
	{
	case type::line:
	{
		Point2D p = std::get<type::line>(formula).at(parameter);
		if (segment.is_on(p))
			return p;
		break;
	}

	case type::circle:
	{
		Point2D p = std::get<type::circle>(formula).at(parameter);
		if (segment.is_on(p))
			return p;
		break;
	}
	}
	return {};
}

std::optional<Point2D> Segment::at(float parameter)
{
	return Segment::at(*this, parameter);
}
