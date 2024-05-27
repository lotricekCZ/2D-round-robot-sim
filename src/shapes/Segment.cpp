/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#include "Segment.hpp"
#include "TVector.hpp"
#include <variant>
#include <optional>
#include <algorithm>
#include <type_traits>
#include <cmath>
#include <cinttypes>
#ifndef noexec
#include <execution>
#endif

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
	auto formula = first.get_formula();
	switch (formula.index())
	{
	case type::line:
	{
		ret = second.intersection(std::get<type::line>(formula));
		break;
	}

	case type::circle:
	{
		ret = second.intersection(std::get<type::circle>(formula));
		break;
	}
	}

	for (size_t i = 0; i < ret.size(); i++)
		if (!first.is_on(ret.at(i)))
			ret.erase(ret.begin() + i--);

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
	Points2D ret = {};
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
	for (size_t i = 0; i < ret.size(); i++)
		if (!segment.is_on(ret.at(i)))
			ret.erase(ret.begin() + i--);

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
	for (size_t i = 0; i < ret.size(); i++)
		if (!segment.is_on(ret.at(i)))
			ret.erase(ret.begin() + i--);
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
Points2D Segment::intersection(const Segment &segment) const
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
Points2D Segment::intersection(const Line2D &line) const
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
Points2D Segment::intersection(const Circle2D &circle) const
{
	return Segment::intersection(*this, circle);
}

float Segment::distance(const Segment &first, const Segment &second)
{
	if (Segment::intersection(first, second).size() != 0)
		return 0;
	auto fml_1 = first.get_formula();
	auto fml_2 = second.get_formula();
	switch (fml_1.index())
	{
	case type::line:
		switch (fml_2.index())
		{
		case type::line:
			return Segment::distance_lin(first, second);
		case type::circle:
			return Segment::distance_cmb(first, second);
		}
		return -1;
	case type::circle:
		switch (fml_2.index())
		{
		case type::line:
			return Segment::distance_cmb(second, first);
		case type::circle:
			return Segment::distance_cir(first, second);
		}
	}
	return std::numeric_limits<float>::infinity();
}

