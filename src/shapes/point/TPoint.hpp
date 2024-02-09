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
    TPoint();
    static T distance(TPoint<T, dims> a, TPoint<T, dims> b);
    T distance(TPoint<T, dims> a);
};

#include "TPoint.tpp"

class Point2D : public TPoint<float, 2>
{
};

#endif /* TPOINT_HPP */
