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
	this->circle_center = TPoint<T, dims>(args...);
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
	this->circle_center = c;
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
	return TPoint<T, dims>::distance(circle_center, a) < radius;
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
	std::vector<TPoint<T, dims>> ret;
	// Implement intersection calculation here
	auto d = c.distance(l);
	if (d != 0)
		return ret;
	T alpha = std::acos(d / c.radius);
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
	if (dist.length() > (k.radius + c.radius))
		return ret;
	T alpha = std::acos((std::pow(k.radius, 2) + std::pow(dist.length(), 2) - std::pow(c.radius, 2)) / (2 * k.radius * dist.length()));
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
	return circ.circle_center + TPoint<T, dims>(std::cos(2 * M_PI * par), std::sin(2 * M_PI * par)) * circ.radius;
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
	T alpha = std::acos((a.radius - b.radius) / (c2c.length()));

	// Add the first pair of tangents
	ans.emplace_back(a.at((theta + alpha) / (2 * M_PI)), b.at((theta + alpha) / (2 * M_PI)));
	ans.emplace_back(a.at((theta - alpha) / (2 * M_PI)), b.at((theta - alpha) / (2 * M_PI)));

	// If the distance between circle centers is greater than the sum of their radii, add another pair of tangents
	if (c2c.length() > (a.radius + b.radius))
	{
		alpha = std::acos((a.radius + b.radius) / (c2c.length()));
		ans.emplace_back(a.at((theta + alpha) / (2 * M_PI)), b.at((theta + alpha + M_PI) / (2 * M_PI)));
		ans.emplace_back(a.at((theta - alpha) / (2 * M_PI)), b.at((theta - alpha + M_PI) / (2 * M_PI)));
	}

	return ans;
}


template <typename T, uint32_t dims>
std::vector<TLine<T, dims>> TCircle<T, dims>::tangents(TCircle<T, dims> a)
{
	return TCircle<T, dims>::tangents(*this, a);
}

// template <typename T, uint32_t dims>
// std::vector<TPoint<T, dims>> TCircle<T, dims>::tangent_points(TCircle c, TPoint<T, dims> point){
// 	T diff_x = point.x - c.center.x;
// 	T diff_y = point.y - c.center.y;
// 	T dxr = -diff_y;
// 	T dyr = diff_x;
// 	T distance = c.center.distance(point);
// 	std::vector<TPoint<T, dims>> ret;
// 	if (distance >= c.radius){
// 		T rho = c.radius / distance;
// 		T ad = std::pow(rho, 2);
// 		T bd = rho * std::sqrt(1-std::pow(rho, 2));
// 		ret.assign({TPoint<T, dims>(c.center.x + ad * diff_x + bd * dxr, c.center.y + ad * diff_y + bd * dyr),
// 					TPoint<T, dims>(c.center.x + ad * diff_x - bd * dxr, c.center.y + ad * diff_y - bd * dyr)});
// 		}
// 	return ret;
// }

// template <typename T, uint32_t dims>
// std::vector<TPoint<T, dims>> TCircle<T, dims>::tangent_points(TPoint<T, dims> point){
// 	return TCircle<T, dims>::tangent_points(*this, point);
// }

// template <typename T, uint32_t dims>
// std::vector<TLine<T, dims>> TCircle<T, dims>::tangents(TCircle c, TPoint<T, dims> point){
// 	std::vector<TLine<T, dims>> ret;
// 	if(c.is_on(point)){
// 		ret.push_back(TLine<T, dims>(c.center, point).make_perpendicular(point));
// 		return ret;
// 		}
// 	for(auto i: TCircle<T, dims>::tangent_points(c, point))
// 		ret.emplace_back(point, i);
// 	return ret;
// }

// template <typename T, uint32_t dims>
// std::vector<TLine<T, dims>> TCircle<T, dims>::tangents(TPoint<T, dims> point){
// 	return TCircle<T, dims>::tangents(*this, point);
// }

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
	ss << TPoint<T, dims>::print(a.circle_center) << " + " << a.radius << "(cos(2 π t), sin(2 π t))";
	return ss.str();
}

// template <typename T, uint32_t dims>
// bool TCircle<T, dims>::on_segment(TPoint<T, dims> start, TPoint<T, dims> end, TPoint<T, dims> point, bool angle){
// 	if(!is_on(point)){
// 		return false;
// 		}

// 	TLine<T, dims> cut(start, end);
// 	TLine<T, dims> perp = cut.make_perpendicular(this -> center);

