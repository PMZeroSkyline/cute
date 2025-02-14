#ifndef GEOMETRY_SMITH_IBL_HLSL
#define GEOMETRY_SMITH_IBL_HLSL
float geometry_schlick_ibl_ggx(float nv, float roughness)
{
    // note that we use a different k for IBL
    float a = roughness;
    float k = (a * a) / 2.0;

    float nom   = nv;
    float denom = nv * (1.0 - k) + k;

    return nom / denom;
}
float geometry_smith_ibl(vec3 N, vec3 V, vec3 L, float roughness)
{
    float nv = max(dot(N, V), 0.0);
    float nl = max(dot(N, L), 0.0);
    float ggx2 = geometry_schlick_ibl_ggx(nv, roughness);
    float ggx1 = geometry_schlick_ibl_ggx(nl, roughness);

    return ggx1 * ggx2;
}
#endif