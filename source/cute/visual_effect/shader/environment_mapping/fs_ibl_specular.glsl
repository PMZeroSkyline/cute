out vec4 FragColor;
in V2F {
    vec3 worldPos;
} i;
uniform float iRoughness;
uniform samplerCube iEnvironmentTexture;
#include "../lib/hammersley.glsl"
#include "../lib/importance_sample_ggx.glsl"
#include "../lib/distribution_ggx.glsl"
#include "../lib/cubemap_mapping.glsl"
void main()
{
    vec3 prefilter = vec3(0.0);
    float resolution = float(textureSize(iEnvironmentTexture, 0).x);
    vec3 N = normalize(i.worldPos);
    vec3 R = N;
    vec3 V = R;
    const uint SAMPLE_COUNT = 1024u;
    float total_weight = 0.0;
    for(uint i = 0u; i < SAMPLE_COUNT; ++i)
    {
        vec2 Xi = hammersley(i, SAMPLE_COUNT);
        vec3 H = importance_sample_ggx(Xi, N, iRoughness);
        vec3 L  = normalize(2.0 * dot(V, H) * H - V);
        float nl = max(dot(N, L), 0.0);
        if(nl > 0.0)
        {
            float D   = distribution_ggx(N, H, iRoughness);
            float nh = max(dot(N, H), 0.0);
            float hv = max(dot(H, V), 0.0);
            float pdf = D * nh / (4.0 * hv) + 0.0001; 
            float sa_texel  = 4.0 * PI / (6.0 * resolution * resolution);
            float sa_sample = 1.0 / (float(SAMPLE_COUNT) * pdf + 0.0001);
            float mip_level = iRoughness == 0.0 ? 0.0 : 0.5 * log2(sa_sample / sa_texel); 
            vec3 col = textureLod(iEnvironmentTexture, cubemap_mapping(L), mip_level).rgb;
            prefilter += col * nl;
            total_weight += nl;
        }
    }
    prefilter = prefilter / total_weight;
    FragColor = vec4(prefilter, 1.0);
}