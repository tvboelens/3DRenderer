#ifndef RAY_H
#define RAY_H
#include "vec3.h"


// Class for a ray (in 3-dimensional real space) of the form x+ty, where t is the variable and x and y are fixed vectors
class Ray
{
private:
    vec3 origin{0.0, 0.0, 0.0};
    vec3 d;

public:
    Ray(const vec3& x_, const vec3& y_): origin{x_}, d{y_} {};
    Ray(const vec3 &y_): d{y_} {};
    const vec3& x() const { return origin; };
    const vec3& y() const { return d; };
};


#endif RAY_H
