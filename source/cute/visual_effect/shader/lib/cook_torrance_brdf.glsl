#ifndef COOK_TORRANCE_BRDF_GLSL
#define COOK_TORRANCE_BRDF_GLSL
#include "distribution_ggx.glsl"
#include "geometry_smith.glsl"
#include "fresnel_schlick.glsl"
vec3 cook_torrance_brdf(vec3 L, vec3 N, vec3 V, vec3 F0, vec3 albedo, float metallic, float roughness) {
    vec3 H = normalize(V + L);
    
    float NDF = distribution_ggx(N, H, roughness);
    float G = geometry_smith(N, V, L, roughness);      
    vec3 F = fresnel_schlick(clamp(dot(H, V), 0.0, 1.0), F0);
       
    vec3 numerator = NDF * G * F; 
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
    vec3 specular = numerator / denominator;
    
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;	  
    float NdotL = max(dot(N, L), 0.0);        
    return (kD * albedo / PI + specular) * NdotL;
}
#endif