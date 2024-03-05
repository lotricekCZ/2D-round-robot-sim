/*
 * TLine.cpp
 *
 * Copyright 2021 Jakub Ramašeuski <jakub@skaryna.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include "TLine.hpp"

#ifndef LINE_CPP
#define LINE_CPP

template <typename T, uint32_t dims>
TLine<T, dims>::TLine(TPoint<T, dims> a, TPoint<T, dims> b) : TVector<T, dims>(TVector<T, dims>(TPoint<T, dims>(), b - a).normalise()), origin(a)
{
}

template <typename T, uint32_t dims>
std::string TLine<T, dims>::print(const TLine<T, dims> &line)
{
    // std::string pointStr = TPoint<T, dims>::print(line::TPoint<T, dims>::this);
    // std::string vectorStr = TVector<T, dims>::print(line);
    return TPoint<T, dims>::print(line.origin) + " + t" + TVector<T, dims>::print(line);
}

template <typename T, uint32_t dims>
std::string TLine<T, dims>::print()
{
    return TLine<T, dims>::print(*this);
}

template <typename T, uint32_t dims>
T TLine<T, dims>::distance(TPoint<T, dims> point)
{
    return TLine<T, dims>::distance(*this, point);
}

template <typename T, uint32_t dims>
T TLine<T, dims>::distance(TLine<T, dims> line, TPoint<T, dims> point)
{
    try
    {
        std::cout << "moment" << TPoint<T, dims>::dot(line.origin, point) << " and " << TPoint<T, dims>::dot(line.get_point(), point) << std::endl;
        std::cout << "moment" << TPoint<T, dims>::dot(line.origin, point) << " and " << TPoint<T, dims>::dot(line.get_point(), point) << std::endl;
        return TPoint<T, dims>::distance(line.at(-TPoint<T, dims>::dot(line.origin, point) / TPoint<T, dims>::dot(line.get_point(), point)), point);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "moment" << std::endl;
        return std::numeric_limits<T>::infinity();
    }
}

template <typename T, uint32_t dims>
TPoint<T, dims> TLine<T, dims>::at(T a)
{
    try
    {
        std::cout << "moment" << a << std::endl;
        return TPoint<T, dims>(this->origin + this->get_point() * a);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "moment" << std::endl;
        return TPoint<T, dims>(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity());
    }
}

/*
TLine<T, dims>::TLine(T angle, T c){
    this -> b = 1;
    this -> a = -tan(angle);
    this -> c = c;
    }

TLine<T, dims>::TLine(){
    }

T TLine<T, dims>::get_y(T x){
    // ax + by + c = 0 -> by = -ax -c ->  y = (-ax -c) / b
    // all these this -> are here just for sure
    // returns infinity if no point for such x
    return  (b != 0)?(-(this -> a)*x - this -> c) / this -> b : std::numeric_limits<float>::infinity();
    }

T TLine<T, dims>::get_x(T y){
    // ax + by + c = 0 -> by = -ax -c ->  x = (-by -c) / a
    // all these this -> are here just for sure
    // returns infinity if no point for such y
    return (b != 0)? (-(this -> b)*y - this -> c) / this -> a : std::numeric_limits<float>::infinity();
    }

TLine TLine<T, dims>::operator /(T d){
    return (d != 0)?(TLine(this -> a / d, this -> b / d, this -> c / d)) : TLine(0, 0, 0);
    }

TLine TLine<T, dims>::make_parallel (TPoint<T, dims> c){
    return TLine(this -> a, this -> b, -(this -> a * c.x + this -> b * c.y));
    }

std::string TLine<T, dims>::print (TLine l){
    return 	std::string(std::to_string(l.a) + "x" +((l.b >= 0)?"+":"") +\
            std::to_string(l.b) + "y"+ ((l.c >= 0)?"+":"") + std::to_string(l.c) + " = 0");
    }

std::string TLine<T, dims>::print (){
    return print(*this);
    }

bool TLine<T, dims>::on_segment (TPoint<T, dims> on_seg, TPoint<T, dims> a_seg, TPoint<T, dims> b_seg){
    return std::abs((on_seg.get_distance(a_seg) + on_seg.get_distance(b_seg)) - a_seg.get_distance(b_seg)) <= 1e-4;
    }

TPoint<T, dims> TLine<T, dims>::intersection(TLine a, TLine b){
    if((a.b * b.a - b.b * a.a) == 0) return TPoint<T, dims>(std::numeric_limits<float>::infinity(), \
                                                        std::numeric_limits<float>::infinity());
    T x = (- a.b * b.c + b.b * a.c) / (a.b * b.a - b.b * a.a);
    // place for wtf, but it should work
    // just believe me, this should be ok
    return TPoint<T, dims>(x, (a.b != 0? a.get_y(x): b.get_y(x)));
    }

TPoint<T, dims> TLine<T, dims>::intersection(TLine a){
    return intersection(a, *this);
    }

TLine TLine<T, dims>::make_perpendicular(TPoint<T, dims> c){
    //~ std::cout << print() << std::endl;
    return TLine(((std::abs(this -> a) < 1e-3)?(-1):(1)) * this -> b,
                ((std::abs(this -> b) < 1e-3)?(1):(-1)) * this -> a,
                ((std::abs(this -> b) < 1e-3)?(-1):(1)) * this -> a * c.y - ((std::abs(this -> a) < 1e-3)?(-1):(1)) * this -> b * c.x);

    }

TLine TLine<T, dims>::make_perpendicular(){ /// for uses of making distance measurements among two parallel TLines
    return TLine(-b, a, c);
    }

TLine TLine<T, dims>::make_axis(TLine a, TLine b){
     /// parallel TLines, returns the same with average c
    if((a.b * b.a - b.b * a.a) == 0) return TLine(a.a, b.b, (a.c+b.c)/2);
    TPoint<T, dims> c = a.intersection(a, b);

    //~ std::cout << c.print() << std::endl;
    T angle = (a.get_angle() + b.get_angle()) / 2.0;
    return TLine(angle, c);
    }

//~ TLine TLine<T, dims>::make_perpendicular(TPoint<T, dims> c){
    //~ return TLine(this -> b, -this -> a, - (this -> a * c.x + this -> b * c.x));
    //~ }

T TLine<T, dims>::get_angle(){
    return atan2f(-a, b);
    }

T TLine<T, dims>::get_angle(TLine l){
    return get_angle() - l.get_angle();
    }

T TLine<T, dims>::get_angle(TLine l, TLine m){
    return m.get_angle() - l.get_angle();
    }

T TLine<T, dims>::get_distance(TLine l, TPoint<T, dims> c){
    return std::abs(l.a * c.x + l.b * c.y + l.c)/(sqrt(pow(l.a, 2) + pow(l.b, 2)));
    }

T TLine<T, dims>::get_distance(TPoint<T, dims> c){
    return get_distance(*this, c);
    }

T TLine<T, dims>::get_distance(TLine l){
    TLine n = make_perpendicular();
    return intersection(*this, n).get_distance(intersection(l, n));
    }

T TLine<T, dims>::get_distance(TLine l, TLine m){
    TLine n = l.make_perpendicular();
    //~ std::cout << intersection(m, n).print() << std::endl;
    //~ std::cout << intersection(l, n).print() << std::endl;
    //~ std::cout << n.print() << std::endl;
    //~ std::cout << TLine(intersection(l, n), intersection(m, n)).print() << std::endl;
    return intersection(m, n).get_distance(intersection(l, n));
    }
*/
#endif // LINE_CPP