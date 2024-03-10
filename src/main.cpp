#include <iostream>
#include "shapes/TPoint.hpp"
#include "shapes/TVector.hpp"
#include "shapes/TLine.hpp"

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
		Point3D b(0.95, 1, 1);
		Point3D c(0, 0, 1);
		Point3D d(1, 1, 1);
		std::cout << Line3D(a, b).print() << std::endl;
		std::cout << Line3D(c, d).print() << std::endl;
		std::cout << Line3D(a, b).distance(Line3D(c,d)) << std::endl;
	}
	return 0;
};
