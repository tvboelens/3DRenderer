#ifndef RAYTRACER_H
#define RAYTRACER_H
#include "../vec3.h"
#include "../canvas.h"
#include "../scene.h"
#include "ray.h"
#include "../color.h"
#include <array>

class RayTracer
{
    private:
        vec3 camera_position;
        // Rotation matrix to change camera orientation, entries are rows of matrix. Matrix should be element of SO(3).
        std::array<vec3,3> camera_rotation;
        double viewport_distance;
        double viewport_width;
        double viewport_height;
    public:
        RayTracer(const vec3 &camera_position_ = {0.0, 0.0, 0.0},
                  std::array<vec3, 3> camera_rotation_ = {vec3{1,0,0},vec3{0,1,0},vec3{0,0,1}},
                  double viewport_distance_ = 1.0,
                  double viewport_width_ = 1.0,
                  double viewport_height_ = 1.0)
            : camera_position{camera_position_}
            , camera_rotation{camera_rotation_}
            , viewport_distance{viewport_distance_}
            , viewport_width{viewport_width_}
            , viewport_height{viewport_height_} {};
        vec3 CanvasToViewport(int x, int y, const Canvas &C);
        Color TraceRay(const Ray &ray, const Scene& scene, double t_min, double t_max);
        double ComputeLighting(const Scene& scene, const vec3 &point, const vec3 &normal);
        void PaintCanvas(Canvas &C, const Scene &S);
};

#endif
