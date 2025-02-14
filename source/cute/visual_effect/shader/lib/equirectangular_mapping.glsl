#ifndef EQUIRECTANGULAR_MAPPING_GLSL
#define EQUIRECTANGULAR_MAPPING_GLSL
#include "pi.glsl"
#include "hypot.glsl"
vec2 equirectangular_mapping(/*worldPos*/vec3 v)
{
    vec3 d = normalize(v);
    vec2 uv;
    uv.x = -atan(d.y, d.x) / (2.0 * PI) + 0.5;
    uv.y = atan(d.z, hypot(d.x, d.y)) / PI + 0.5;
    return uv;
}
#endif