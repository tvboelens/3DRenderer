#include <array>
#include <iostream>
#include <limits>
#include <optional>
#include "raytracer.h"

vec3 RayTracer::CanvasToViewport(int x, int y, const Canvas& C)
{
    vec3 output(double(x) * viewport_width / double(C.getWidth()),
                double(y) * double(viewport_height) / double(C.getHeight()),
                viewport_distance);
    // ad-hoc method of matrix multiplication
    double a{dot(camera_rotation[0], output)};
    double b{dot(camera_rotation[1], output)};
    double c{dot(camera_rotation[2], output)};
    output = {a, b, c};
    output += camera_position;
    return output;
}

// Method to determine color of closest sphere that intersects a ray. 
// If ray is given by x+ty, then take sphere such that t is in [t_min, t_max]
Color RayTracer::TraceRay(const Ray &ray, const Scene &scene, double t_min, double t_max)
{
    double closest_t{std::numeric_limits<double>::infinity()};
    std::optional<Sphere> closest_sphere;
    std::array<double, 2> t;
    for (std::vector<Sphere *>::const_iterator sphere = scene.getSpheres().begin();
         sphere < scene.getSpheres().end(); ++sphere)
    {
        t = (*sphere)->IntersectRay(ray);
        if (t[0] < closest_t && t[0] >= t_min && t[0] <= t_max)
        {
            closest_t = t[0];
            closest_sphere.emplace(Sphere{**sphere});
        }
        if (t[1] < closest_t && t[1] >= t_min && t[1] <= t_max)
        {
            closest_t = t[1];
            closest_sphere.emplace(Sphere{**sphere});
        }
    }
    // If the ray intersects a sphere, compute the closest point of intersection,
    // the normal at this point and use it to compute lighting and color
    if(closest_sphere.has_value())
    {
        vec3 P{ray.x() + closest_t * ray.y()};
        vec3 normal{P - closest_sphere.value().get_center()};
        normal /= normal.length();
        return closest_sphere.value().getColor() * ComputeLighting(scene, P, normal);
    }
    // If no sphere intersects the ray
    return scene.getBackgroundColor();
}

// Compute lighting at point P of a surface with normal vector normal at P
double RayTracer::ComputeLighting(const Scene& scene, const vec3 &P, const vec3 &normal)
{
    if (scene.getLights().size()==0) 
    {
        return 1.0;
    }
    double i{0};
    for(std::vector<Light *>::const_iterator light = scene.getLights().begin();
        light < scene.getLights().end();++light)
    {
        vec3 L{0, 0, 0};
        if ((*light)->type() == ambient)
        {
            i += (*light)->intensity();
        }
        if ((*light)->type()==point)
        {
            L = (*light)->position().value() - P;
        }
        if ((*light)->type() == directional)
        {
            L = (*light)->direction().value();
        }
        double N_dot_L = dot(normal, L);
        if(N_dot_L>0)
        {
            i += (*light)->intensity() * N_dot_L / (normal.length() * L.length());
        }     
    }
    return i;
}

void RayTracer::PaintCanvas(Canvas& canvas, const Scene &scene)
{
    std::clog << "Starting painting...";
    Ray ray{camera_position, {0.0, 0.0, viewport_distance}};
    for (int y = -(canvas.getHeight() - canvas.getHeight() % 2) / 2;
         y < (canvas.getHeight() + canvas.getHeight() % 2) / 2; ++y)
    {
        std::clog << "\rPainting, lines remaining: "
                  << ((canvas.getHeight() + canvas.getHeight() % 2) / 2 - y)
                  << ' '
                  << std::flush;
        for (int x = -(canvas.getWidth() - canvas.getWidth() % 2) / 2;
             x < (canvas.getWidth() + canvas.getWidth() % 2) / 2; ++x)
        {
            vec3 viewport_coordinate = CanvasToViewport(x, y, canvas);
            ray.Sety(viewport_coordinate);
            Color color = TraceRay(ray, scene, viewport_distance, std::numeric_limits<double>::infinity());
            canvas.PutPixel(x, y, color);
        }
    }
    std::clog << "\rDone painting.                 " << std::endl;
}
