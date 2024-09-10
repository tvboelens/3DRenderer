#ifndef RAY_H
#define RAY_H
#include "../vec3.h"


// Class for a ray (in 3-dimensional real space) of the form x+ty, where t is the variable and x and y are fixed vectors
class Ray
{
private:
    vec3 origin{0.0, 0.0, 0.0};
    vec3 direction;

public:
    Ray(const vec3& x, const vec3& y): origin{x}, direction{y} {};
    Ray(const vec3 &y): direction{y} {};

    const vec3& GetOrigin() const { return origin; };
    const vec3& GetDirection() const { return direction; };
    void SetOrigin(const vec3 &x) { origin = x; };
    void SetDirection(const vec3 &y) { direction = y; };
};

#endif
