#ifndef GEOMETRY_SMITH_IBL_GLSL
#define GEOMETRY_SMITH_IBL_GLSL
// combination of the GGX and Schlick-Beckmann approximation
float geometry_schlick_ggx(float nv, float roughness) 
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = nv;
    float denom = nv * (1.0 - k) + k;

    return nom / denom;
}

float geometry_smith(vec3 N, vec3 V, vec3 L, float roughness) 
{
    float nv = max(dot(N, V), 0.0);
    float nl = max(dot(N, L), 0.0);
    float ggx2 = geometry_schlick_ggx(nv, roughness);
    float ggx1 = geometry_schlick_ggx(nl, roughness);

    return ggx1 * ggx2;
}
#endif