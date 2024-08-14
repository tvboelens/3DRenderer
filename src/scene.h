#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "sphere.h"
#include "color.h"

class Scene
{
    std::vector<Sphere*> spheres;
    Color background_color;
    public:
        void addSphere(const Sphere &S);
        std::vector<Sphere *>::const_iterator getSpheres() const;
        const Color& getBackgroundColor() const { return background_color; };
        Scene(const Color& C = {0.0, 0.0, 0.0}) : background_color{C} {};
        // Copy constructor
        Scene(const Scene &S) : spheres(S.spheres.size()), background_color{S.background_color}
            {
                // Deep copy
                for (size_t i = 0; i < S.spheres.size();++i)
                {
                    spheres[i] = new Sphere;
                    *spheres[i] = *S.spheres[i];
                }
            };
        // Move constructor
        Scene(Scene &&S) noexcept
            : spheres{S.spheres}, background_color{S.background_color}
        {
            S.spheres.clear();
        }
        // Move assignment operator
        Scene &operator=(Scene &&S) noexcept;
        ~Scene();
};

#endif
