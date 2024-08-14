#include "vec3.h"
#include "sphere.h"
#include <cmath>
#include <limits>

std::array<double,2> Sphere::IntersectRay(const Ray& ray) const
{
    vec3 z{ray.x() - center};
    vec3 y{ray.y()};
    double a{y.length_squared()};
    double b{dot(z, y)};
    double c{z.length_squared() - radius * radius};
    double discriminant{b * b - 4 * a * c};

    // If discriminant is negative, the polynomial is not solvable (i.e. ray does not intersect the sphere),
    // so we return infinity
    if(discriminant<0)
    {
        return std::array<double, 2>{std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()};
    }
    return std::array<double, 2>{(std::sqrt(discriminant) - b) / (2 * a),
                                 (-std::sqrt(discriminant) - b) / (2 * a)};
}
