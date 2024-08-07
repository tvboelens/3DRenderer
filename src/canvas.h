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
        Canvas(int width, int height)
        : m_width{width}
        , m_height{height}
        {
            pixels.resize(width);
            for (std::vector<std::vector<Pixel>>::iterator it = pixels.begin();
                 it < pixels.end();++it)
                 {
                     it->resize(height);
                 }
        }
        
        void PutPixel(int x, int y, const Color& color)
        {
            /* We assume that x and y are given from a coordinate system with 0 in the center,
            whereas for the canvas we assume that 0 is in the top left corner, x increases to the right
            and y increases when going down. Thus, we need to transform x and y. We also allow width 
            and height to be odd, which needs to be accounted for in the transformation.
            */
            x += (m_width - (m_width % 2)) / 2;
            y = (m_height - (m_height % 2)) / 2 - y;
            pixels[x][y] = color;
        }
};

#endif
