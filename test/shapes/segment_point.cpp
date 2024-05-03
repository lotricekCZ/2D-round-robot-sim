#include <iostream>
#include "../../src/shapes/TPoint.hpp"
#include "../../src/shapes/TLine.hpp"
#include "../../src/shapes/Segment.hpp"

int main(int argc, char **argv)
{
	if (argc == 7) // linear
	{
		Point2D a(atof(argv[1]), atof(argv[2]));
		Point2D b(atof(argv[3]), atof(argv[4]));
		Point2D c(atof(argv[5]), atof(argv[6]));
		Segment d(b, c);

		std::cout << Segment::distance(d, a);
		std::cout << std::endl;
	}
	else if(argc == 8) // circular
	{
		Point2D a(atof(argv[1]), atof(argv[2]));
		Point2D b(atof(argv[3]), atof(argv[4]));
		Circle2D c(atof(argv[5]), b);
		Segment d(c, {atof(argv[6]), atof(argv[7])});

		std::cout << Segment::distance(d, a);
		std::cout << std::endl;
	}

	return 0;
};
