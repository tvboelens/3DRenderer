#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "sphere.h"

class Scene
{
    std::vector<Sphere*> spheres;
    public:
        void addSphere(const Sphere &S);
        const std::vector<Sphere *>::iterator getSpheres();
        // Copy constructor
        Scene(const Scene &S) : spheres(S.spheres.size()) 
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
            : spheres{S.spheres}
        {
            S.spheres.clear();
        }
        // Move assignment operator
        Scene &operator=(Scene &&S) noexcept;
        ~Scene();
};

#endif
