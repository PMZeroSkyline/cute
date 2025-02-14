#ifndef FRESNEL_SCHLICK_GLSL
#define FRESNEL_SCHLICK_GLSL
vec3 fresnel_schlick(float cos_theta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cos_theta, 0.0, 1.0), 5.0);
}
#endif