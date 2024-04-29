#include <iostream>
#include "shapes/TPoint.hpp"
#include "shapes/TVector.hpp"
#include "shapes/TLine.hpp"
#include "shapes/TCircle.hpp"
#include "shapes/Segment.hpp"

int main(int argc, char **argv)
{
	Point2D a(1, 1);
	Point2D b(0, 0);
	Point2D j(0.4, 0.45);
	Point3D c(3, 4, 5);
	Point3D i(-3, -4, -5);
	Point3D k(-1, 3, -1);
	Point3D d(0, 0);
	Point3D l(1, 1, 1);
	TPoint<float, 12> e(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	TPoint<float, 12> f(0, 0);
	TPoint<float, 1> g(34.5);
	TPoint<float, 1> h(-34.5);
	std::cout << (a + a).distance(b) << std::endl;
	std::cout << (a - a).distance(b) << std::endl;
	std::cout << (a * 5).distance(b) << std::endl;
	std::cout << (a / 2).distance(b) << std::endl;
	std::cout << c.distance(d) << std::endl;
	std::cout << c.print() << std::endl;
	std::cout << e.distance(f) << std::endl;
	std::cout << g.distance(h) << std::endl;
	std::cout << Vect2D(a, b).length() << std::endl;
	std::cout << Vect2D(a, b).length() << std::endl;
	std::cout << Vect3D(c, d).length() << std::endl;
	std::cout << Vect3D(c, d).normalise().length() << std::endl;
	std::cout << (Vect3D(c, d).normalise() >> d).print() << std::endl;
	std::cout << (Line3D(c, d)).print() << std::endl;
	std::cout << Vect3D::dot(Vect3D(d, i), Vect3D(d, c)) << std::endl;
	std::cout << Point2D::dot(a, j) << std::endl;
	std::cout << Line2D(a, b).print() << std::endl;
	std::cout << Line2D(a, b).at(4).print() << std::endl;
	std::cout << Line2D(a, b).distance(j) << std::endl;

	std::cout << Line3D(l, d).print() << std::endl;
	std::cout << Line3D(l, d).distance(k) << std::endl;
	{
		Point3D a(1, 2, 0);
		Point3D b(0, 1, 2);
		Point3D c(0, 0, 0);
		std::cout << Vect3D::cross(Vect3D(c, a), Vect3D(c, b)).print() << std::endl;
	}
	{
		Point3D a(0, 0, 0);
		Point3D b(1, 0, 1);
		Point3D c(0, 1, 0);
		Point3D d(1, 1, 1);
		std::cout << Line3D(a, b).print() << std::endl;
		std::cout << Line3D(c, d).print() << std::endl;
		std::cout << Line3D(a, b).distance(Line3D(c, d)) << std::endl;
	}
	{
		Point2D a(0, 0);
		Point2D b(1, 1);
		Point2D c(4, 5);
		Point2D d(5, 6);
		std::cout << Line2D(a, b).print() << std::endl;
		std::cout << Line2D(c, d).print() << std::endl;
		std::cout << Line2D(a, b).distance(Line2D(c, d)) << std::endl;
	}
	{
		Point2D a(0, 0);
		Point2D b(1, 1);
		std::cout << Vect2D::print_geogebra(Vect2D(a, b)) << std::endl;
		std::cout << Vect2D::print_geogebra((Vect2D(a, b) * 1.5)) << std::endl;
	}
	{
		Point2D a(0, 0);
		Point2D b(2, 1);
		Point2D c(4, 5);
		Point2D d(5, 6);
		// std::cout << Circle2D(4, a).print() << std::endl;
		// std::cout << Circle2D(5, c).print() << std::endl;
		// Circle2D(5, c).intersection(Circle2D(4, a));

		// std::cout << Circle2D(4, d).print() << std::endl;
		// std::cout << Circle2D(5, c).print() << std::endl;
		// Circle2D(5, c).intersection(Circle2D(4, d));

		std::cout << Circle2D(4, d).print() << std::endl;
		std::cout << Circle2D(5, b).print() << std::endl;
		std::cout << Point2D::print(Circle2D(5, b).intersection(Circle2D(4, d))) << std::endl;

		// std::cout << Circle2D(4, d).print() << std::endl;
		// std::cout << Circle2D(4, a).print() << std::endl;
		// Circle2D(4, a).intersection(Circle2D(4, d));
	}
	{
		Point2D a(0, 0);
		Point2D b(2, 1);
		Point2D c(4, 5);
		Point2D d(5, 6);
		// std::cout << Circle2D(4, a).print() << std::endl;
		// std::cout << Circle2D(5, c).print() << std::endl;
		// Circle2D(5, c).intersection(Circle2D(4, a));

		// std::cout << Circle2D(4, d).print() << std::endl;
		// std::cout << Circle2D(5, c).print() << std::endl;
		// Circle2D(5, c).intersection(Circle2D(4, d));

		std::cout << Circle2D(4, d).print() << std::endl;
		std::cout << Circle2D(5, b).print() << std::endl;
		std::cout << Point2D::print(Circle2D(5, b).intersection(Circle2D(4, d))) << std::endl;

		// std::cout << Circle2D(4, d).print() << std::endl;
		// std::cout << Circle2D(4, a).print() << std::endl;
		// Circle2D(4, a).intersection(Circle2D(4, d));
	}
	{
		Point2D a(0, 6);
		Point2D b(10, 0);
		Point2D c(2, 2);

		std::cout << Circle2D(3, c).print() << std::endl;
		std::cout << Line2D(a, b).print() << std::endl;
		std::cout << Point2D::print(Circle2D(3, c).intersection(Line2D(a, b))) << std::endl;
	}
	{
		Point2D a(0, 6);
		Point2D b(10, 0);
		Point2D c(2, 2);

		std::cout << Circle2D(3, a).print() << std::endl;
		std::cout << Circle2D(4, b).print() << std::endl;
		std::cout << Circle2D(1, c).print() << std::endl;

		for (auto i : Circle2D(3, a).tangents(Circle2D(4, b)))
			std::cout << i.print() << std::endl;
		for (auto i : Circle2D(1, c).tangents(Circle2D(4, b)))
			std::cout << i.print() << std::endl;
	}
	{
		Point2D a(0, 6);
		Point2D b(2, 8.2362);
		Point2D c(-3, 6);

		std::cout << Segment(a, b).print() << std::endl;
		Segment segment(Circle2D(3, a), {0.125, 0.375});
		std::cout << b.print() << "\n"
				  << c.print() << std::endl;
		std::cout << segment.print() << std::endl;
		std::cout << Circle2D(3, a).distance(b) << std::endl;
		std::cout << std::boolalpha << Circle2D(3, a).is_on(b) << " " << std::boolalpha << Circle2D(3, a).is_on(c) << std::endl;
		std::cout << std::boolalpha << segment.is_on(b) << " " << std::boolalpha << segment.is_on(c) << std::endl;
	}
	{
		Point2D a(0, 6);
		Point2D b(-2, 6);
		Point2D c(-3, 6);
		Point2D d(-3, 6.1);
		Point2D e(-2.8, 6);
		Point2D f(0.1, 5.9);

		std::cout << Segment(a, c).print() << std::endl;
		Segment segment(a, c);
		std::cout << b.print() << "\n"
				  << c.print() << std::endl;
		std::cout << segment.print() << std::endl;
		std::cout << std::boolalpha << segment.is_on(b) << " " << std::boolalpha << segment.is_on(c) << std::endl;
		std::cout << std::boolalpha << segment.is_on(d) << " " << std::boolalpha << segment.is_on(e) << std::endl;
		std::cout << std::boolalpha << segment.is_on(a) << " " << std::boolalpha << segment.is_on(f) << std::endl;
	}
	{
		Point3D a(0, 6);
		Point3D b(-2, 4);
		Point3D c(-3, 6);
		Point3D d(2, 7);

		// std::cout << Line3D(a, b).intersection(Line3D(c, d)).value().print() << std::endl;
		std::cout << Line3D(a, b).print() << std::endl;
		std::cout << Line3D(c, d).print() << std::endl;
		std::cout << Line3D::intersection(Line3D(a, b), Line3D(c, d)).value().print() << std::endl;
		std::cout << Line3D(b, a).print() << std::endl;
		std::cout << Line3D(c, d).print() << std::endl;
		std::cout << Line3D::intersection(Line3D(b, a), Line3D(c, d)).value().print() << std::endl;
		std::cout << Line3D(a, c).print() << std::endl;
		std::cout << Line3D(d, b).print() << std::endl;
		std::cout << Line3D::intersection(Line3D(a, c), Line3D(b, d)).value().print() << std::endl;
	}
	{
		Point2D a(0, 6);
		Point2D b(-2, 4);
		Point2D c(-3, 6);
		Point2D d(0, 4);

		// std::cout << Line3D(a, b).intersection(Line3D(c, d)).value().print() << std::endl;
		std::cout << Line2D(a, b).print() << std::endl;
		std::cout << Segment(c, d).print() << std::endl;
		for (auto i : Segment::intersection(Segment(d, c), Line2D(a, b)))
			std::cout << i.print() << std::endl;
	}
	{
		Point2D a(0, 6);
		Point2D b(-2, 10);
		Point2D c(0, 0);

		// std::cout << Line3D(a, b).intersection(Line3D(c, d)).value().print() << std::endl;
		Segment segment(Circle2D(3, a), {0.125, 0.375});
		std::cout << Line2D(b, c).print() << std::endl;
		std::cout << segment.print() << std::endl;
		for (auto i : Segment::intersection(segment, Line2D(b, c)))
			std::cout << i.print() << std::endl;
	}
	return 0;
};
