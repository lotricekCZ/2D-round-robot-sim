/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <vector>
#include <cinttypes>
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
    float rotation = 0;
public:
    renderable(/* args */);
    ~renderable();
    virtual void render() = 0;
    virtual void move(float dx, float dy) = 0;
    virtual void place(float x = 0, float y = 0) = 0;
    virtual void rotate(float a = 0) = 0;
};

#endif