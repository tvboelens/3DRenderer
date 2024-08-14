#include "scene.h"

void Scene::addSphere(const Sphere &S)
{
    Sphere *ptr = new Sphere{S};
    spheres.push_back(ptr);
}

const std::vector<Sphere *>& Scene::getSpheres() const
{
    return spheres;
}

Scene::~Scene()
{
    for (auto ptr : spheres)
         {
             delete ptr;
         }
    spheres.clear();
}

Scene& Scene::operator=(Scene &&S) noexcept
{
    if(&S==this)
    {
        return *this;
    }
    for (auto ptr : spheres)
    {
        delete ptr;
    }
    spheres.clear();
    spheres = S.spheres;
    S.spheres.clear();
    return *this;
}
