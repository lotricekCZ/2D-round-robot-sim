#ifndef TPOINT_TPP
#define TPOINT_TPP

/**
 * @brief Calculates the Euclidean distance between two points in the same dimensional space.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @param a First point.
 * @param b Second point.
 * @return The Euclidean distance between points 'a' and 'b'.
 */
template <typename T, uint32_t dims>
T TPoint<T, dims>::distance(TPoint<T, dims> a, TPoint<T, dims> b)
{
    return std::sqrt(std::inner_product(a.coords.begin(), a.coords.end(), b.coords.begin(), T(0),
                                        std::plus<T>(), [](T ap, T bp)
                                        { return std::pow(ap - bp, 2); }));
}

/**
 * @brief Calculates the Euclidean distance between the current point and another point using the static version of the function.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @param a The other point.
 * @return The Euclidean distance between the current point and point 'a'.
 */
template <typename T, uint32_t dims>
T TPoint<T, dims>::distance(TPoint<T, dims> a)
{
    return distance(*this, a);
}

/**
 * @brief Constructs a point with the provided coordinates.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @tparam Args Types of arguments used to initialize coordinates.
 * @param args Arguments used to initialize coordinates.
 */
template <typename T, uint32_t dims>
template <typename... Args>
TPoint<T, dims>::TPoint(Args... args)
{
    coords = std::array<T, dims>{{static_cast<T>(args)...}};
};

#endif /* TPOINT_TPP */
