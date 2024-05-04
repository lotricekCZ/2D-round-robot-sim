/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#include <cmath>
#include <string>
#include <vector>
#include <array>
#include <limits>
#include <string>
#include <iostream>
#include <cinttypes>

#include "TPoint.hpp"
#include "TLine.hpp"
// #include "TLine.hpp"

#ifndef TCIRCLE_HPP
#define TCIRCLE_HPP

template <typename T, uint32_t dims>
class TCircle
{
	T radius = 1;
	TPoint<T, dims> circle_center;

public:
	TCircle(T radius, TPoint<T, dims>);

	template <typename... Args>
	TCircle(T radius, Args...);

	static std::vector<TCircle> circles(TLine<T, dims>, TLine<T, dims>, T radius = 1);
	static std::vector<TPoint<T, dims>> tangent_points(TCircle c, TPoint<T, dims> point);

	static std::vector<TPoint<T, dims>> intersection(TCircle, TLine<T, dims>); // function to decide if sth intersects
	static std::vector<TPoint<T, dims>> intersection(TCircle k, TCircle c);

	static std::vector<TLine<T, dims>> tangents(TCircle c, TPoint<T, dims> point);
	static std::vector<TLine<T, dims>> tangents(TCircle a, TCircle b);
	static void tangents(TPoint<T, dims> c, T r1, T r2, std::vector<TLine<T, dims>> &ans);
	static TPoint<T, dims> at(TCircle&, T);
	bool inside(TPoint<T, dims> a);
	bool is_on(TPoint<T, dims> c, T epsilon = std::numeric_limits<T>::epsilon() * 2048);
	static TPoint<T, dims> center(TCircle);
	TPoint<T, dims> center();
	std::vector<TPoint<T, dims>> tangent_points(TPoint<T, dims> point);
	std::vector<TPoint<T, dims>> points();

	std::vector<TPoint<T, dims>> intersection(TLine<T, dims>); // function to decide if sth intersects
	std::vector<TPoint<T, dims>> intersection(TCircle);
	TPoint<T, dims> at(T);
	std::vector<TLine<T, dims>> tangents(TPoint<T, dims> point);
	std::vector<TLine<T, dims>> tangents(TCircle c);
	std::string print();
	static std::string print(TCircle &);
	

	static T distance(TCircle, TPoint<T, dims>);
	static T distance(TCircle, TLine<T, dims>);
	static T distance(TCircle, TPoint<T, dims>, TPoint<T, dims>);

	T distance(TPoint<T, dims>);
	T distance(TLine<T, dims>);
	T distance(TPoint<T, dims>, TPoint<T, dims>);

	bool operator==(const TCircle &rhs)
	{
		return this->center == rhs.center && this->radius == rhs.radius;
	}

	bool operator!=(const TCircle &rhs)
	{
		return !(*this == rhs);
	}

	TCircle operator+(const T &rhs)
	{
		return TCircle(this->center, this->radius + rhs);
	}

	TCircle operator-(const T &rhs)
	{
		return TCircle(this->center, (this->radius - rhs < 0) ? 0 : this->radius - rhs);
	}

private:
	/* add your private declarations */
};

#include "TCircle.cpp"
typedef TCircle<float, 2> Circle2D;
typedef TCircle<float, 3> Circle3D;

#endif /* OBSTACLE_HPP */