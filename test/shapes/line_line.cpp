#include <iostream>
#include "../../src/shapes/TPoint.hpp"
#include "../../src/shapes/TLine.hpp"
#include "../../src/shapes/TCircle.hpp"

int main(int argc, char **argv)
{
    Point2D a(atof(argv[1]), atof(argv[2]));
    Point2D b(atof(argv[3]), atof(argv[4]));
    Point2D c(atof(argv[5]), atof(argv[6]));
    Point2D d(atof(argv[7]), atof(argv[8]));
    Line2D e(a, b), f(c, d);

    printf("%f %s", Line2D::distance(e, f), Line2D::intersection(e, f).value_or(std::numeric_limits<float>::infinity()).print().c_str());
    std::cout.flush();
    return 0;
};
