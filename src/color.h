#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <stdexcept>

double clamp(double x)
{
    if (x<0) {
        return 0.0;
    }
    if(x>255) {
        return 255.0;
    }
    return x;
}

class Color: public vec3
{
public:
    Color() { vec3(); };
    Color(double r, double g, double b) 
    {
        vec3(clamp(r), clamp(g), clamp(b));
    }
    Color(vec3 v)
    {
        vec3(clamp(v.x()), clamp(v.y()), clamp(v.z()));
    }
    // Access functions
    double r() const { return coordinates[0]; }
    double g() const { return coordinates[1]; }
    double b() const { return coordinates[2]; }

    // Arithmetic functions
    Color& operator+=(const Color& color)
    {
        coordinates[0] = clamp(coordinates[0] + color.r());
        coordinates[1] = clamp(coordinates[1] + color.g());
        coordinates[2] = clamp(coordinates[2] + color.b());
        return *this;
    }

    Color& operator-=(const Color& color)
    {
        coordinates[0] = clamp(coordinates[0] - color.r());
        coordinates[1] = clamp(coordinates[1] - color.g());
        coordinates[2] = clamp(coordinates[2] - color.b());
        return *this;
    }

    Color& operator*=(double a)
    {
        coordinates[0] *= a;
        coordinates[1] *= a;
        coordinates[2] *= a;
        return *this;
    }

    Color& operator/=(double a)
    {
        coordinates[0] /= a;
        coordinates[1] /= a;
        coordinates[2] /= a;
        return *this;
    }
};

using Pixel = Color;

#endif
