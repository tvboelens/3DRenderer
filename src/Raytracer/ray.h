#ifndef RAY_H
#define RAY_H
#include "vec3.h"


// Class for a ray (in 3-dimensional real space) of the form x+ty, where t is the variable and x and y are fixed vectors
class Ray
{
private:
    vec3 x{0.0, 0.0, 0.0};
    vec3 y;

public:
    Ray(const vec3& x_, const vec3& y_): x{x_}, y{y_} {};
    Ray(const vec3 &y_): y{y_} {};
    const vec3 &x() const { return x; };
    const vec3 &y() const { return y; };
};


#endif RAY_H
