#include <vector>
#include "TPoint.hpp"
#include "TCircle.hpp"
#include "TLine.hpp"

#ifndef TCIRCLE_CPP
#define TCIRCLE_CPP

/**
 * @brief Construct a new TCircle object
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @param r Radius of the circle
 * @param args Coordinates of the center of the circle
 */
template <typename T, uint32_t dims>
template <typename... Args>
TCircle<T, dims>::TCircle(T r, Args... args)
{
	this->center = TPoint<T, dims>(args...);
	this->radius = r;
}

/**
 * @brief Construct a new TCircle object
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @param r Radius of the circle
 * @param c Center point of the circle
 */
template <typename T, uint32_t dims>
TCircle<T, dims>::TCircle(T r, TPoint<T, dims> c)
{
	this->center = c;
	this->radius = r;
}

/**
 * @brief Check if a point is inside the circle
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @param a Point to check
 * @return true if the point is inside the circle
 * @return false if the point is outside the circle
 */
template <typename T, uint32_t dims>
bool TCircle<T, dims>::inside(TPoint<T, dims> a)
{
	return TPoint<T, dims>::distance(center, a) < radius;
}

/**
 * @brief Check if a point is on the circle
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @param c Point to check
 * @param epsilon Epsilon for floating point comparison
 * @return true if the point is on the circle
 * @return false if the point is not on the circle
 */
template <typename T, uint32_t dims>
bool TCircle<T, dims>::is_on(TPoint<T, dims> c, T epsilon)
{
	return std::abs(TPoint<T, dims>::distance(center, c) - radius) <= epsilon;
}

/**
 * @brief Get the points object
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @return std::vector<TPoint<T, dims>> Vector of points (empty for a circle)
 */
template <typename T, uint32_t dims>
std::vector<TPoint<T, dims>> TCircle<T, dims>::points()
{
	return std::vector<TPoint<T, dims>>();
}

/**
 * @brief Find the intersection points between a circle and a line
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @param c Circle to intersect
 * @param l Line to intersect
 * @return std::vector<TPoint<T, dims>> Vector of intersection points
 */
template <typename T, uint32_t dims>
std::vector<TPoint<T, dims>> TCircle<T, dims>::intersection(TCircle<T, dims> c, TLine<T, dims> l)
{
	static_assert(dims == 2, "TCircle: dimensions other than 2D are not yet supported");
	std::vector<TPoint<T, dims>> ret;
	// Implement intersection calculation here
	return ret;
}

/**
 * @brief Find the intersection points between a circle and a line
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @param l Line to intersect
 * @return std::vector<TPoint<T, dims>> Vector of intersection points
 */
template <typename T, uint32_t dims>
std::vector<TPoint<T, dims>> TCircle<T, dims>::intersection(TLine<T, dims> l)
{
	return intersection(*this, l);
}

/**
 * @brief Find the intersection points between two circles
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @param k First circle
 * @param c Second circle
 * @return std::vector<TPoint<T, dims>> Vector of intersection points
 */
template <typename T, uint32_t dims>
std::vector<TPoint<T, dims>> TCircle<T, dims>::intersection(TCircle k, TCircle c)
{
	std::vector<TPoint<T, dims>> ret;
	auto vec = TVector<T, dims>(k.center, c.center) * ((std::pow(k.radius, 2)) / (std::pow(k.radius, 2) + std::pow(c.radius, 2)));
	std::cout << vec.get_point().print() << std::endl;

	T alpha = std::acos(vec.length() / (k.radius));
	T theta = std::atan2((vec.d(1)), (vec.d(0)));
	std::cout << k.at((theta + alpha) / (2 * M_PI)).print() << std::endl;
	std::cout << k.at((theta - alpha) / (2 * M_PI)).print() << std::endl;
	return ret;
}

/**
 * @brief Find the intersection points between two circles
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @param c Second circle
 * @return std::vector<TPoint<T, dims>> Vector of intersection points
 */
template <typename T, uint32_t dims>
std::vector<TPoint<T, dims>> TCircle<T, dims>::intersection(TCircle c)
{
	return intersection(*this, c);
}

/**
 * @brief Get the point at a given parameter value on the circle
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @param circ Circle
 * @param par Parameter value
 * @return TPoint<T, dims> Point on the circle at the given parameter value
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TCircle<T, dims>::at(TCircle<T, dims> &circ, T par)
{
	return circ.center + TPoint<T, dims>(std::cos(2 * M_PI * par), std::sin(2 * M_PI * par)) * circ.radius;
}

/**
 * @brief Get the point at a given parameter value on the circle
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @param par Parameter value
 * @return TPoint<T, dims> Point on the circle at the given parameter value
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TCircle<T, dims>::at(T par)
{
	return TCircle<T, dims>::at(*this, par);
}
/**
 * @brief Print the circle equation.
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @return std::string String representation of the circle equation
 */
template <typename T, uint32_t dims>
std::string TCircle<T, dims>::print()
{
	return TCircle<T, dims>::print(*this);
}

/**
 * @brief Print the circle equation.
 *
 * @tparam T Data type for the coordinates
 * @tparam dims Number of dimensions
 * @param a Circle object to print
 * @return std::string String representation of the circle equation
 */
template <typename T, uint32_t dims>
std::string TCircle<T, dims>::print(TCircle<T, dims> &a)
{
	std::stringstream ss;
	ss << TPoint<T, dims>::print(a.center) << " + " << a.radius << "(cos(2 π t), sin(2 π t))";
	return ss.str();
}

#endif
