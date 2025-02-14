#ifndef FRESNEL_SCHLICK_ROUGHENSS_GLSL
#define FRESNEL_SCHLICK_ROUGHENSS_GLSL

vec3 fresnel_schlick_roughness(float cos_theta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cos_theta, 0.0, 1.0), 5.0);
}   

#endif