#ifndef RAY_H
#define RAY_H
#include "vec3.h"


// Class for a ray (in 3-dimensional real space) of the form x+ty, where t is the variable and x and y are fixed vectors
class Ray
{
private:
    vec3 x_{0.0, 0.0, 0.0};
    vec3 y_;

public:
    Ray(const vec3& x, const vec3& y): x_{x}, y_{y} {};
    Ray(const vec3 &y): y_{y} {};

    const vec3& x() const { return x_; };
    const vec3& y() const { return y_; };
    void Setx(const vec3 &x) { x_ = x; };
    void Sety(const vec3 &y) { y_ = y; };
};

#endif RAY_H
