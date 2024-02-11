/**
 * @brief Default constructor for TVector.
 * 
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 */
template <typename T, uint32_t dims>
TVector<T, dims>::TVector() {}

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
 * @brief Calculates the length of the vector.
 * 
 * @tparam T Type of the coordinates.
 * @tparam dims Number of dimensions.
 * @return Length of the vector.
 */
template <typename T, uint32_t dims>
T TVector<T, dims>::length()
{
    return TPoint<T, dims>::distance(this->first, this->second);
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
TVector<T, dims> TVector<T, dims>::operator << (const TVector<T, dims>& rhs){
    TPoint<T, dims> difference = this -> first - rhs.first; // difference of two origins
    TVector<T, dims> diff = rhs; // difference of two origins
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
TPoint<T, dims> TVector<T, dims>::operator << (const TPoint<T, dims>& rhs){
    TPoint<T, dims> difference = this -> second - this -> first; // difference of two origins
    TPoint<T, dims> orig = rhs; // difference of two origins
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
TPoint<T, dims> TVector<T, dims>::get_origin(){
    return this->first;
}

// Overloaded arithmetic operators

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator + (const TVector<T, dims>& rhs){
    TVector<T, dims> add = (*this << rhs);
    return (*this << TVector<T, dims>(this -> first + add.first, this -> second + add.second));
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator - (const TVector<T, dims>& rhs){
    TVector<T, dims> add = (*this << rhs);
    return (*this << TVector<T, dims>(this -> first - add.first, this -> second - add.second));
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator * (const T& rhs){
    return TVector<T, dims>(this -> first, this -> second * rhs - this -> first, true);
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator - (const T& rhs){
    return this -> extend(this -> length() - rhs);
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator + (const T& rhs){
    return this -> extend(this -> length() + rhs);
}

template <typename T, uint32_t dims>
TVector<T, dims> TVector<T, dims>::operator / (const T& rhs){
    return TVector<T, dims>(this -> first, this -> length()/rhs, this -> angle(), true);
}

