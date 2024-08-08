#include "vec3.h"
#include <cmath>

vec3& vec3::operator+=(const vec3 &v)
{
    coordinates[0] += v.x();
    coordinates[1] += v.y();
    coordinates[2] += v.z();
    return *this;
}

vec3& vec3::operator-=(const vec3 &v)
{
    coordinates[0] -= v.x();
    coordinates[1] -= v.y();
    coordinates[2] -= v.z();
    return *this;
}

vec3& vec3::operator*=(double a)
{
    coordinates[0] *= a;
    coordinates[1] *= a;
    coordinates[2] *= a;
    return *this;
}

vec3& vec3::operator/=(double a)
{
    coordinates[0] /= a;
    coordinates[1] /= a;
    coordinates[2] /= a;
    return *this;
}

double vec3::length_squared()
{
    return coordinates[0] * coordinates[0] + coordinates[1] * coordinates[1] + coordinates[2] * coordinates[2];
}

double vec3::length()
{
    return std::sqrt(length_squared());
}
