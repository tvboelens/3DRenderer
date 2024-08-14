#include <array>
#include <limits>
#include "raytracer.h"

vec3 RayTracer::CanvasToViewport(int x, int y, const Canvas& C)
{
    vec3 output(double(x) * viewport_width / double(C.getWidth()),
                double(y) * double(viewport_height) / double(C.getHeight()),
                viewport_distance);
    // output = camera_rotation * output + camera_position;
    return output;
}

// Method to determine color of closest sphere that intersects a ray. 
// If ray is given by x+ty, then take sphere such that t is in [t_min, t_max]
Color RayTracer::TraceRay(const Ray &ray, const Scene &scene, double t_min, double t_max)
{
    double closest_t{std::numeric_limits<double>::infinity()};
    std::array<double, 2> t;
    Color color{scene.getBackgroundColor()};
    for (std::vector<Sphere *>::const_iterator sphere = scene.getSpheres().begin();
         sphere < scene.getSpheres().end(); ++sphere)
    {
        t = (*sphere)->IntersectRay(ray);
        if (t[0] < closest_t && t[0] >= t_min && t[0] <= t_max)
        {
            closest_t = t[0];
            color = (*sphere)->getColor();
        }
        if (t[1] < closest_t && t[1] >= t_min && t[1] <= t_max)
        {
            closest_t = t[1];
            color = (*sphere)->getColor();
        }
    }
    return color;
}

void RayTracer::PaintCanvas(Canvas canvas, const Scene &scene)
{
    Ray ray{camera_position,{0.0,0.0,viewport_distance}};
    for (int y = -(canvas.getHeight() - canvas.getHeight() % 2) / 2;
         y < (canvas.getHeight() + canvas.getHeight() % 2) / 2; ++y)
    {
        for (int x = -(canvas.getWidth() - canvas.getWidth() % 2) / 2;
             x < (canvas.getWidth() + canvas.getWidth() % 2) / 2; ++y)
        {
            vec3 viewport_coordinate = CanvasToViewport(x, y, canvas);
            ray.Sety(viewport_coordinate);
            Color color = TraceRay(ray, scene, 1, std::numeric_limits<double>::infinity());
            canvas.PutPixel(x, y, color);
        }
    }
}
