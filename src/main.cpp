#include <iostream>
#include "shapes/point/point.hpp"

int main(int argc, char ** argv){
	Point2D a;
	
	std::cout << a.distance(a) << std::endl;
	return 0;
};