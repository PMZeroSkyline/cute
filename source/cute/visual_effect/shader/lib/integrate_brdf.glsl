#ifndef INTEGRATE_BRDF_H
#define INTEGRAGE_BRDF_H
#include "geometry_smith_ibl.glsl"
#include "importance_sample_ggx.glsl"
#include "hammersley.glsl"
vec2 integrate_brdf(float nv, float roughness)
{
    vec3 V;
    V.x = sqrt(1.0 - nv*nv);
    V.y = 0.0;
    V.z = nv;
    float A = 0.0;
    float B = 0.0; 
    vec3 N = vec3(0.0, 0.0, 1.0);
    const uint SAMPLE_COUNT = 1024u;
    for(uint i = 0u; i < SAMPLE_COUNT; ++i)
    {
        vec2 Xi = hammersley(i, SAMPLE_COUNT);
        vec3 H = importance_sample_ggx(Xi, N, roughness);
        vec3 L = normalize(2.0 * dot(V, H) * H - V);
        float nl = max(L.z, 0.0);
        float nh = max(H.z, 0.0);
        float vh = max(dot(V, H), 0.0);
        if(nl > 0.0)
        {
            float G = geometry_smith_ibl(N, V, L, roughness);
            float G_Vis = (G * vh) / (nh * nv);
            float Fc = pow(1.0 - vh, 5.0);
            A += (1.0 - Fc) * G_Vis;
            B += Fc * G_Vis;
        }
    }
    A /= float(SAMPLE_COUNT);
    B /= float(SAMPLE_COUNT);
    return vec2(A, B);
}
#endif