#include <array>
#include <cmath>
#include <iostream>
#include <limits>
#include <optional>
#include "raytracer.h"
#include <thread>

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
Color RayTracer::TraceRay(const Ray &ray, const Scene &scene, double t_min, double t_max, int recursion_depth)
{

    std::pair<std::optional<Sphere>, double> closest = ComputeClosestIntersection(scene, ray, t_min, t_max);
    std::optional<Sphere> closest_sphere = closest.first;
    double closest_t = closest.second;
    // If the ray intersects a sphere, compute the closest point of intersection,
    // the normal at this point and use it to compute lighting and color
    if (!closest_sphere.has_value())
    {
        // If no sphere intersects the ray
        return scene.getBackgroundColor();
    }

    // compute local color
    vec3 D{ray.GetDirection()};
    vec3 P{ray.GetOrigin() + closest_t * D};
    vec3 normal{P - closest_sphere.value().get_center()};
    
    D *= -1.0;
    normal /= normal.length();
    Color local_color = closest_sphere.value().getColor() * ComputeLighting(scene, P, normal, D, closest_sphere.value().get_specular());

    // If we hit the recursion limit or the object is not reflective, we're done
    double r = closest_sphere.value().get_reflective();
    if (recursion_depth <= 0 or r <= 0){
            return local_color;
        }
    // compute reflected color
    Ray reflecting_ray {P, ReflectRay(D, normal)};
    Color reflected_color = TraceRay(reflecting_ray, scene, 0.001, std::numeric_limits<double>::infinity(), recursion_depth-1);

    return local_color * (1 - r) + reflected_color * r;
}

// Compute lighting at point P of a surface with normal vector normal at P
double RayTracer::ComputeLighting(const Scene& scene, const vec3 &P, const vec3 &normal, const vec3& V, const double& s)
{
    double t_max;
    if (scene.getLights().size() == 0)
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
            t_max = 1;
        }
        if ((*light)->type() == directional)
        {
            L = (*light)->direction().value();
            t_max = std::numeric_limits<double>::infinity();
        }

        // shadow check
        Ray light_ray{P, L};
        std::pair<std::optional<Sphere>, double> shadows = ComputeClosestIntersection(scene, light_ray, 0.001, t_max);
        if (shadows.first.has_value())
        {
            continue;
        }

        // diffuse reflection
        double N_dot_L = dot(normal, L);
        if(N_dot_L>0)
        {
            i += (*light)->intensity() * N_dot_L / (normal.length() * L.length());
        }    
        
        // specular reflection
        if (s!=-1){
            vec3 R;
            R = 2 * normal * dot(normal, L) - L;
            double r_dot_v = dot(R, V);
            if (r_dot_v>0){
                i += (*light)->intensity() * std::pow(r_dot_v / (R.length() * V.length()), s);
            }
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
            ray.SetDirection(viewport_coordinate);
            Color color = TraceRay(ray, scene, viewport_distance, std::numeric_limits<double>::infinity(),3);
            canvas.PutPixel(x, y, color);
        }
    }
    std::clog << "\rDone painting.                 " << std::endl;
}

void RayTracer::PaintCanvas_parallel(Canvas &canvas, const Scene &scene)
{
    const unsigned int hardware_threads = std::thread::hardware_concurrency();
    const unsigned int num_threads = (hardware_threads != 0 ? hardware_threads : 2);
    std::clog << "Starting painting using " << num_threads << " threads..." << std::endl;
    std::vector<std::thread> threads(num_threads - 1);
    std::vector<Ray> rays(num_threads, {camera_position, {0.0,0.0, viewport_distance}});
    int line_block_length = canvas.getHeight()/num_threads;
    int y_start = -(canvas.getHeight() - canvas.getHeight() % 2) / 2;
    int y_end = y_start;
    for (unsigned int i = 0; i < num_threads-1;++i)
    {
        y_end += line_block_length;

        threads[i] = std::thread(&RayTracer::PaintCanvasLines, this, std::ref(canvas), std::ref(scene), std::ref(rays[i]),
                                 y_start, y_end);
        y_start = y_end;
    }
    PaintCanvasLines(canvas, scene, rays.back(), y_end, (canvas.getHeight() + canvas.getHeight() % 2) / 2);
    for (auto &entry : threads)
        entry.join();
    std::clog
        << "\rDone painting.                 " << std::endl;
}

void RayTracer::PaintCanvasLines(Canvas &canvas, const Scene &scene, Ray& ray, int y_start, int y_end)
{
    for (int y = y_start;y < y_end; ++y)
    {
        for (int x = -(canvas.getWidth() - canvas.getWidth() % 2) / 2;
             x < (canvas.getWidth() + canvas.getWidth() % 2) / 2; ++x)
        {
            vec3 viewport_coordinate = CanvasToViewport(x, y, canvas);
            ray.SetDirection(viewport_coordinate);
            Color color = TraceRay(ray, scene, viewport_distance, std::numeric_limits<double>::infinity(),3);
            canvas.PutPixel(x, y, color);
        }
    }
}

std::pair<std::optional<Sphere>, double> RayTracer::ComputeClosestIntersection(const Scene& scene, const Ray& ray, double t_min, double t_max)
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
    return std::pair<std::optional<Sphere>, double>{closest_sphere, closest_t};
}

vec3 RayTracer::ReflectRay(const vec3 &R, const vec3 &N)
{
    return 2 * N * dot(N, R) - R;
}
