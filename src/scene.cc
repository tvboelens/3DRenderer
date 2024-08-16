#include "scene.h"

void Scene::addSphere(const Sphere &S)
{
    Sphere *ptr = new Sphere{S};
    spheres.push_back(ptr);
}

void Scene::addLight(const Light& light)
{
    Light *ptr = new Light{light};
    lights.push_back(ptr);
}

const std::vector<Light *> &Scene::getLights() const
{
    return lights;
}

const std::vector<Sphere *> &Scene::getSpheres() const
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
    for (auto ptr: lights)
    {
        delete ptr;
    }
    lights.clear();
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
    for (auto ptr: lights)
    {
        delete ptr;
    }
    spheres.clear();
    lights.clear();
    spheres = S.spheres;
    lights = S.lights;
    S.spheres.clear();
    S.lights.clear();
    return *this;
}
