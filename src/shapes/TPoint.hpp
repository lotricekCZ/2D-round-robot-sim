#ifndef TPOINT_HPP
#define TPOINT_HPP

#include <cmath>
#include <array>
#include <numeric>
#include <algorithm>
#include <cinttypes>
#include <functional>

template <typename T, uint32_t dims>
class TPoint
{
    std::array<T, dims> coords;

public:
    template <typename ...Args>
    TPoint(Args ...);

    static T distance(TPoint<T, dims> a, TPoint<T, dims> b);
    T distance(TPoint<T, dims> a);
};

#include "TPoint.tpp"

typedef TPoint<float, 2> Point2D;
typedef TPoint<float, 3> Point3D;

#endif /* TPOINT_HPP */
