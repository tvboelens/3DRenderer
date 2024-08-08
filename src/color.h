#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

double clamp(double x);

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
    Color &operator+=(const Color &color);
    Color &operator-=(const Color &color);
    Color &operator*=(double a);
    Color &operator/=(double a);
};

using Pixel = Color;

#endif
