#ifndef TPOINT_TPP
#define TPOINT_TPP

template <typename T, uint32_t dims>
T TPoint<T, dims>::distance(TPoint<T, dims> a, TPoint<T, dims> b){
    return std::sqrt(std::inner_product(a.coords.begin(), a.coords.end(), b.coords.begin(), T(0),
                                        std::plus<T>(), [](T ap, T bp)
                                        { return std::pow(ap - bp, 2); }));
}

template <typename T, uint32_t dims>
T TPoint<T, dims>::distance(TPoint<T, dims> a)
{
    return distance(*this, a);
}

#endif /* TPOINT_TPP */
