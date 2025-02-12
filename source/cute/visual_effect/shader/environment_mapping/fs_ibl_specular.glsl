out vec4 FragColor;
in V2F {
    vec3 worldPos;
} i;
// https://learnopengl.com/PBR/Lighting
const float PI = 3.14159265359;
uniform float iRoughness;
uniform samplerCube iEnvironmentTexture;
// trowbridge_reitz (ggx)
float distribution_ggx(vec3 N, vec3 H, float roughness) 
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}
vec3 importance_sample_ggx(vec2 Xi, vec3 N, float roughness)
{
    float a = roughness*roughness;
	
    float phi = 2.0 * PI * Xi.x;
    float cosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));
    float sinTheta = sqrt(1.0 - cosTheta*cosTheta);
	
    vec3 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;
	
    vec3 up        = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
    vec3 tangent   = normalize(cross(up, N));
    vec3 bitangent = cross(N, tangent);
	
    vec3 sampleVec = tangent * H.x + bitangent * H.y + N * H.z;
    return normalize(sampleVec);
}
// http://holger.dammertz.org/stuff/notes_HammersleyOnHemisphere.html
float radical_inverse_VdC(uint bits) 
{
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10;
}
vec2 hammersley(uint i, uint N)
{
    return vec2(float(i)/float(N), radical_inverse_VdC(i));
}
// https://www.khronos.org/opengl/wiki/Cubemap_Texture
vec3 cubemap_mapping(vec3 v)
{
    return vec3(v.x, v.z, v.y);
}

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