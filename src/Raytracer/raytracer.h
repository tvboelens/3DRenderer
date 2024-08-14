#ifndef RAYTRACER_H
#define RAYTRACER_H
#include "../vec3.h"
#include "../canvas.h"
#include "../scene.h"
#include "ray.h"
#include "../color.h"

class RayTracer
{
    vec3 camera_position;
    // camera_rotation; Still have to figure out which type to use here
    double viewport_distance;
    double viewport_width;
    double viewport_height;

    vec3 CanvasToViewport(int x, int y, const Canvas& C);
    Color TraceRay(const Ray &ray, const Scene& scene, double t_min, double t_max);
    void PaintCanvas(Canvas C, const Scene &S);
};

#endif
