/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */
#include "vehicle.hpp"
#include <cassert>
#include <QOpenGLFunctions>

vehicle::vehicle(/* args */) : Circle2D(0.1)
{
}

vehicle::~vehicle()
{
}

void vehicle::render()
{
    assert((vehicle::poly_count % 8) == 0);
    auto point_center = this->center();
    auto center = point_center.point();
    std::vector<std::array<float, 2>> vtx(vehicle::poly_count);

    glColor3f(colors[0] / 255.0f, colors[1] / 255.0f, colors[2] / 255.0f);
    glBegin(GL_POLYGON);
    for (size_t i = 0; i < vehicle::poly_count; i++)
    {
        auto o = (this->at((float)(i) / ((float)vehicle::poly_count)) - point_center).point();
        glVertex2f(center[0] + o[0], center[1] + o[1]); // not the most optimal approach, I could've done that with just an 1/8 of a points
    }
    glEnd();
}

void vehicle::move(float dx, float dy)
{
    this->reposition(dx, dy);
}

void vehicle::place(float x, float y) {
    Circle2D::place(x, y);
}

void vehicle::rotate(float a) {
    rotation += a;
}