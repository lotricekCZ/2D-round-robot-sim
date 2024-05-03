#include "TCircle.hpp"
#include "TLine.hpp"
#include "TPoint.hpp"
#include <variant>

#ifndef SEGMENT_HPP
#define SEGMENT_HPP

class Segment
{
private:
	enum type
	{
		circle,
		line
	};
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
	std::variant<Circle2D, Line2D> get_formula() const;

	static Points2D intersection(const Segment &, const Segment &);
	static Points2D intersection(const Segment &, const Line2D &);
	static Points2D intersection(const Segment &, const Circle2D &);

	Points2D intersection(const Segment &) const;
	Points2D intersection(const Line2D &) const;
	Points2D intersection(const Circle2D &) const;

	static float distance(const Segment &, const Segment &);
	static float distance(const Segment &, const Line2D &);
	static float distance(const Segment &, const Circle2D &);
	static float distance(const Segment &, const Point2D &);

	float distance(const Segment &) const;
	float distance(const Line2D &) const;
	float distance(const Circle2D &) const;
	float distance(const Point2D &) const;
	Point2D start() const;
	Point2D end() const;

	static std::optional<Point2D> at(Segment segment, float parameter);
	std::optional<Point2D> at(float parameter) const;
	static Line2D bisector(Segment &);
	Line2D bisector();
	static std::string print(Segment &);
	std::string print();
	static bool is_on(const Segment &, const Point2D &);
	bool is_on(const Point2D &) const;
private:
	static float distance_lin(const Segment &, const Segment &);
	static float distance_cir(const Segment &, const Segment &);
	static float distance_cmb(const Segment &, const Segment &);
};

#endif