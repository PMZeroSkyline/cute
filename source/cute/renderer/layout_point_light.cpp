#include "layout_point_light.h"

std140::PointLight::PointLight(const vec3 &_position, const vec3 &_color, float _intensity, float _range) : position(_position), color(_color), intensity(_intensity), range(_range) {}