#ifndef TPOINT_HPP
#define TPOINT_HPP

#include <cmath>
#include <array>
#include <numeric>
#include <algorithm>
#include <cinttypes>
#include <functional>
#include <sstream>

template <typename T, uint32_t dims>
class TPoint
{
    std::array<T, dims> coords;

public:
    template <typename... Args>
    TPoint(Args...);
    TPoint(TPoint &);
    static std::string print(const TPoint &);
    std::string print();
    static std::array<T, dims> point(TPoint&);
    static T distance(TPoint<T, dims> a, TPoint<T, dims> b);
    static T dot(TPoint, TPoint);
    T dot(TPoint);

    std::array<T, dims> point();
    T distance(TPoint<T, dims> a);
    TPoint operator-(const TPoint &rhs);
    TPoint operator+(const TPoint &rhs);
    TPoint operator/(const T &rhs);
    TPoint operator*(const T &rhs);
    TPoint operator*=(const T &rhs);
    TPoint operator-=(const TPoint &rhs);

    inline bool operator==(const TPoint &rhs)
    {
        return this->get_distance(rhs) <= std::numeric_limits<T>::epsilon;
    }
};

#include "TPoint.cpp"

typedef TPoint<float, 2> Point2D;
typedef TPoint<float, 3> Point3D;

#endif /* TPOINT_HPP */
