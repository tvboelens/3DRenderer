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

double vec3::length_squared() const
{
    return coordinates[0] * coordinates[0] + coordinates[1] * coordinates[1] + coordinates[2] * coordinates[2];
}

double vec3::length() const
{
    return std::sqrt(length_squared());
}

double vec3::operator*(const vec3& w) const
{
    double output{x() * w.x()};
    output += y() * w.y();
    output += z() * w.z();
    return output;
}

vec3 operator+(const vec3 &x, const vec3 &y)
{
    vec3 output{x};
    output += y;
    return output;
}

vec3 operator-(const vec3 &x, const vec3 &y)
{
    vec3 output{x};
    output += -1.0 * y;
    return output;
}
vec3 operator*(const vec3 &x, double a)
{
    vec3 output{x};
    output *= a;
    return output;
}
vec3 operator*(double a, const vec3 &x)
{
    vec3 output{x};
    output *= a;
    return output;
}

double dot(const vec3 &v, const vec3 &w)
{
    return v * w;
}
