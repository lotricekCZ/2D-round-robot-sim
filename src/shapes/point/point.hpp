#ifndef POINT_H
#define POINT_H
#include <array>
#include <cstdint>

template <typename T, uint32_t dims>
class TPoint {
    protected:
    std::array<T, dims> coords;
    public:
    static T distance(TPoint, TPoint);
    T distance(TPoint);
};

typedef TPoint<float, 2> Point2D;
#endif // POINT_H