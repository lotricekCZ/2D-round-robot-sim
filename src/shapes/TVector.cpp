/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#ifndef TVECTOR_CPP
#define TVECTOR_CPP

#include <cinttypes>
#include "TVector.hpp"

/**
 * @brief Default constructor for TVector.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 */
template <typename T, uint32_t dims>
TVector<T, dims>::TVector() {}

// /**
//  * @brief Default constructor for TVector.
//  *
//  * @tparam T Type of the coordinates.
//  * @tparam dims Number of dimensions.
//  */
// template <typename T, uint32_t dims>
// TVector<T, dims>::TVector(TVector<T, dims> &vector) {
//	 *this = vector;
// }

/**
 * @brief Default constructor for TVector.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 */
template <typename T, uint32_t dims>
TVector<T, dims>::TVector(const TVector<T, dims> &vector)
{
	*this = vector;
}

template <typename T, uint32_t dims>
template <typename... Args>
TVector<T, dims>::TVector(T arg, const Args &...args)
{
	this->second = TPoint<T, dims>(arg, static_cast<T>(args)...);
}

/**
 * @brief Constructor for TVector taking two points.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @param a First point.
 * @param b Second point.
 */
template <typename T, uint32_t dims>
TVector<T, dims>::TVector(TPoint<T, dims> a, TPoint<T, dims> b)
{
	this->first = a;
	this->second = b;
}

/**
 * @brief Constructor for TVector taking two points.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @param a Second point.
 */
template <typename T, uint32_t dims>
TVector<T, dims>::TVector(TPoint<T, dims> b)
{
	this->first = TPoint<T, dims>(0);
	this->second = b;
}

/**
 * @brief Calculates the length of the vector.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @return Length of the vector.
 */
template <typename T, uint32_t dims>
T TVector<T, dims>::length()
{
	return TVector<T, dims>::length(*this);
}

/**
 * @brief Calculates the length of the vector.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @return Length of the vector.
 */
template <typename T, uint32_t dims>
T TVector<T, dims>::length(TVector<T, dims> v)
{
	return TPoint<T, dims>::distance(v.first, v.second);
}

/**
 * @brief Overloaded operator for shifting vector by another vector.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @param rhs The vector by which to shift.
 * @return New vector shifted by the given vector.
 */
template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator<<(const TVector<T, dims> &rhs)
{
	TPoint<T, dims> difference = this->first - rhs.first; // difference of two origins
	TVector<T, dims> diff = rhs;						  // difference of two origins
	return TVector<T, dims>(diff.first + difference, diff.second + difference);
}

/**
 * @brief Overloaded operator for shifting vector by a point.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @param rhs The point by which to shift.
 * @return New point shifted by the vector.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TVector<T, dims>::operator<<(const TPoint<T, dims> &rhs)
{
	TPoint<T, dims> difference = this->second - this->first; // difference of two origins
	TPoint<T, dims> orig = rhs;								 // difference of two origins
	return orig + difference;
}

/**
 * @brief Retrieves the origin of the vector.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @return Origin point of the vector.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TVector<T, dims>::get_origin()
{
	return this->first;
}

/**
 * @brief Retrieves the origin of the vector.
 *
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @return Origin point of the vector.
 */
