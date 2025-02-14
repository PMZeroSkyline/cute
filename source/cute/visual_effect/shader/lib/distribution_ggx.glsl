#ifndef DISTRIBUTION_GGX
#define DISTRIBUTION_GGX
#include "pi.glsl"
// trowbridge_reitz (ggx)
float distribution_ggx(vec3 N, vec3 H, float roughness) 
{
    float a = roughness*roughness;
    float a2 = a*a;
    float nh = max(dot(N, H), 0.0);
    float nh2 = nh*nh;

    float nom   = a2;
    float denom = (nh2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
#endif