#include "vec3.h"
#include "sphere.h"
#include <cmath>
#include <limits>

double Sphere::IntersectRay(const Ray& ray)
{
    vec3 z{ray.x() - center};
    vec3 y{ray.y()};
    double a{y.length_squared()};
    double b{dot(z, y)};
    double c{z.length_squared() - radius * radius};
    double discriminant{b * b - 4 * a * c};
    // If discriminant is negative, the polynomial is not solvable (i.e. ray does not intersect the sphere),
    // so we return -infinity
    if(discriminant<0)
    {
        return -std::numeric_limits<double>::infinity();
    }
    double s{(std::sqrt(discriminant) - b) / (2 * a)};
    double t{(-std::sqrt(discriminant) - b) / (2 * a)};
    // If the solutions are both negative, then the ray does not intersect sphere, so again return -infinity
    if (s < 0 && t < 0)
    {
        return -std::numeric_limits<double>::infinity();
    }
    // Return smallest nonnegative solution
    // If t < 0 then s>=0
    if (t < 0)
    {
        return s;
    }
    if (s <= t && s >= 0)
    {
        return s;
    }
    // If all previous conditions were false, then 0<=t and either t<=s or s<0
    return t;
}
