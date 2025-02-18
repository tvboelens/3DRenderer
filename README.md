# 3DRenderer

Ongoing project to build 3D renderers in C++(17), one using raytracing and the other using rasterization, following [this tutorial](https://www.gabrielgambetta.com/computer-graphics-from-scratch/).

# Raytracer
Renders a scene with spheres and lighting.
## Prerequisites
You only need the C++ standard library and the thread library. For building use Cmake.

# Usage
All the source code is in the `src/` folder. The scene is constructed in `src/Raytracer/main.cc` via the Scene class. The Scene class has methods to add spheres and lights to it at various locations. The image is generated from an instance of the Canvas class via the render method. Before rendering, use the Raytracer class to paint the Canvas object.

If you want to create a customized image, modify the code in `src/Raytracer/main.cc`.

# Building
After cloning this repository and customizing `src/Raytracer/main.cc`, build it using Cmake. Run the following commands (for example in Bash) to create a build directory and compile:
```
mkdir build && cd build
cmake ..
make
```
Then run 
```
./Raytracer
```
to run the program. Output is generated as `image.ppm`.

# Example output:
Here is an example of a rendered scene:
![](./image.ppm "example image")