float Segment::distance(const Segment &segment, const Line2D &line)
{
	auto formula = segment.get_formula();
	switch (formula.index())
	{
	case type::circle:
	{
		if (segment.intersection(line).size() != 0)
			return 0;
		// return candidates
		std::vector<float> ret_c = {line.distance(segment.start()), line.distance(segment.end())};

		auto l = line.get_point().point();
		for (auto intersection : segment.intersection(Line2D(Vect2D(l.at(1), -l.at(0)), (std::get<type::circle>(segment.get_formula()).center()))))
			ret_c.push_back(line.distance(intersection));
		return *std::min_element(ret_c.begin(), ret_c.end());
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
	auto formula = segment.get_formula();
	switch (formula.index())
	{
	case type::circle:
	{
		// if (segment.intersection(line).size() != 0)
		// 	return 0;
		// // return candidates
		// std::vector<float> ret_c = {circle.distance(segment.start()), circle.distance(segment.end())};

		// auto l = line.get_point().point();
		// for (auto intersection : segment.intersection(Line2D(Vect2D(l.at(1), -l.at(0)), (std::get<type::circle>(segment.get_formula()).center()))))
		// 	ret_c.push_back(line.distance(intersection));
		// return *std::min_element(ret_c.begin(), ret_c.end());
		// break;
	}
	case type::line:
	{
		// auto inter = std::get<type::line>(formula).intersection(line);
		// if (inter && segment.is_on(inter.value()))
		// 	return 0;
		// Points2D c = {Segment::at(segment, segment.range.at(0)).value(), Segment::at(segment, segment.range.at(1)).value()};
		// return std::min(static_cast<Line2D>(line).distance(c.at(0)), static_cast<Line2D>(line).distance(c.at(1)));
	}
	}

	return std::numeric_limits<float>::infinity();
}

float Segment::distance(const Segment &segment, const Point2D &point)
{
	if (segment.is_on(point))
		return 0;
	auto formula = segment.get_formula();
	switch (formula.index())
	{
	case type::line:
	{
		auto l = std::get<type::line>(formula).get_point().point();
		Points2D p = Segment::intersection(segment, Line2D(Vect2D(l.at(1), -l.at(0)), (point))); // always exactly one point. or none

		if (p.size() != 0)
			return point.distance(p.at(0));

		return std::min(point.distance(segment.start()), point.distance(segment.end()));
	}

	case type::circle:
	{
		Points2D p = (segment.intersection(Line2D(point, std::get<type::circle>(formula).center())));
		p.push_back(segment.start());
		p.push_back(segment.end());
		float ret = std::numeric_limits<float>::infinity();
		for (auto i : p)
		{
			float rc = point.distance(i);
			if (rc < ret)
				ret = rc;
		}
		return ret;
	}
	}
	return std::numeric_limits<float>::infinity();
}

float Segment::distance(const Segment &segment) const
{
	return Segment::distance(*this, segment);
}
float Segment::distance(const Line2D &line) const
{
	return Segment::distance(*this, line);
}
float Segment::distance(const Circle2D &circle) const
{
	return Segment::distance(*this, circle);
}

float Segment::distance(const Point2D &point) const
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
					  (segment.start() + segment.end()) / 2);
	}
	case type::line:
	{
		auto l = std::get<type::line>(formula).get_point().point();
		return Line2D(Vect2D(l.at(1), -l.at(0)), (segment.start() + segment.end()) / 2);
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
		if (segment.range.at(0) < segment.range.at(1))
			return ((segment.range.at(0) <= angle && angle <= segment.range.at(1)) || std::abs(angle - segment.range.at(0)) <= (std::numeric_limits<float>::epsilon() * 1024) || std::abs(angle - segment.range.at(1)) <= (std::numeric_limits<float>::epsilon() * 1024));
		else
			return (segment.range.at(1) <= angle && angle <= segment.range.at(0) || std::abs(angle - segment.range.at(0)) <= (std::numeric_limits<float>::epsilon() * 1024) || std::abs(angle - segment.range.at(1)) <= (std::numeric_limits<float>::epsilon() * 1024));
	}
	case type::line:
	{
		Line2D line = std::get<type::line>(formula);
		return line.is_on(point) &&
			   (std::abs(Point2D::distance(line.at(segment.range.at(0)), point) + Point2D::distance(line.at(segment.range.at(1)), point) - Point2D::distance(line.at(segment.range.at(0)), line.at(segment.range.at(1)))) <= std::numeric_limits<float>::epsilon() * 2048);
	}
	}
	return false;
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
	if (segment.range.at(0) < segment.range.at(1))
	{
		ss << "\n(" << segment.range.at(0) << " <= t <= " << segment.range.at(1) << ")";
	}
	else
	{
		ss << "\n(" << segment.range.at(1) << " <= t <= " << segment.range.at(0) << ")";
	}

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

std::optional<Point2D> Segment::at(float parameter) const
{
	return Segment::at(*this, parameter);
}

Point2D Segment::start() const
{
	return Segment::at(*this, range.at(0)).value();
}
Point2D Segment::end() const
{
	return Segment::at(*this, range.at(1)).value();
}

