#include "../vec3.h"
#include "raytracer.h"
#include "../scene.h"
#include "../sphere.h"
#include "../color.h"
#include "light.h"

int main()
{

    Scene scene{{255.0,255.0,255.0}};
    Canvas canvas{256, 256};

    RayTracer raytracer;
    scene.addSphere(Sphere{{0.0, -1.0, 3.0}, 1.0, {255.0, 0.0, 0.0}}); // Red
    scene.addSphere(Sphere{{2.0, 0.0, 4.0}, 1.0, {0.0, 0.0, 255.0}}); // Blue
    scene.addSphere(Sphere{{-2.0, 0.0, 4.0}, 1.0, {0.0, 255.0, 0.0}}); // Green
    scene.addSphere(Sphere({0.0,-5001.0,0.0}, 5000.0, {255.0,255.0,0.0}));//Yellow

    scene.addLight(Light(ambient, 0.2));
    scene.addLight(Light(point, 0.6, {2, 1, 0}));
    scene.addLight(Light(directional, 0.2, {1, 4, 4}));

    raytracer.PaintCanvas(canvas, scene);
    canvas.render();

    return 0;
}
