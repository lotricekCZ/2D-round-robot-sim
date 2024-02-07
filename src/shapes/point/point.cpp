#include "point.hpp"
#include <numeric>
#include <cmath>
#include <algorithm>

template <typename T, uint32_t dims>
T TPoint<T, dims>::distance(TPoint<T, dims> a, TPoint<T, dims> b){
    std::array<T, dims> c = std::transform(a.coords.cbegin(), a.coords.cend(), b.coords.cbegin(), b.coords.cend(), 
                   [](T ap, T bp){return std::pow(ap-bp, 2);});
    return std::sqrt(std::accumulate(c.begin(), c.end()));
}

template <typename T, uint32_t dims>
T TPoint<T, dims>::distance(TPoint<T, dims> a){
    return TPoint<T, dims>::distance(*this, a);
}