#include <iostream>
#include "../../src/shapes/TPoint.hpp"
#include "../../src/shapes/TLine.hpp"
#include "../../src/shapes/Segment.hpp"

int main(int argc, char **argv)
{
	if (argc == 10)
	{
		Point2D a(atof(argv[1]), atof(argv[2]));
		Point2D b(atof(argv[3]), atof(argv[4]));
		Circle2D c(atof(argv[7]), Point2D(atof(argv[5]), atof(argv[6])));
		Line2D e(a, b);
		Segment f(c, {atof(argv[8]), atof(argv[9])});

		std::cout << Segment::distance(f, e) << " ";

		for (auto i : Segment::intersection(f, e))
			std::cout << i.print() << " ";
		std::cout << std::endl;
	}
	else
	{
		Point2D a(atof(argv[1]), atof(argv[2]));
		Point2D b(atof(argv[3]), atof(argv[4]));
		Point2D c(atof(argv[5]), atof(argv[6]));
		Point2D d(atof(argv[7]), atof(argv[8]));
		
		Line2D e(a, b);
		Segment f(c, d);

		std::cout << Segment::distance(f, e) << " ";
		for (auto i : Segment::intersection(f, e))
			std::cout << i.print() << " ";
		std::cout << std::endl;
	}

	return 0;
};
