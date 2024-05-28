/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#include <optional>
#include "TLine.hpp"
#include "TPoint.hpp"
#include "TVector.hpp"

#ifndef LINE_CPP
#define LINE_CPP

/**
 * @brief Constructs a line passing through two given points.
 * 
 * This constructor initializes a line passing through two given points.
 * 
 * @param a The first point.
 * @param b The second point.
 */
template <typename T, uint32_t dims>
TLine<T, dims>::TLine(TPoint<T, dims> a, TPoint<T, dims> b) : TVector<T, dims>(TVector<T, dims>(TPoint<T, dims>(), b - a).normalise()), origin(a)
{
}
/**
 * @brief Constructs a line passing through two given points.
 * 
 * This constructor initializes a line passing through two given points.
 * 
 * @param a The first point.
 * @param b The second point.
 */
template <typename T, uint32_t dims>
TLine<T, dims>::TLine(TVector<T, dims> dir, TPoint<T, dims> src) : TVector<T, dims>(dir.normalise()), origin(src)
{
}

/**
 * @brief Generates a string representation of the given line.
 * 
 * This method generates a string representation of the specified line.
 * 
 * @param line The line to be represented as a string.
 * @return std::string The string representation of the line.
 */
template <typename T, uint32_t dims>
std::string TLine<T, dims>::print(const TLine<T, dims> &line)
{
	return TPoint<T, dims>::print(line.origin) + " + t" + TVector<T, dims>::print(line);
}

/**
 * @brief Generates a string representation of this line.
 * 
 * This method generates a string representation of this line.
 * 
 * @return std::string The string representation of this line.
 */
template <typename T, uint32_t dims>
std::string TLine<T, dims>::print()
{
	return TLine<T, dims>::print(*this);
}

/**
 * @brief Computes the distance from this line to a given point.
 * 
 * This method computes the distance from this line to the specified point.
 * 
 * @param point The point for which the distance is computed.
 * @return T The distance from this line to the point.
 */
template <typename T, uint32_t dims>
T TLine<T, dims>::distance(TPoint<T, dims> point) const
{
	return TLine<T, dims>::distance(*this, point);
}

/**
 * @brief Computes the distance from a given line to a given point.
 * 
 * This method computes the distance from the specified line to the specified point.
 * 
 * @param line The line.
 * @param point The point.
 * @return T The distance from the line to the point.
 */
template <typename T, uint32_t dims>
T TLine<T, dims>::distance(TLine<T, dims> line, const TPoint<T, dims> &point)
{
	try
	{
		if (dims == 2)
		{
			std::array<T, dims> vec = line.get_point().point();
			std::array<T, dims> p1 = line.origin.point();
			std::array<T, dims> p0 = const_cast<TPoint<T, dims> &>(point).point();
			return std::abs(vec.at(0) * (p1.at(1) - p0.at(1)) - vec.at(1) * (p1.at(0) - p0.at(0))) / line.length();
		}
		T denom = TPoint<T, dims>::dot(line.get_point(), line.get_point());
		T frac = TPoint<T, dims>::dot(line.get_point(), point - line.origin);

		TPoint<T, dims> p2 = line.at(frac / denom);
		return TPoint<T, dims>::distance(p2, point);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return std::numeric_limits<T>::infinity();
	}
}

template <typename T, uint32_t dims>
T TLine<T, dims>::distance(TLine<T, dims> line)
{
	return TLine<T, dims>::distance(*this, line);
}

/**
 * @brief Computes the distance between two lines.
 * 
 * This method computes the distance between two lines.
 * 
 * @param line1 The first line.
 * @param line2 The second line.
 * @return T The distance between the two lines.
 */
