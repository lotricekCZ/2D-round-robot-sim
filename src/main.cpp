#include <iostream>
#include "shapes/TPoint.hpp"
#include "shapes/TVector.hpp"

int main(int argc, char **argv)
{
	Point2D a(1, 1);
	Point2D b(0, 0);
	Point3D c(1, 1, 1);
	Point3D d(0, 0);
	TPoint<float, 12> e(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	TPoint<float, 12> f(0, 0);
	TPoint<float, 1> g(34.5);
	TPoint<float, 1> h(-34.5);
	std::cout << (a + a).distance(b) << std::endl;
	std::cout << (a - a).distance(b) << std::endl;
	std::cout << (a * 5).distance(b) << std::endl;
	std::cout << (a / 2).distance(b) << std::endl;
	std::cout << c.distance(d) << std::endl;
	std::cout << e.distance(f) << std::endl;
	std::cout << g.distance(h) << std::endl;
	std::cout << Vect2D(a, b).length() << std::endl;
	return 0;
};
