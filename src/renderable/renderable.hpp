/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <typeinfo>
#include <vector>
#include <cinttypes>
#include "../shapes/TPoint.hpp"

#include <QOpenGLFunctions>


class renderable
{
private:
    static uint32_t ID_incrementor;
protected:
    union 
    {
        uint32_t ID: 24; // unique identifier
        uint8_t colors[3];
    };
    float _rotation = 0;
public:
    renderable(/* args */);
    ~renderable();
    uint32_t id(){return ID;};
    float rotation(){return _rotation;};
    void set_rotation(float rot){_rotation = rot;};
    virtual std::string info() = 0;
    virtual void render() = 0;
    virtual void move(float dx, float dy) = 0;
    virtual void place(float x = 0, float y = 0) = 0;
    virtual void rotate(float a = 0) = 0;
    virtual Point2D center() = 0;
};

#endif