#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include "vec3.h"
#include "color.h"

class Canvas{
    int m_width;
    int m_height;
    std::vector<std::vector<Pixel>> pixels;
    public:
        Canvas(int width, int height);

        void PutPixel(int x, int y, const Color &color);
};

#endif
