#ifndef EVALUATE_SPHERICAL_HARMONICS_GLSL
#define EVALUATE_SPHERICAL_HARMONICS_GLSL
vec3 evaluate_spherical_harmonics(Coefficients c, vec3 v) 
{
    vec3 direction = vec3(v.x, v.z, -v.y);
    vec3 value = vec3(0.0);
    value += c.v0 * 0.282095;
    value += c.v1 * 0.488603 * direction.y;
    value += c.v2 * 0.488603 * direction.z;
    value += c.v3 * 0.488603 * direction.x;
    value += c.v4 * 1.092548 * direction.x * direction.y;
    value += c.v5 * 1.092548 * direction.y * direction.z;
    value += c.v6 * 0.315392 * (3.0 * direction.z * direction.z - 1.0);
    value += c.v7 * 1.092548 * direction.x * direction.z;
    value += c.v8 * 0.546274 * (direction.x * direction.x - direction.y * direction.y);
    return value;
}
#endif