float Segment::distance_lin(const Segment &first, const Segment &second)
{
	if (Segment::intersection(first, second).size() != 0)
	{
		return 0;
	}
	auto fml_1 = std::get<type::line>(first.get_formula()).get_point().point();
	auto fml_2 = std::get<type::line>(second.get_formula()).get_point().point();

	std::vector<Line2D> intersections;
	float ret = std::numeric_limits<float>::infinity();

	std::array<Points2D, 4> inters = {
		Segment::intersection(second, Line2D(Vect2D(fml_2.at(1), -fml_2.at(0)), first.start())),
		Segment::intersection(second, Line2D(Vect2D(fml_2.at(1), -fml_2.at(0)), first.end())),
		Segment::intersection(first, Line2D(Vect2D(fml_1.at(1), -fml_1.at(0)), second.start())),
		Segment::intersection(first, Line2D(Vect2D(fml_1.at(1), -fml_1.at(0)), second.end()))};
	Points2D origins = {first.start(), first.end(), second.start(), second.end()};

	for (uint8_t i = 0; i < inters.size(); i++)
		if (inters[i].size() != 0)
		{
			float retc = origins[i].distance(inters[i][0]);
			ret = (ret < retc) ? ret : retc;
		}
	float start_start = first.start().distance(second.start());
	float start_end = first.start().distance(second.end());
	float end_start = first.end().distance(second.start());
	float end_end = first.end().distance(second.end());

	float shortest = std::numeric_limits<float>::infinity();
	for (auto o : {start_start, start_end, end_start, end_end})
	{
		shortest = (shortest < o) ? shortest : o;
	}
	ret = (ret < shortest) ? ret : shortest;

	return ret;
}

float Segment::distance_cir(const Segment &first, const Segment &second)
{
	if (Segment::intersection(first, second).size() != 0)
		return 0;

	float ret = std::numeric_limits<float>::infinity();
	Circle2D a_formula = std::get<type::circle>(first.get_formula());
	Circle2D b_formula = std::get<type::circle>(second.get_formula());

	// make line from each center to each start/end/center (estimated count: 5)
	Line2D start_center(first.start(), b_formula.center());
	Line2D end_center(first.end(), b_formula.center());
	Line2D center_center(a_formula.center(), b_formula.center());
	Line2D center_start(a_formula.center(), second.start());
	Line2D center_end(a_formula.center(), second.end());

	Points2D int_start_center = Segment::intersection(second, start_center);
	Points2D int_end_center = Segment::intersection(second, end_center);
	Points2D int_center_center_b = Segment::intersection(second, center_center);
	Points2D int_center_center_a = Segment::intersection(first, center_center);
	Points2D int_center_start = Segment::intersection(first, center_start);
	Points2D int_center_end = Segment::intersection(first, center_end);

	std::array<Points2D, 4> it_1 = {int_start_center, int_end_center,
									int_center_start, int_center_end};
	std::array<Point2D, 4> it_2 = {first.start(), first.end(), second.start(), second.end()};
	for (uint8_t i = 0; i < 4; i++)
	{
		for (auto o : it_1[i])
		{
			float retc = o.distance(it_2[i]);
			ret = (ret < retc) ? ret : retc;
		}
	}
	for (uint8_t i = 0; i < int_center_center_b.size(); i++)
	{
		for (uint8_t o = 0; o < int_center_center_a.size(); o++)
		{
			float retc = int_center_center_b[i].distance(int_center_center_a[o]);
			ret = (ret < retc) ? ret : retc;
		}
	}

	// get distances between starts and ends
	float start_start = first.start().distance(second.start());
	float start_end = first.start().distance(second.end());
	float end_start = first.end().distance(second.start());
	float end_end = first.end().distance(second.end());
	float shortest = std::numeric_limits<float>::infinity();
	for (auto o : {start_start, start_end, end_start, end_end})
	{
		shortest = (shortest < o) ? shortest : o;
	}
	ret = (ret < shortest) ? ret : shortest;

	return ret;
}

