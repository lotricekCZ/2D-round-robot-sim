#ifndef TPOINT_TPP
#define TPOINT_TPP
#include <functional>
#include <cinttypes>
#include <iostream>
#include "TPoint.hpp"
/**
 * @brief Calculates the Euclidean distance between two points in the same dimensional space.
 *
 * @tparam T Type of the TPoint<T, dims>.
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
 * @tparam T Type of the TPoint<T, dims>.
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
 * @brief Constructs a point with the provided TPoint<T, dims>.
 *
 * @tparam T Type of the TPoint<T, dims>.
 * @tparam dims Number of dimensions.
 * @tparam Args Types of arguments used to initialize TPoint<T, dims>.
 * @param args Arguments used to initialize TPoint<T, dims>.
 */
template <typename T, uint32_t dims>
template <typename... Args>
TPoint<T, dims>::TPoint(Args... args) : coords{{static_cast<T>(args)...}} {}

/**
 * @brief Constructs a point with the provided TPoint<T, dims>.
 *
 * @tparam T Type of the TPoint<T, dims>.
 * @tparam dims Number of dimensions.
 * @param args Arguments used to initialize TPoint<T, dims>.
 */
template <typename T, uint32_t dims>
TPoint<T, dims>::TPoint(TPoint<T, dims> &point) {
	*this = point;
}

/**
 * @brief Subtracts the coordinates of the given point from the coordinates of this point.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @param rhs The point whose coordinates will be subtracted from this point's coordinates.
 * @return A new point representing the result of the subtraction.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TPoint<T, dims>::operator-(const TPoint<T, dims> &rhs)
{
	TPoint<T, dims> result;
	std::transform(coords.begin(), coords.end(), rhs.coords.begin(), result.coords.begin(),
				   [](const T &a, const T &b)
				   { return a - b; });
	return result;
}

/**
 * @brief Adds the coordinates of the given point to the coordinates of this point.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @param rhs The point whose coordinates will be added to this point's coordinates.
 * @return A new point representing the result of the addition.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TPoint<T, dims>::operator+(const TPoint<T, dims> &rhs)
{
	TPoint<T, dims> result;
	std::transform(coords.begin(), coords.end(), rhs.coords.begin(), result.coords.begin(),
				   [](const T &a, const T &b)
				   { return a + b; });
	return result;
}

/**
 * @brief Divides all coordinates of this point by the given value.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @param rhs The value by which to divide the coordinates.
 * @return A new point representing the result of the division.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TPoint<T, dims>::operator/(const T &rhs)
{
	TPoint<T, dims> result;
	std::transform(coords.begin(), coords.end(), result.coords.begin(),
				   [rhs](const T &a)
				   { return a / rhs; });
	return result;
}

/**
 * @brief Multiplies all coordinates of this point by the given value.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @param rhs The value by which to multiply the coordinates.
 * @return A new point representing the result of the multiplication.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TPoint<T, dims>::operator*(const T &rhs)
{
	TPoint<T, dims> result;
	std::transform(coords.begin(), coords.end(), result.coords.begin(),
				   [rhs](const T &a)
				   { return a * rhs; });
	return result;
}

/**
 * @brief Multiplies all coordinates of this point by the given value and assigns the result to this point.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @param rhs The value by which to multiply the coordinates.
 * @return Reference to this point after multiplication.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TPoint<T, dims>::operator*=(const T &rhs)
{
	*this = *this * rhs;
	return *this;
}

/**
 * @brief Subtracts the coordinates of the given point from the coordinates of this point and assigns the result to this point.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @param rhs The point whose coordinates will be subtracted from this point's coordinates.
 * @return Reference to this point after subtraction.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TPoint<T, dims>::operator-=(const TPoint<T, dims> &rhs)
{
	*this = *this - rhs;
	return *this;
}

template <typename T, uint32_t dims>
std::string TPoint<T, dims>::print(const TPoint<T, dims>& point)
{
	std::stringstream ss;
	ss << "(";
	for (auto i : point.coords)
	{
		ss << i << ", ";
	}
	ss.seekp(-2, std::ios_base::cur);
	ss << ")";
	std::string ret = ss.str();
	ret.pop_back();
	return ret;
}

template <typename T, uint32_t dims>
std::string TPoint<T, dims>::print()
{
	return TPoint<T, dims>::print(*this);
}

template <typename T, uint32_t dims>
std::array<T, dims> TPoint<T, dims>::point()
{
	return TPoint<T, dims>::point(*this);
}

template <typename T, uint32_t dims>
std::array<T, dims> TPoint<T, dims>::point(TPoint<T, dims> &point)
{
	return point.coords;
}

template <typename T, uint32_t dims>
T TPoint<T, dims>::dot(TPoint a, TPoint b)
{
	return std::inner_product(a.coords.begin(), a.coords.end(), b.coords.begin(), T{0});
}

template <typename T, uint32_t dims>
T TPoint<T, dims>::dot(TPoint a)
{
	return TPoint<T, dims>::dot(*this, a);
}
#endif /* TPOINT_TPP */