// 	std::vector<TPoint<T, dims>> intersections = intersection(perp, (*this));
// 	/// it's sure there are exactly two intersections, both do have exact same distance to start and end
// 	T d0 = start.distance(intersections[0]);
// 	T d1 = start.distance(intersections[1]);
// 	T max;
// 	TPoint<T, dims>* p_center;
// 	if(d0 > d1){ // checks which of them is further -> that one also has bigger angle
// 		p_center = &intersections[0];
// 		max = d0;
// 		}else{
// 			p_center = &intersections[1];
// 			max = d1;
// 			}

// 	// returns true if the point is on bigger segment if bigger angle is set (1)
// 	// it is checked by a fact that it is actually closer than start/end
// 	// if that is not the case, it already is on the TCircle, so it must be on the smaller angle
// 	return angle == (p_center -> distance(point) < max);
// 	};

// template <typename T, uint32_t dims>
// std::vector<TCircle<T, dims>> TCircle<T, dims>::TCircles(TLine<T, dims> a, TLine<T, dims> b, T radius){
// 	std::vector<TCircle> ret;
// 	TPoint<T, dims> intersection = a.intersection(b);
// 	if(intersection.is_invalid()){
// 		return ret;
// 	}
// 	T angle = a.get_angle(b);
// 	//~ std::cout << intersection.print() << std::endl;
// 	ret.emplace_back(intersection.make_global(TPoint<T, dims>(0, radius / (sin(angle/2))), ((a.get_angle() + b.get_angle())/2)-pi_const), radius);
// 	ret.emplace_back(intersection.make_global(TPoint<T, dims>(0, -radius / (sin(angle/2))), ((a.get_angle() + b.get_angle())/2)-pi_const), radius);
// 	ret.emplace_back(intersection.make_global(TPoint<T, dims>(radius / (sin(pi_const/2 -angle/2)), 0), ((a.get_angle() + b.get_angle())/2)-pi_const), radius);
// 	ret.emplace_back(intersection.make_global(TPoint<T, dims>(-radius / (sin(pi_const/2 -angle/2)), 0), ((a.get_angle() + b.get_angle())/2)-pi_const), radius);

// 	return ret;
// 	}

template <typename T, uint32_t dims>
T TCircle<T, dims>::distance(TCircle<T, dims> circ, TPoint<T, dims> point)
{ // gets the distance from circumference
	return std::abs(point.distance(circ.circle_center) - circ.radius);
}

template <typename T, uint32_t dims>
T TCircle<T, dims>::distance(TPoint<T, dims> co)
{ // gets the distance from circumference
	return distance((*this), co);
}

template <typename T, uint32_t dims>
T TCircle<T, dims>::distance(TCircle<T, dims> ci, TLine<T, dims> l)
{ // gets the distance from circumference
	auto p = l.distance(ci.circle_center);
	return (ci.radius > p) ? 0 : p;
}

template <typename T, uint32_t dims>
T TCircle<T, dims>::distance(TLine<T, dims> li)
{ // gets the distance from circumference
	return distance((*this), li);
}

// template <typename T, uint32_t dims>
// T TCircle<T, dims>::distance(TCircle c, TPoint<T, dims> a, TPoint<T, dims> b){
// 	std::array<T, 2> distances_ab = {c.center.distance(a), c.center.distance(b)};

// 	if((c.radius < distances_ab[0]) ^ (c.radius < distances_ab[1])){
// 		/// fact that one of the TPoint<T, dims> is closer and the other further means that it has on_segment intersection
// 		return 0;
// 		}

// 	TLine<T, dims> l(a, b);
// 	std::vector<TPoint<T, dims>> intersections = c.intersection(l);
// 	if(intersections.size() == 0){
// 		/// means the segment is outside - treat it as a TLine<T, dims> for some part
// 		TLine<T, dims> p = l.make_perpendicular(c.center);

// 		TPoint<T, dims> inter = p.intersection(l);
// 		std::cout << c.center.print() << std::endl;
// 		std::cout << p.print() << std::endl;
// 		std::cout << inter.print() << std::endl;
// 		return std::abs(((l.on_segment(inter, a, b))? c.center.distance(inter):
// 									((distances_ab[0] < distances_ab[1])? distances_ab[0]: distances_ab[1])) - c.radius);
// 		}

// 	return std::abs((distances_ab[0] > distances_ab[1]? distances_ab[0]: distances_ab[1]) - c.radius);
// 	}

// template <typename T, uint32_t dims>
// T TCircle<T, dims>::distance(TPoint<T, dims> a, TPoint<T, dims> b){
// 	return distance((*this), a, b);
// 	}


template <typename T, uint32_t dims>
TPoint<T, dims> TCircle<T, dims>::center(TCircle<T, dims> circle)
{
	return circle.circle_center;
}

template <typename T, uint32_t dims>
TPoint<T, dims> TCircle<T, dims>::center()
{
	return TCircle<T, dims>::center(*this);
}

#endif
