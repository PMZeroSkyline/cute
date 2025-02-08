#include "punctual_light.h"

PunctualLight::PunctualLight(const json& j) : Light(j)
{
    if (j.contains("color"))
    {
        color = j["color"];
    }
}