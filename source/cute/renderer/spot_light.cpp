#include "spot_light.h"

SpotLight::SpotLight(const json& j) : PointLight(j)
{
    if (j.contains("spot"))
    {
        json spot = j["spot"];
        if (spot.contains("innerConeAngle"))
        {
            innerConeAngle = spot["innerConeAngle"];
        }
        if (spot.contains("outerConeAngle"))
        {
            outerConeAngle = spot["outerConeAngle"];
        }
    }
}
void to_json(json& j, const SpotLight& l)
{
    j["type"] = "spot";
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
    if (l.innerConeAngle != 0.f)
    {
        j["spot"]["innerConeAngle"] = l.innerConeAngle;
    }
    if (l.outerConeAngle != PI / 4.f)
    {
        j["spot"]["outerConeAngle"] = l.outerConeAngle;
    }
}