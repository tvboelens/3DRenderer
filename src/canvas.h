#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <string>
#include "vec3.h"
#include "color.h"

class Canvas{
    int m_width;
    int m_height;
    std::vector<std::vector<Pixel>> pixels;
    public:
        Canvas(int width, int height)
            : m_width{width}
            , m_height{height}
            , pixels(width, std::vector<Pixel>(height)) 
            {};

        void PutPixel(int x, int y, const Color &color);
        void render(std::string fname = "image.ppm");
};

#endif
