#include "../vec3.h"
#include "raytracer.h"
#include "../scene.h"
#include "../sphere.h"
#include "../color.h"

int main()
{

    Scene scene{{255.0,255.0,255.0}};
    Canvas canvas{256, 256};

    RayTracer raytracer;
    scene.addSphere(Sphere{{0.0, -1.0, 3.0}, 1.0, {255.0, 0.0, 0.0}}); // Red
    scene.addSphere(Sphere{{2.0, 0.0, 4.0}, 1.0, {0.0, 0.0, 255.0}}); // Blue
    scene.addSphere(Sphere{{-2.0, 0.0, 4.0}, 1.0, {0.0, 255.0, 0.0}}); // Green

    raytracer.PaintCanvas(canvas, scene);
    canvas.render();

    return 0;
}
