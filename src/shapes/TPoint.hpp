#ifndef TPOINT_HPP
#define TPOINT_HPP

#include <cmath>
#include <vector>
#include <array>
#include <numeric>
#include <algorithm>
#include <cinttypes>
#include <functional>
#include <sstream>

template <typename T, uint32_t dims>
class TPoint
{
	std::array<T, dims> coords;

public:
	template <typename... Args>
	TPoint(Args...);
	TPoint(const TPoint &);
	static std::string print(const TPoint &);
	static std::string print(const std::vector<TPoint> &);
	std::string print();
	static std::array<T, dims> point(const TPoint &);
	static T distance(const TPoint<T, dims> &a, const TPoint<T, dims> &b);
	static T dot(TPoint, TPoint);
	T dot(TPoint);
	static TPoint cross(const TPoint&, const TPoint&);
	std::array<T, dims> point();
	T distance(const TPoint<T, dims> &a);
	TPoint operator-(const TPoint<T, dims> &rhs) const;
	TPoint operator+(const TPoint &rhs);
	TPoint operator/(const T &rhs);
	TPoint operator*(const T &rhs);
	TPoint operator*=(const T &rhs);
	TPoint operator-=(const TPoint &rhs);

	bool operator==(const TPoint &rhs);
};

#include "TPoint.cpp"

typedef TPoint<float, 2> Point2D;
typedef TPoint<float, 3> Point3D;
template <typename T, uint32_t dims>
using TPoints = std::vector<TPoint<T, dims>>;
typedef std::vector<Point2D> Points2D;
typedef std::vector<Point3D> Points3D;

#endif /* TPOINT_HPP */
