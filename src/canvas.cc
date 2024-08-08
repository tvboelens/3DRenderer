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
    pixels[x][y] = color;
}
