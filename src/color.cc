#include "color.h"

double clamp(double x)
{
    if (x < 0)
    {
        return 0.0;
    }
    if (x > 255)
    {
        return 255.0;
    }
    return x;
}

Color& Color::operator+=(const Color &color)
{
    coordinates[0] = clamp(coordinates[0] + color.r());
    coordinates[1] = clamp(coordinates[1] + color.g());
    coordinates[2] = clamp(coordinates[2] + color.b());
    return *this;
}

Color& Color::operator-=(const Color &color)
{
    coordinates[0] = clamp(coordinates[0] - color.r());
    coordinates[1] = clamp(coordinates[1] - color.g());
    coordinates[2] = clamp(coordinates[2] - color.b());
    return *this;
}

Color& Color::operator*=(double a)
{
    coordinates[0] *= a;
    coordinates[1] *= a;
    coordinates[2] *= a;
    return *this;
}

Color& Color::operator/=(double a)
{
    coordinates[0] /= a;
    coordinates[1] /= a;
    coordinates[2] /= a;
    return *this;
}
