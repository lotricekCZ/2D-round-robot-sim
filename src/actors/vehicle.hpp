/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <cinttypes>
#include "../shapes/TCircle.hpp"
#include "../renderable/renderable.hpp"

class vehicle: public renderable, public Circle2D
{
private:
    // overall number of polygons circle will have
    const uint16_t poly_count = 32;
    const float radius = 0.1;
public:
    vehicle(/* args */);
    ~vehicle();
    void render() override;
    void place(float x = 0, float y = 0) override;
    void rotate(float a = 0) override;
    void move(float dx = 0, float dy = 0) override;
};


#endif