#include <vector>
#include <algorithm>
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
	this->circle_center = TPoint<T, dims>(args...);
	this->_radius = r;
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
	this->circle_center = c;
	this->_radius = r;
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
	return TPoint<T, dims>::distance(circle_center, a) < _radius;
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
	return TCircle<T, dims>::distance(*this, c) <= epsilon;
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
	std::vector<TPoint<T, dims>> ret = {};
	// Implement intersection calculation here
	auto d = l.distance(c.center());
	if (d > c._radius)
		return ret;
	T alpha = std::acos(d / c._radius);
	T beta = std::atan2(l.d(1), l.d(0)) + M_PI_2;

	ret.push_back(c.at((beta + alpha) / (2 * M_PI)));
	if (std::abs(alpha) > std::numeric_limits<T>::epsilon())
		ret.push_back(c.at((beta - alpha) / (2 * M_PI)));
	
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
	auto dist = TVector<T, dims>(k.circle_center, c.circle_center);
	if (dist.length() > (k._radius + c._radius))
		return ret;
	T alpha = std::acos((std::pow(k._radius, 2) + std::pow(dist.length(), 2) - std::pow(c._radius, 2)) / (2 * k._radius * dist.length()));
	T theta = std::atan2((dist.d(1)), (dist.d(0)));
	ret.push_back(k.at((theta + alpha) / (2 * M_PI)));
	if (std::abs(alpha) > std::numeric_limits<T>::epsilon())
		ret.push_back(k.at((theta - alpha) / (2 * M_PI)));
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
	return circ.circle_center + TPoint<T, dims>(std::cos(2 * M_PI * par), std::sin(2 * M_PI * par)) * circ._radius;
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
 * @brief Calculates the tangents of two circles in 2D.
 *
 * @tparam T The data type of circle points (e.g., float, double, etc.).
 * @tparam dims The number of dimensions in which the circles reside. Only 2D circles are supported.
 * @param a The first circle.
 * @param b The second circle.
 * @return std::vector<TLine<T, dims>> A vector containing the tangents of the two circles.
 */
template <typename T, uint32_t dims>
std::vector<TLine<T, dims>> TCircle<T, dims>::tangents(TCircle<T, dims> a, TCircle<T, dims> b)
{
	static_assert(dims == 2, "TCircle::tangents is supported only for 2D circles");
	std::vector<TLine<T, dims>> ans;
	TVector<T, dims> c2c(a.circle_center, b.circle_center); // vector from center of circle to center of circle

	// Calculate angles for tangents
	T theta = std::atan2((c2c.d(1)), (c2c.d(0)));
	T alpha = std::acos((a._radius - b._radius) / (c2c.length()));

	// Add the first pair of tangents
	ans.emplace_back(a.at((theta + alpha) / (2 * M_PI)), b.at((theta + alpha) / (2 * M_PI)));
	ans.emplace_back(a.at((theta - alpha) / (2 * M_PI)), b.at((theta - alpha) / (2 * M_PI)));

	// If the distance between circle centers is greater than the sum of their radii, add another pair of tangents
	if (c2c.length() > (a._radius + b._radius))
	{
		alpha = std::acos((a._radius + b._radius) / (c2c.length()));
		ans.emplace_back(a.at((theta + alpha) / (2 * M_PI)), b.at((theta + alpha + M_PI) / (2 * M_PI)));
		ans.emplace_back(a.at((theta - alpha) / (2 * M_PI)), b.at((theta - alpha + M_PI) / (2 * M_PI)));
	}

	return ans;
}

/**
 * @brief Computes tangents between this circle and another circle.
 *
 * This method calculates the tangents between this circle and the provided circle.
 * It returns a vector of lines representing the tangents.
 *
 * @param a The other circle to compute tangents with.
 * @return std::vector<TLine<T, dims>> Vector of lines representing the tangents between this circle and the provided circle.
 */
template <typename T, uint32_t dims>
std::vector<TLine<T, dims>> TCircle<T, dims>::tangents(TCircle<T, dims> a)
{
	return TCircle<T, dims>::tangents(*this, a);
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
	ss << TPoint<T, dims>::print(a.circle_center) << " + " << a._radius << "(cos(2 π t), sin(2 π t))";
	return ss.str();
}


/**
 * @brief Computes the distance from a point to the circumference of a circle.
 *
 * This method calculates the distance from a given point to the circumference of the circle.
 *
 * @param circ The circle to which the distance is computed.
 * @param point The point for which the distance to the circumference is calculated.
 * @return T The distance from the point to the circumference of the circle.
 */
template <typename T, uint32_t dims>
T TCircle<T, dims>::distance(TCircle<T, dims> circ, TPoint<T, dims> point)
{
	return std::abs(point.distance(circ.circle_center) - circ._radius);
}

/**
 * @brief Computes the distance from a point to the circumference of this circle.
 *
 * This method calculates the distance from a given point to the circumference of this circle.
 *
 * @param co The point for which the distance to the circumference is calculated.
 * @return T The distance from the point to the circumference of this circle.
 */
template <typename T, uint32_t dims>
T TCircle<T, dims>::distance(TPoint<T, dims> co)
{
	return distance((*this), co);
}

/**
 * @brief Computes the distance from a circle to the circumference of another circle.
 *
 * This method calculates the distance from the circumference of a given circle to the circumference of another circle.
 *
 * @param ci The circle to which the distance is computed.
 * @param l The line for which the distance to the circumference is calculated.
 * @return T The distance from the circumference of the circle to the line.
 */
template <typename T, uint32_t dims>
T TCircle<T, dims>::distance(TCircle<T, dims> ci, TLine<T, dims> l)
{
	auto p = l.distance(ci.circle_center);
	std::cout << std::abs(ci._radius - p) << std::endl;
	return ((ci._radius >= p)) ? 0 : p;
}

/**
 * @brief Computes the distance from this circle to the circumference of a line.
 *
 * This method calculates the distance from the circumference of this circle to a given line.
 *
 * @param li The line for which the distance to the circumference is calculated.
 * @return T The distance from the circumference of this circle to the line.
 */
template <typename T, uint32_t dims>
T TCircle<T, dims>::distance(TLine<T, dims> li)
{
	return distance((*this), li);
}


/**
 * @brief Computes the center point of the given circle.
 *
 * This method returns the center point of the specified circle.
 *
 * @param circle The circle for which the center point is computed.
 * @return TPoint<T, dims> The center point of the circle.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TCircle<T, dims>::center(TCircle<T, dims> circle)
{
	return circle.circle_center;
}

/**
 * @brief Returns radius of the circle.
 *
 * @return T radius of the circle.
 */
template <typename T, uint32_t dims>
T TCircle<T, dims>::radius()
{
	return _radius;
}

/**
 * @brief Computes the center point of this circle.
 *
 * This method returns the center point of this circle.
 *
 * @return TPoint<T, dims> The center point of this circle.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TCircle<T, dims>::center()
{
	return TCircle<T, dims>::center(*this);
}

template <typename T, uint32_t dims>
template <typename... Args>
void TCircle<T, dims>::reposition(Args... args){
	circle_center = circle_center + TPoint<T, dims>(args...);
}

template <typename T, uint32_t dims>
template <typename... Args>
void TCircle<T, dims>::place(Args... args){
	circle_center = TPoint<T, dims>(args...);
}

#endif

