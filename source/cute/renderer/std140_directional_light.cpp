#include "std140_directional_light.h"

std140::DirectionalLight::DirectionalLight(const vec3 &_direction, const vec3 &_color, float _intensity) : direction(_direction), color(_color), intensity(_intensity) {}