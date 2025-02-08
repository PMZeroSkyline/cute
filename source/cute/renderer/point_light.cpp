#include "point_light.h"
#include "core/math/common.h"

PointLight::PointLight(const json& j) : PunctualLight(j)
{
    intensity = intensity / (683.f / PI / 4.f); // candela to watts
    if (j.contains("range"))
    {
        range = j["range"];
    }
}
void to_json(json& j, const PointLight& l)
{
    j["type"] = "point";
    if (l.name != "")
    {
        j["name"] = l.name;
    }
    if (l.intensity != 1.f)
    {
        j["intensity"] = l.intensity * (683.f / PI / 4.f);
    }
    if (l.color != vec3(1.f))
    {
        j["color"] = l.color;
    }
    if (l.range != 0.f)
    {
        j["range"] = l.range;
    }
}