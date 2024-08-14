#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "Raytracer/ray.h"
#include "color.h"

class Sphere
{
private:
    vec3 center;
    double radius;
    Color color;
public:
    //Sphere() {};
    Sphere(const vec3 &center_ = {0.0, 0.0, 0.0},
           double radius_ = {1.0}, 
           const Color& color_ = {0.0, 0.0, 0.0})
        : center{center_}, radius{radius_}, color{color_} {};
    Sphere(const Sphere &S) : center{S.center}, radius{S.radius} {};
    const vec3 &get_center() const { return center; };
    const double &get_radius() const { return radius; };
    double IntersectRay(const Ray &ray);
};


#endif
