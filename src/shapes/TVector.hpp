#ifndef TVECTOR_HPP
#define TVECTOR_HPP

#include <cmath>
#include <array>
#include <numeric>
#include <algorithm>
#include <cinttypes>
#include <functional>
#include "TPoint.hpp"

// template <typename T>
template <typename T, uint32_t dims>
class TVector: public std::pair<TPoint<T, dims>, TPoint<T, dims>>
{
    // std::pair<TPoint<T, dims>, TPoint<T, dims>> points;

public:
    using std::pair<TPoint<T, dims>, TPoint<T, dims>>::swap;
    // using std::pair<TPoint<T, dims>, TPoint<T, dims>>::get<>;
    TVector();
    TVector(TPoint<T, dims>, TPoint<T, dims>);

    T length();
};

#include "TVector.tpp"

typedef TVector<float, 2> Vect2D;
typedef TVector<float, 3> Vect3D;

#endif /* TVECTOR_HPP */