template <typename T, uint32_t dims>
T TLine<T, dims>::distance(TLine<T, dims> line1, TLine<T, dims> line2)
{
	try
	{
		if constexpr (dims == 2)
		{
			if (line1.normalise().get_point() == line2.normalise().get_point())
			{
				return TLine<T, dims>::distance(line1, line2.origin);
			}
			else
			{
				return 0;
			}
		}
		else
		{
			if (line1.normalise().get_point() == line2.normalise().get_point())
			{
				return TVector<T, dims>(TPoint<T, dims>::cross(line1.get_point(), (line1.origin - line2.origin))).length() / line1.length();
			}
			return (TPoint<T, dims>::dot(line1.origin - line2.origin, TPoint<T, dims>::cross(line1.get_point(), line2.get_point())) / (TVector<T, dims>::cross(static_cast<TVector<T, dims> &>(line1), static_cast<TVector<T, dims> &>(line2)).length()));
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return std::numeric_limits<T>::infinity();
	}
}

/**
 * @brief Computes the point on this line at a given parameter value.
 * 
 * This method computes the point on this line at the specified parameter value.
 * 
 * @param a The parameter value.
 * @return TPoint<T, dims> The point on this line at the parameter value.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TLine<T, dims>::at(const T &a)
{
	try
	{
		return TPoint<T, dims>(this->origin + this->get_point() * a);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		std::cout << "moment" << std::endl;
		return TPoint<T, dims>(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
	}
}
template <typename T, uint32_t dims>
bool TLine<T, dims>::is_on(const TPoint<T, dims> &point)
{
	return TLine<T, dims>::is_on(*this, point);
}

/**
 * @brief Checks if a given point lies on a given line within a specified epsilon.
 * 
 * This method checks if the specified point lies on the specified line within the specified epsilon.
 * 
 * @param line The line to check.
 * @param point The point to check.
 * @param epsilon The epsilon value.
 * @return bool True if the point lies on the line within the epsilon, false otherwise.
 */
template <typename T, uint32_t dims>
bool TLine<T, dims>::is_on(const TLine<T, dims> &line, const TPoint<T, dims> &point, T epsilon)
{
	return TLine<T, dims>::distance(line, point) <= epsilon;
}

/**
 * @brief Computes the intersection point of two lines.
 * 
 * This method computes the intersection point of two lines.
 * 
 * @param first The first line.
 * @param second The second line.
 * @return std::optional<TPoint<T, dims>> The intersection point if it exists, otherwise std::nullopt.
 */
template <typename T, uint32_t dims>
std::optional<TPoint<T, dims>> TLine<T, dims>::intersection(const TLine<T, dims> &first, const TLine<T, dims> &second)
{
	if (TLine<T, dims>::distance(first, second) >= (std::numeric_limits<T>::epsilon() * 1024))
		return {};
	if constexpr (dims == 3)
	{
		T parameter = (TPoint<T, dims>::distance((TPoint<T, dims>::cross((second.origin - first.origin), static_cast<TVector<T, dims>>(second).get_point())), static_cast<TVector<T, dims>>(first).get_origin())) / (TVector<T, dims>::cross(static_cast<const TVector<T, dims> &>(first), static_cast<const TVector<T, dims> &>(second)).length());
		auto cand = static_cast<TLine<T, dims>>(first).at(-parameter);
		if (static_cast<TLine<T, dims>>(second).is_on(cand))
			return cand;
		return static_cast<TLine<T, dims>>(first).at(parameter);
	}
	if constexpr (dims == 2)
	{
		auto p0 = static_cast<TPoint<T, dims>>(first.origin).point();
		auto p1 = static_cast<TPoint<T, dims>>(second.origin).point();
		auto v0 = static_cast<TVector<T, dims>>(first).get_point().point();
		auto v1 = static_cast<TVector<T, dims>>(second).get_point().point();
		T parameter = (v1.at(0)* (p1.at(1) - p0.at(1)) + v1.at(1)* (p0.at(0) - p1.at(0))) / (v1.at(0) * v0.at(1) - v1.at(1) * v0.at(0));
		// auto cand = static_cast<TLine<T, dims>>(first).at(-parameter);
		// if (static_cast<TLine<T, dims>>(second).is_on(cand))
		// 	return cand;
		return static_cast<TLine<T, dims>>(first).at(parameter);
	}
	return {};
}

/**
 * @brief Computes the intersection point of this line with another line.
 * 
 * This method computes the intersection point of this line with another line.
 * 
 * @param line The other line.
 * @return std::optional<TPoint<T, dims>> The intersection point if it exists, otherwise std::nullopt.
 */
template <typename T, uint32_t dims>
std::optional<TPoint<T, dims>> TLine<T, dims>::intersection(const TLine<T, dims> &line)
{
	return TLine<T, dims>::intersection(*this, line);
}

#endif // LINE_CPP