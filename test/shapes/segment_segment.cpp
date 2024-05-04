/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#include <iostream>
#include "../../src/shapes/TPoint.hpp"
#include "../../src/shapes/TLine.hpp"
#include "../../src/shapes/Segment.hpp"

int main(int argc, char **argv)
{
	if (argc == 11) // two circular segments
	{
		Point2D a(atof(argv[1]), atof(argv[2]));
		Point2D b(atof(argv[3]), atof(argv[4]));
		Circle2D c(atof(argv[5]), a);
		Circle2D d(atof(argv[6]), b);

		Segment e(c, {atof(argv[7]), atof(argv[8])});
		Segment f(d, {atof(argv[9]), atof(argv[10])});

		std::cout << Segment::distance(f, e) << " ";
		for (auto i : Segment::intersection(f, e))
			std::cout << i.print() << " ";
		std::cout << std::endl;
	}
	else if(argc == 10) // circular - linear
	{
		Point2D a(atof(argv[1]), atof(argv[2]));
		Point2D b(atof(argv[3]), atof(argv[4]));
		Point2D c(atof(argv[5]), atof(argv[6]));
		Circle2D d(atof(argv[7]), c);
		Segment e(d, {atof(argv[8]), atof(argv[9])});
		Segment f(a, b);

		std::cout << Segment::distance(f, e) << " ";
		std::cout << f.bisector().print() << " ";
		for (auto i : Segment::intersection(f, e))
			std::cout << i.print() << " ";
		std::cout << std::endl;
	}
	else if(argc == 9) // linear - linear
	{
		Point2D a(atof(argv[1]), atof(argv[2]));
		Point2D b(atof(argv[3]), atof(argv[4]));
		Point2D c(atof(argv[5]), atof(argv[6]));
		Point2D d(atof(argv[7]), atof(argv[8]));
		Segment e(a, b);
		Segment f(c, d);

		std::cout << Segment::distance(f, e) << " ";
		std::cout << f.bisector().print() << " ";
		for (auto i : Segment::intersection(f, e))
			std::cout << i.print() << " ";
		std::cout << std::endl;
	}

	return 0;
};