float Segment::distance_cmb(const Segment &first, const Segment &second)
{
	if (Segment::intersection(first, second).size() != 0)
		return 0;

	float ret = std::numeric_limits<float>::infinity();
	auto fml_lin = first.get_formula();
	auto fml_cir = second.get_formula();
	auto linear = first;
	auto circular = second;

	if (fml_cir.index() == type::line)
	{
		std::swap(fml_cir, fml_lin);
		std::swap(circular, linear);
	}

	Line2D n_line = std::get<type::line>(fml_lin);
	Circle2D n_circ = std::get<type::circle>(fml_cir);
	auto n_line_vec = n_line.get_point().point();
	// Line2D(Vect2D(fml_2.at(1), -fml_2.at(0)), first.start())
	Line2D perp_center = Line2D(Vect2D(n_line_vec.at(1), -n_line_vec.at(0)), n_circ.center());
	Line2D perp_start = Line2D(Vect2D(n_line_vec.at(1), -n_line_vec.at(0)), circular.start());
	Line2D perp_end = Line2D(Vect2D(n_line_vec.at(1), -n_line_vec.at(0)), circular.end());

	Point2D e_center = Line2D::intersection(perp_center, n_line).value();
	Point2D e_start = Line2D::intersection(perp_start, n_line).value();
	Point2D e_end = Line2D::intersection(perp_end, n_line).value();

	Points2D int_center = Segment::intersection(circular, perp_center);
	Points2D int_start = Segment::intersection(circular, perp_start);
	Points2D int_end = Segment::intersection(circular, perp_end);

	if (linear.is_on(e_center))
	{
		for (auto i : int_center)
		{
			// they already are on circular segment, so no worries I suppose
			float retc = i.distance(e_center); // return candidate
			//~ std::cout << i.print_geogebra() << std::endl;
			ret = (ret < retc) ? ret : retc;
		}
	}

	if (linear.is_on(e_start))
	{
		float retc = circular.start().distance(e_start); // return candidate
		ret = (ret < retc) ? ret : retc;
		for (auto i : int_start)
		{
			// they already are on circular segment, so no worries I suppose
			retc = i.distance(e_start); // return candidate
			//~ std::cout << i.print_geogebra() << std::endl;
			ret = (ret < retc) ? ret : retc;
		}
	}

	if (linear.is_on(e_end))
	{
		float retc = circular.end().distance(e_end); // return candidate
		ret = (ret < retc) ? ret : retc;
		for (auto i : int_end)
		{
			// they already are on circular segment, so no worries I suppose
			//~ std::cout << i.print_geogebra() << std::endl;
			float retc = i.distance(e_end); // return candidate
			ret = (ret < retc) ? ret : retc;
		}
	}

		// cares about every other possibilities
		Line2D start_center_variant = Line2D(linear.start(), n_circ.center());
		Line2D end_center_variant = Line2D(linear.end(), n_circ.center());

		Line2D start_start_variant = Line2D(linear.start(), circular.start());
		Line2D end_start_variant = Line2D(linear.end(), circular.start());
		Line2D start_end_variant = Line2D(linear.start(), circular.end());
		Line2D end_end_variant = Line2D(linear.end(), circular.end());

		// all the possible variants of intersection of circular segment with the lines above
		Points2D start_center_intersections = circular.intersection(start_center_variant);
		Points2D end_center_intersections = circular.intersection(end_center_variant);

		Points2D start_start_intersections = circular.intersection(start_start_variant);
		Points2D end_start_intersections = circular.intersection(end_start_variant);
		Points2D start_end_intersections = circular.intersection(start_end_variant);
		Points2D end_end_intersections = circular.intersection(end_end_variant);
		std::array<Points2D, 6> it_1 = {start_center_intersections, end_center_intersections, start_start_intersections,
														end_start_intersections, start_end_intersections, end_end_intersections};
		std::array<Point2D, 2> it_2 = {linear.start(), linear.end()};
		for (uint8_t i = 0; i < 6; i++)
		{
			for (auto o : it_1[i])
			{
				//~ std::cout << o.print_geogebra() << std::endl;
				float retc = o.distance(it_2[i % 2]);
				ret = (ret < retc) ? ret : retc;
			}
		}

		float start_start = Point2D::distance(linear.start(), circular.start());
		float start_end = Point2D::distance(linear.start(), circular.end());
		float end_start = Point2D::distance(linear.end(), circular.start());
		float end_end = Point2D::distance(linear.end(), circular.end());

		float shortest = std::numeric_limits<float>::infinity();
		for (auto o : {start_start, start_end, end_start, end_end})
		{
			shortest = (shortest < o) ? shortest : o;
		}
		ret = (ret < shortest) ? ret : shortest;

	return ret;
}