template <typename T, uint32_t dims>
TPoint<T, dims> TVector<T, dims>::get_point() const
{
	return this->second;
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::normalise(TVector<T, dims> vec)
{
	return vec / TVector<T, dims>::length(vec);
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::normalise()
{
	return TVector<T, dims>::normalise(*this);
}

// Overloaded arithmetic operators

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator+(const TVector<T, dims> &rhs)
{
	TVector<T, dims> add = (*this << rhs);
	return (*this << TVector<T, dims>(this->first + add.first, this->second + add.second));
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator-(const TVector<T, dims> &rhs)
{
	TVector<T, dims> add = (*this << rhs);
	return (*this << TVector<T, dims>(this->first - add.first, this->second - add.second));
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator*(const T &rhs)
{
	return TVector<T, dims>(this->first, this->first + (this->second - this->first) * rhs);
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator-(const T &rhs)
{
	return this->extend(this->length() - rhs);
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator+(const T &rhs)
{
	return this->extend(this->length() + rhs);
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator/(const T &rhs)
{
	return TVector<T, dims>(this->first, this->first + (this->second - this->first) / rhs);
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator>>(TPoint<T, dims> &rhs)
{
	TPoint<T, dims> diff = rhs - this->first;
	return TVector<T, dims>(this->first + diff, this->second + diff);
}

/**
 * @brief Prints the vector in a human-readable format.
 *
 * @tparam T The type of the vector components.
 * @param vector The vector to print.
 * @return std::string A string representation of the vector.
 */
template <typename T, uint32_t dims>
std::string TVector<T, dims>::print(const TVector<T, dims> &vector)
{
	return TPoint<T, dims>::print(vector.second - vector.first);
}

/**
 * @brief Prints the vector in a format suitable for GeoGebra.
 *
 * @tparam T The type of the vector components.
 * @param vector The vector to print.
 * @return std::string A string representation of the vector for GeoGebra.
 */
template <typename T, uint32_t dims>
std::string TVector<T, dims>::print_geogebra(TVector<T, dims> vector)
{
	static_assert(dims <= 3, "TVector: dimensions bigger than 3D are not yet supported, or present in geogebra");
	std::stringstream ss;
	ss << "=Vector[" << TPoint<T, dims>::print(vector.first) << "," << TPoint<T, dims>::print(vector.second) << "]";
	return ss.str();
}

/**
 * @brief Prints the vector in a human-readable format.
 *
 * @tparam T The type of the vector components.
 * @param vector The vector to print.
 * @return std::string A string representation of the vector.
 */
template <typename T, uint32_t dims>
std::string TVector<T, dims>::print()
{
	return TVector<T, dims>::print(*this);
}

/**
 * @brief Calculates the dot product of two vectors.
 *
 * @tparam T The type of the vector components.
 * @param a The first vector.
 * @param b The second vector.
 * @return T The dot product of the two vectors.
 */
template <typename T, uint32_t dims>
T TVector<T, dims>::dot(TVector a, TVector b)
{
	return TPoint<T, dims>::dot(a.second - a.first, b.second - b.first);
}

/**
 * @brief Calculates the dot product of a vector and a point.
 *
 * @tparam T The type of the vector components.
 * @param a The vector.
 * @param b The point.
 * @return T The dot product of the vector and the point.
 */
template <typename T, uint32_t dims>
T TVector<T, dims>::dot(TVector<T, dims> a, TPoint<T, dims> b)
{
	return TPoint<T, dims>::dot(a.second - a.first, b);
}

/**
 * @brief Calculates the cross product of two vectors.
 *
 * @tparam T The type of the vector components.
 * @param v1 The first vector.
 * @param v2 The second vector.
 * @return TVector<T, dims> The cross product of the two vectors.
 */
template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::cross(TVector<T, dims> v1, TVector<T, dims> v2)
{
	static_assert(dims == 3, "TVector: TVector dimensions must be equal to 3, for that the cross product doesn't work for any other number of dimensions.\n");
	return TVector<T, dims>((v1.second.point().at(1) - v1.first.point().at(1)) * (v2.second.point().at(2) - v2.first.point().at(2)) - (v2.second.point().at(1) - v2.first.point().at(1)) * (v1.second.point().at(2) - v1.first.point().at(2)),
							(v1.second.point().at(2) - v1.first.point().at(2)) * (v2.second.point().at(0) - v2.first.point().at(0)) - (v2.second.point().at(2) - v2.first.point().at(2)) * (v1.second.point().at(0) - v1.first.point().at(0)),
							(v1.second.point().at(0) - v1.first.point().at(0)) * (v2.second.point().at(1) - v2.first.point().at(1)) - (v2.second.point().at(0) - v2.first.point().at(0)) * (v1.second.point().at(1) - v1.first.point().at(1)));
}

/**
 * @brief Computes the component of the vector along the specified dimension.
 * 
 * This method computes the component of the vector along the specified dimension.
 * 
 * @param index The dimension index.
 * @return T The component along the specified dimension.
 */
template <typename T, uint32_t dims>
T TVector<T, dims>::d(uint32_t index)
{
	return d(*this, index);
}

/**
 * @brief Computes the component of the vector along the specified dimension.
 * 
 * This method computes the component of the vector along the specified dimension.
 * 
 * @param v The vector.
 * @param index The dimension index.
 * @return T The component along the specified dimension.
 */
template <typename T, uint32_t dims>
T TVector<T, dims>::d(TVector<T, dims> v, uint32_t index)
{
	return v.get_point().point().at(index) - v.get_origin().point().at(index);
}


/*
template <typename T, uint32_t dims>
TPoint<T, dims> TVector<T, dims>::get_point(){
	return (((type >> 1) & 1)? second: TPoint<T, dims>::make_local(second.x, second.y, first));
	}


template <typename T, uint32_t dims>
T TVector<T, dims>::angle(){
	return (type >> 1)? first.get_gamma(second): second.y;
	}


template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::extend(TVector<T, dims> v, T length){
	return TVector<T, dims>(v.first, length, v.angle(), true); // to_coords = true
	}


template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::extend(T length){
	return extend(*this, length);
	}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::swap(TVector<T, dims> v){
	return TVector<T, dims>(v.get_point(), v.get_origin());
	}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::swap(){
	return TVector<T, dims>::swap(*this);
	}
*/
#endif /* TVECTOR_TPP */