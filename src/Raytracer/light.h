#ifndef LIGHT_H
#define LIGHT_H
#include <exception>
#include <optional>
#include "../vec3.h"

enum LightType
{
    ambient,
    point,
    directional,
};

class Light
{
private:
    LightType type_;
    double intensity_;
    std::optional<vec3> position_;
    std::optional<vec3> direction_;
public:
    Light(LightType type, double intensity, const vec3& v): type_{type}, intensity_{intensity}
    {
        if(type==point){position_ = v;}
        if(type==directional){direction_ = v;}
        if(type==ambient){throw std::invalid_argument("Ambient type only takes intensity as input!");}
    } ;
    Light(LightType type, double intensity): type_{type}, intensity_{intensity}
    {
        if(type==point){throw std::invalid_argument("Missing position!");;}
        if(type==directional){throw std::invalid_argument("Missing direction!");}
    } ;
    const LightType &type() const { return type_; };
    const std::optional<vec3>& position() const { return position_; }
    const std::optional<vec3>& direction() const { return direction_; }
    const double &intensity() const { return intensity_; }
};





#endif
