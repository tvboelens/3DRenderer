#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include <array>
#include "Raytracer/ray.h"
#include "color.h"

class Sphere
{
private:
    vec3 center;
    double radius;
    Color color;
    double specular_coefficient;
    double reflective;

public:
    //Sphere() {};
    Sphere(const vec3 &center_ = {0.0, 0.0, 0.0},
           double radius_ = 1.0, 
           const Color& color_ = {0.0, 0.0, 0.0},
            double specular_coefficient_ = -1.0,
            double reflective_ = 0.0)
        : center{center_}, radius{radius_}, color{color_}, specular_coefficient{specular_coefficient_}, reflective{reflective_} {};
    const vec3 &get_center() const { return center; };
    const double &get_radius() const { return radius; };
    const Color& getColor() const {return color;};
    std::array<double,2> IntersectRay(const Ray &ray) const;
    const double &get_specular() const { return specular_coefficient; };
    const double &get_reflective() const { return reflective; };
};

#endif
