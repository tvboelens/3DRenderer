#ifndef VEC3_H
#define VEC3_H

#include <cmath>

class vec3{
    protected:
        double coordinates[3];
    public:
        vec3() : coordinates{0.0, 0.0, 0.0} {};
        vec3(double x, double y, double z) : coordinates{x, y, z} {};
        
        double x() const { return coordinates[0]; };
        double y() const { return coordinates[1]; };
        double z() const { return coordinates[2]; };

        vec3& operator+=(const vec3& v)
        {
            coordinates[0] += v.x();
            coordinates[1] += v.y();
            coordinates[2] += v.z();
            return *this;
        }

        vec3& operator-=(const vec3 &v)
        {
            coordinates[0] -= v.x();
            coordinates[1] -= v.y();
            coordinates[2] -= v.z();
            return *this;
        }

        vec3& operator*=(double a)
        {
            coordinates[0] *= a;
            coordinates[1] *= a;
            coordinates[2] *= a;
            return *this;
        }

        vec3& operator/=(double a)
        {
            coordinates[0] /= a;
            coordinates[1] /= a;
            coordinates[2] /= a;
            return *this;
        }

        double length_squared()
        {
            return coordinates[0] * coordinates[0] + coordinates[1] * coordinates[1] + coordinates[2] * coordinates[2];
        }

        double length()
        {
            return std::sqrt(length_squared());
        }
};


#endif
