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
T TPoint<T, dims>::distance(const TPoint<T, dims> &a, const TPoint<T, dims> &b)
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
T TPoint<T, dims>::distance(const TPoint<T, dims> &a) const
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
TPoint<T, dims>::TPoint(T arg, Args... args) : coords{{arg, static_cast<T>(args)...}} {}

// template <typename T, uint32_t dims>
// TPoint<T, dims>::TPoint(const TPoint<T, dims> &point) {
//		 this->coords = point.coords;
//	 }
template <typename T, uint32_t dims>
TPoint<T, dims>::TPoint() {
		 this->coords.fill(0);
	 }
/**
 * @brief Constructs a point with the provided TPoint<T, dims>.
 *
 * @tparam T Type of the TPoint<T, dims>.
 * @tparam dims Number of dimensions.
 * @param args Arguments used to initialize TPoint<T, dims>.
 */
template <typename T, uint32_t dims>
TPoint<T, dims>::TPoint(const TPoint<T, dims> &point)
{
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
TPoint<T, dims> TPoint<T, dims>::operator-(const TPoint<T, dims> &rhs) const
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

/**
 * @brief Generates a string representation of a vector of points.
 * 
 * This method generates a string representation of a vector of points.
 * 
 * @param arr The vector of points.
 * @return std::string The string representation of the vector of points.
 */
template <typename T, uint32_t dims>
std::string TPoint<T, dims>::print(const std::vector<TPoint<T, dims>> &arr)
{
	std::stringstream ss;
	for (auto p : arr)
		ss << p.print() << "\n";
	std::string ret = ss.str();
	ret.pop_back();
	return ret;
}

/**
 * @brief Generates a string representation of the given point.
 * 
 * This method generates a string representation of the specified point.
 * 
 * @param point The point to be represented as a string.
 * @return std::string The string representation of the point.
 */
template <typename T, uint32_t dims>
std::string TPoint<T, dims>::print(const TPoint<T, dims> &point)
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

/**
 * @brief Generates a string representation of this point.
 * 
 * This method generates a string representation of this point.
 * 
 * @return std::string The string representation of this point.
 */
template <typename T, uint32_t dims>
std::string TPoint<T, dims>::print()
{
	return TPoint<T, dims>::print(*this);
}

/**
 * @brief Retrieves the coordinates of this point as an array.
 * 
 * This method retrieves the coordinates of this point as an array.
 * 
 * @return std::array<T, dims> The coordinates of this point.
 */
template <typename T, uint32_t dims>
std::array<T, dims> TPoint<T, dims>::point()
{
	return TPoint<T, dims>::point((const TPoint<T, dims>&)*this);
}

/**
 * @brief Retrieves the coordinates of the given point as an array.
 * 
 * This method retrieves the coordinates of the specified point as an array.
 * 
 * @param point The point.
 * @return std::array<T, dims> The coordinates of the point.
 */
template <typename T, uint32_t dims>
std::array<T, dims> TPoint<T, dims>::point(const TPoint<T, dims> &point)
{
	return point.coords;
}

/**
 * @brief Computes the dot product of two points.
 * 
 * This method computes the dot product of two points.
 * 
 * @param a The first point.
 * @param b The second point.
 * @return T The dot product of the two points.
 */
template <typename T, uint32_t dims>
T TPoint<T, dims>::dot(TPoint a, TPoint b)
{
	return std::inner_product(a.coords.begin(), a.coords.end(), b.coords.begin(), T{0});
}

/**
 * @brief Computes the dot product of this point with another point.
 * 
 * This method computes the dot product of this point with the specified point.
 * 
 * @param a The other point.
 * @return T The dot product of this point with the other point.
 */
template <typename T, uint32_t dims>
T TPoint<T, dims>::dot(TPoint a)
{
	return TPoint<T, dims>::dot(*this, a);
}

/**
 * @brief Computes the cross product of two 3-dimensional points.
 * 
 * This method computes the cross product of two 3-dimensional points.
 * 
 * @param p1 The first point.
 * @param p2 The second point.
 * @return TPoint<T, dims> The cross product of the two points.
 * @throw std::logic_error Thrown if the dimensions of the points are not equal to 3.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TPoint<T, dims>::cross(const TPoint<T, dims>& p1, const TPoint<T, dims>& p2)
{
	static_assert(dims == 3, "TPoint: TPoint dimensions must be equal to 3, for that the cross product doesn't work for any other number of dimensions.\n");
	return TPoint<T, dims>((p1.coords.at(1)) * (p2.coords.at(2)) - (p2.coords.at(1)) * (p1.coords.at(2)),
						   (p1.coords.at(2)) * (p2.coords.at(0)) - (p2.coords.at(2)) * (p1.coords.at(0)),
						   (p1.coords.at(0)) * (p2.coords.at(1)) - (p2.coords.at(0)) * (p1.coords.at(1)));
}

/**
 * @brief Checks if this point is equal to another point.
 * 
 * This method checks if this point is equal to the specified point.
 * 
 * @param rhs The other point.
 * @return true if the points are equal, false otherwise.
 */
template <typename T, uint32_t dims>
bool TPoint<T, dims>::operator==(const TPoint<T, dims> &rhs)
{
	return this->distance(rhs) <= std::numeric_limits<T>::epsilon();
}

#endif /* TPOINT_TPP */
