out vec2 FragColor;
in V2F {
    vec2 texcoord0;
} i;
// https://learnopengl.com/PBR/Lighting
const float PI = 3.14159265359;
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
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = geometry_schlick_ibl_ggx(nv, roughness);
    float ggx1 = geometry_schlick_ibl_ggx(NdotL, roughness);
    return ggx1 * ggx2;
}
vec3 importance_sample_ggx(vec2 Xi, vec3 N, float roughness)
{
    float a = roughness*roughness;
    float phi = 2.0 * PI * Xi.x;
    float cos_theta = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));
    float sin_theta = sqrt(1.0 - cos_theta*cos_theta);
    vec3 H;
    H.x = cos(phi) * sin_theta;
    H.y = sin(phi) * sin_theta;
    H.z = cos_theta;
    vec3 up        = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
    vec3 tangent   = normalize(cross(up, N));
    vec3 bitangent = cross(N, tangent);
    vec3 sample_vec = tangent * H.x + bitangent * H.y + N * H.z;
    return normalize(sample_vec);
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
void main() 
{
    FragColor = integrate_brdf(i.texcoord0.x, i.texcoord0.y);
}