#include <fstream>
#include <iostream>
#include "canvas.h"

void Canvas::PutPixel(int x, int y, const Color& color)
{
    /* We assume that x and y are given from a coordinate system with 0 in the center,
    whereas for the canvas we assume that 0 is in the top left corner, x increases to the right
    and y increases when going down. Thus, we need to transform x and y. We also allow width
    and height to be odd, which needs to be accounted for in the transformation.
    */
    x += (m_width - (m_width % 2)) / 2;
    y = (m_height - (m_height % 2)) / 2 - y;
    // Don't do anything if (x,y) lies outside of the canvas
    if(x<0||x>=m_width) 
    {
        return;
    }
    if(y<0||y>=m_height)
    {
        return;
    }
    pixels[x][y] = color;
}

// Render to ppm format
void Canvas::render(std::string fname="image.ppm")
{
    std::ofstream img_file{fname};
    // If we couldn't open output file stream for writing output an error
    if(!img_file)
    {
        std::cerr << "ERROR: " << fname << " could not be opened for writing!";
        return;
    }

    img_file << "P3\n"
             << m_width << ' ' << m_height << "\n255\n";
    for (int j = 0; j < m_height; ++j)
    {
        for (int i = 0; i < m_width; ++i)
        {
            img_file << pixels[i][j].r() << ' ' << pixels[i][j].g() << ' ' << pixels[i][j].g() << "\n";
        }
    }
}
