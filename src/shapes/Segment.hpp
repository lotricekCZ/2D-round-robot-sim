#include "TCircle.hpp"
#include "TLine.hpp"
#include "TPoint.hpp"
#include <variant>

#ifndef SEGMENT_HPP
#define SEGMENT_HPP

class Segment
{
private:
	std::variant<std::monostate, Circle2D, Line2D> formula; // nullptr is available only on creation
	std::array<float, 2> range;
public:
	Segment(const Circle2D &, const std::array<float, 2> &);
	Segment(const Line2D &, const std::array<float, 2> &);
	Segment(const Point2D &start, const Point2D &end);
	~Segment();

	void assign_range(const std::array<float, 2> &);
	void assign_formula(const Line2D &);
	void assign_formula(const Circle2D &);
	std::variant<Circle2D, Line2D> get_formula();

	static Points2D intersection(Segment &, Segment &);
	static Points2D intersection(Segment &, Line2D &);
	static Points2D intersection(Segment &, Circle2D &);

	Points2D intersection(Segment &);
	Points2D intersection(Line2D &);
	Points2D intersection(Circle2D &);

	static float distance(Segment &, Segment &);
	static float distance(Segment &, Line2D &);
	static float distance(Segment &, Circle2D &);
	static float distance(Segment &, Point2D &);

	float distance(Segment &);
	float distance(Line2D &);
	float distance(Circle2D &);
	float distance(Point2D &);

	static Line2D bisector(Segment &);
	Line2D bisector();
	static std::string print(Segment &);
	std::string print();
	static bool is_on(Segment &, Point2D &);
	bool is_on(Point2D &);
};

#endif