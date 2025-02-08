#include "uniform_spot_light.h"

std140::SpotLight::SpotLight(const vec3 &_position, const vec3 &_direction, const vec3 &_color, float _intensity, float _range, float innerConeAngle, float outerConeAngle) : position(_position), direction(_direction), color(_color), intensity(_intensity), range(_range)
{
    angleScale = 1.0f / fmax(0.001f, cos(innerConeAngle) - cos(outerConeAngle));
    angleOffset = -cos(outerConeAngle) * angleScale;
}