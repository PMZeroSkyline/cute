#include "directional_light.h"

DirectionalLight::DirectionalLight(const json& j) : PunctualLight(j) 
{
    intensity = intensity / 683.f; // candela to watts
}
void to_json(json& j, const DirectionalLight& l)
{
    j["type"] = "directional";
    if (l.name != "")
    {
        j["name"] = l.name;
    }
    if (l.intensity != 1.f)
    {
        j["intensity"] = l.intensity * 683.f;
    }
    if (l.color != vec3(1.f))
    {
        j["color"] = l.color;
    }
}