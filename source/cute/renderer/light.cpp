#include "light.h"

Light::Light(const json& j)
{
    if (j.contains("name"))
    {
        name = j["name"];
    }
    if (j.contains("intensity"))
    {
        intensity = j["intensity"];
    }
}
Light::~Light() {}