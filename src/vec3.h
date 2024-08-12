#ifndef VEC3_H
#define VEC3_H


class vec3{
    protected:
        double coordinates[3];
    public:
        vec3() : coordinates{0.0, 0.0, 0.0} {};
        vec3(double x, double y, double z) : coordinates{x, y, z} {};
        vec3(const vec3 &v) : coordinates{v.x(), v.y(), v.z()} {};

        double x() const { return coordinates[0]; };
        double y() const { return coordinates[1]; };
        double z() const { return coordinates[2]; };

        vec3 &operator+=(const vec3 &v);
        vec3 &operator-=(const vec3 &v);
        vec3 &operator*=(double a);
        vec3 &operator/=(double a);
        double operator*(const vec3 &w) const;

        double length_squared();
        double length();
};

double dot(const vec3 &v, const vec3 &w);
vec3 operator+(const vec3 &x, const vec3 &y);
vec3 operator-(const vec3 &x, const vec3 &y);
vec3 operator*(const vec3 &x, double a);
vec3 operator*(double a, const vec3 &x);

#endif
