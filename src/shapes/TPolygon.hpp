/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#include <cinttypes>
#include <memory>
#include <optional>
#include <utility>
#include "TPoint.hpp"

#ifndef TPOLYGON_HPP
#define TPOLYGON_HPP

template <typename T, uint32_t dims>
class TPolygon
{
private:
	TPoints<T, dims> vertices;
	std::optional<std::vector<std::pair<
		std::shared_ptr<TPoint<T, dims>>, 
		std::shared_ptr<TPoint<T, dims>>
		>>> edges;
public:
	enum vertex_mode{
		auto_ltr, // left leads to the one on the right until it wraps to the leftmost again
		auto_rtl, // right leads to the one on the left until it wraps to the rightmost again (don't ask me why this is an option)
		user_defined
	};
	TPolygon(/* args */);
	TPolygon(TPoints<T, dims> &);
	~TPolygon();
	 
};

#endif