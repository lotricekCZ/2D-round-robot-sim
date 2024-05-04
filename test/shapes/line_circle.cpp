/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#include <iostream>
#include "../../src/shapes/TPoint.hpp"
#include "../../src/shapes/TLine.hpp"
#include "../../src/shapes/TCircle.hpp"

int main(int argc, char **argv)
{
    Point2D a(atof(argv[1]), atof(argv[2]));
    Point2D b(atof(argv[3]), atof(argv[4]));
    Point2D c(atof(argv[5]), atof(argv[6]));
    Line2D e(a, b);
    Circle2D f(atof(argv[7]), c);

    std::cout << Circle2D::distance(f, e) << " ";

    for (auto i : Circle2D::intersection(f, e))
        std::cout << i.print() << " ";
    std::cout << std::endl;

    return 0;
};
