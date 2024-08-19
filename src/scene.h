#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "sphere.h"
#include "color.h"
#include "Raytracer/light.h"

class Scene
{
    std::vector<Sphere*> spheres;
    std::vector<Light *> lights;
    Color background_color;

public:
    void addSphere(const Sphere &S);
    void addLight(const Light &light);
    const std::vector<Sphere *> &getSpheres() const;
    const std::vector<Light *>& getLights() const;
    const Color &getBackgroundColor() const { return background_color; };
    Scene(const Color &C = {0.0, 0.0, 0.0}) : background_color{C} {};
    // Copy constructor
    Scene(const Scene &S) 
        : spheres(S.spheres.size())
        , lights(S.lights.size())
        , background_color{S.background_color}
    {
    // Deep copy
    for (size_t i = 0; i < S.spheres.size(); ++i)
        {
            spheres[i] = new Sphere{*S.spheres[i]};
        }
        for (size_t i = 0; i < S.lights.size();++i)
        {
            lights[i] = new Light{*S.lights[i]};
        }
    };
    // Copy assignment operator
    Scene& operator=(const Scene &S);
    // Move constructor
    Scene(Scene &&S) noexcept
        : spheres{S.spheres}, lights{S.lights} ,background_color{S.background_color}
    {
        S.spheres.clear();
        S.lights.clear();
    }
    // Move assignment operator
    Scene &operator=(Scene &&S) noexcept;
    ~Scene();
};

#endif
