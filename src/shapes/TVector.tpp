template <typename T, uint32_t dims>
TVector<T, dims>::TVector() {}

template <typename T, uint32_t dims>
TVector<T, dims>::TVector(TPoint<T, dims> a, TPoint<T, dims> b)
{
    this->first = a;
    this->second = b;
}

template <typename T, uint32_t dims>
T TVector<T, dims>::length()
{
    return TPoint<T, dims>::distance(this->first, this->second);
}