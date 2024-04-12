#include <limits>
#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <inttypes.h>

#include "TVector.hpp"
#include "TPoint.hpp"

#ifndef LINE_HPP
#define LINE_HPP

template <typename T, uint32_t dims>
class TLine : public TVector<T, dims>
{
	public:
		TPoint<T, dims> origin;
		// T get_angle();
		// T get_angle(TLine);
		// static T get_angle(TLine, TLine);
		// static T get_distance(TLine, TPoint<T, dims>);
		TLine();
		// TLine(TVector<T, dims>);
		TLine(TPoint<T, dims>, TPoint<T, dims>);

		T distance(TPoint<T, dims>);
		T distance(TLine);
		static T distance(TLine, const TPoint<T, dims>&);
		static T distance(TLine, TLine);
		// T get_distance(TLine);
		// static T get_distance(TLine, TLine);
		bool is_on(const TPoint<T, dims>&);
		static bool is_on(const TLine &line, const TPoint<T, dims>& point, T epsilon = std::numeric_limits<T>::epsilon() * 2048);
		
		
		// TLine make_parallel(TPoint<T, dims>);
		// TLine make_perpendicular(TPoint<T, dims>);
		// TLine make_perpendicular();
		// static TLine make_axis(TLine, TLine);
		static std::string print(const TLine&);
		std::string print();
		TPoint<T, dims> at(const T&);
		
		
		// static bool on_segment(TPoint<T, dims>, TPoint<T, dims>, TPoint<T, dims>);
		// TLine operator /(T);
		// static TPoint<T, dims> intersection(TLine, TLine);
		// TPoint<T, dims> intersection(TLine);
	private:
		
};

#include "TLine.cpp"

typedef TLine<float, 2> Line2D;
typedef TLine<float, 3> Line3D;
#endif /* LINE_HPP */ 