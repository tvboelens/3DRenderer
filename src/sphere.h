#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "Raytracer/ray.h"

class Sphere
{
private:
    vec3 center{0.0, 0.0, 0.0};
    double radius{1.0};
public:
    Sphere() {};
    Sphere(const vec3 &center_) : center{center_} {};
    Sphere(double radius_): radius{radius_} {};
    Sphere(const vec3 &center_, double radius_) : center{center_}, radius{radius_} {};
    Sphere(const Sphere& S) : center{S.center}, radius{S.radius} {};
    const vec3 &get_center() const { return center; };
    const double &get_radius() const { return radius; };
    double IntersectRay(const Ray &ray);
};


#endif
