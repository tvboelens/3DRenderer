#ifndef VEC3_H
#define VEC3_H


class vec3{
    protected:
        double coordinates[3];
    public:
        vec3() : coordinates{0.0, 0.0, 0.0} {};
        vec3(double x, double y, double z) : coordinates{x, y, z} {};
        
        double x() const { return coordinates[0]; };
        double y() const { return coordinates[1]; };
        double z() const { return coordinates[2]; };

        vec3 &operator+=(const vec3 &v);
        vec3 &operator-=(const vec3 &v);
        vec3 &operator*=(double a);
        vec3 &operator/=(double a);

        double length_squared();
        double length();
};

#endif
