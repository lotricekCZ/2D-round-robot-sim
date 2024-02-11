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
    template <typename... Args>
    TPoint(Args...);

    static T distance(TPoint<T, dims> a, TPoint<T, dims> b);
    T distance(TPoint<T, dims> a);
    TPoint operator-(const TPoint &rhs);
    TPoint operator+(const TPoint &rhs);
    TPoint operator/(const T &rhs);
    TPoint operator*(const T &rhs);
    TPoint operator*=(const T &rhs);
    TPoint operator-=(const TPoint &rhs);

    inline bool operator==(const TPoint &rhs)
    {
        const T thres = 0.15; // 0.15 units // 10mm
        /* do actual comparison */
        return this->get_distance(rhs) <= thres;
    }
};

#include "TPoint.tpp"

typedef TPoint<float, 2> Point2D;
typedef TPoint<float, 3> Point3D;

#endif /* TPOINT_HPP */
