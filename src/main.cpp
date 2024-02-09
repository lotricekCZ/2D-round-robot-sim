#include <iostream>
#include "shapes/point/TPoint.hpp"

int main(int argc, char ** argv){
	Point2D a;
	Point2D b;
	std::cout << a.distance(a) << std::endl;
	return 0;
};