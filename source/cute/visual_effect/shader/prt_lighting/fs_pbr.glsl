out vec4 FragColor;
in V2F {
    vec3 worldPos;
    vec2 texcoord0;
    vec3 worldNormal;
} i;
#include "include/light.glsl"
#include "block/light.glsl"
#include "block/camera.glsl"
#include "block/shadow.glsl"
#include "include/pbr.glsl"
#include "include/mapping.glsl"
uniform vec4 iBaseColorFactor;
uniform float iMetallicFactor;
uniform float iRoughnessFactor;
#ifdef BASE_COLOR_TEXTURE_TEXCOORD
uniform sampler2D iBaseColorTexture;
#endif
#ifdef METALLIC_ROUGHNESS_TEXTURE_TEXCOORD
uniform sampler2D iMetallicRoughnessTexture;
#endif
#ifdef NORMAL_TEXTURE_TEXCOORD
uniform sampler2D iNormalTexture;
uniform float iNormalTextureScale;
#endif
#ifdef MASK
uniform float iAlphaCutoff;
#endif
uniform samplerCube iSpecularPrefilterTexture;
uniform sampler2D iBRDFLut;
uniform sampler2D iShadowDepthAttachment;
void main() {
    vec4 albedo = iBaseColorFactor;
#ifdef BASE_COLOR_TEXTURE_TEXCOORD
    vec4 base_color = texture(iBaseColorTexture, i.texcoord0);
    albedo.xyz *= pow(base_color.xyz, vec3(2.2));
    albedo *= base_color.w;
    #ifdef MASK
    if (base_color.a < iAlphaCutoff) 
    { 
        discard; 
    }
    #endif
#endif
    float roughness = iRoughnessFactor;
    float metallic = iMetallicFactor;
    float ao = 1.0;
#ifdef METALLIC_ROUGHNESS_TEXTURE_TEXCOORD
    vec3 arm = texture(iMetallicRoughnessTexture, i.texcoord0).rgb; 
    roughness *= arm.y;
    metallic *= arm.z;
    ao *= arm.x;
#endif
#ifdef NORMAL_TEXTURE_TEXCOORD
    vec3 tangent_normal = texture(iNormalTexture, i.texcoord0).xyz * 2.0 - 1.0;
    tangent_normal = mix(vec3(0.0, 0.0, 1.0), tangent_normal, iNormalTextureScale);
    vec3 N  = i.worldNormal;
    vec3 T  = normalize(dFdx(i.worldPos) * dFdy(i.texcoord0).t - dFdy(i.worldPos) * dFdx(i.texcoord0).t);
    vec3 B  = normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);
    N = normalize(TBN * tangent_normal);
#else
    vec3 N = i.worldNormal;
#endif
    if (gl_FrontFacing == false) {
        N *= vec3(-1.0);
    }
    vec3 V = normalize(iCameraPosition - i.worldPos);
    vec3 F0 = mix(vec3(0.04), albedo.xyz, metallic); 
    vec3 Lo = vec3(0.0);
    for (int it = 0; it != int(iLightSize.x); it++) {
        vec3 L = -iDirectionalLights[it].direction;
        float attenuation = 1.0;
        if (it == 0)
        {
            vec4 lightPos;
            int layer = -1;
            for(int it_layer = 0; it_layer < 4; it_layer++)
            {
                lightPos = iShadowMatrices[it_layer] * vec4(i.worldPos, 1.0);
                lightPos /= lightPos.w;
                if (lightPos.x > -1.0 && lightPos.x < 1.0 && lightPos.y > -1.0 && lightPos.y < 1.0 && lightPos.z > -1.0 && lightPos.z < 1.0)
                {
                    layer = it_layer;
                    break;
                }
            }
            vec3 lightScreenPos = lightPos.xyz * 0.5 + 0.5;
            vec2 lightUV = lightScreenPos.xy * 0.5;
            if (layer == 1)
            {
                lightUV.xy += vec2(0.5, 0.0);
            }
            else if (layer == 2)
            {
                lightUV.xy += vec2(0.0, 0.5);
            }
            else if (layer == 3)
            {
                lightUV.xy += vec2(0.5, 0.5);
            }
            float NL = dot(i.worldNormal, L);
            float bias = 0.0;
            if (NL > 0.0)
            {
                bias = mix(0.003 / float(1+layer), 0.0, NL);
            }
            float shadow = 0.0;
            vec2 texelSize = 1.0 / vec2(textureSize(iShadowDepthAttachment, 0));
            for(int x = -1; x <= 1; ++x)
            {
                for(int y = -1; y <= 1; ++y)
                {
                    float shadowDepth = texture(iShadowDepthAttachment, lightUV + vec2(x, y) * texelSize).x; 
                    float pcfAttenuation = ((shadowDepth + bias) < lightScreenPos.z ? 0.0 : 1.0);
                    shadow += (1.0 - pcfAttenuation);
                }    
            }
            shadow /= 9.0;
            attenuation = 1.0 - shadow;
        }
        vec3 radiance = iDirectionalLights[it].color * iDirectionalLights[it].intensity * PI * attenuation;
        Lo += CookTorranceBRDF(L, N, V, F0, albedo.xyz, metallic, roughness) * radiance;
    }
    for (int it = 0; it != int(iLightSize.y); it++) {
        vec3 L = normalize(iPointLights[it].position - i.worldPos);
        float attenuation = DistanceAttenuation(iPointLights[it].position, iPointLights[it].range, i.worldPos);
        vec3 radiance = iPointLights[it].color * iPointLights[it].intensity * attenuation * 0.1;
        Lo += CookTorranceBRDF(L, N, V, F0, albedo.xyz, metallic, roughness) * radiance;
    }
    for (int it = 0; it != int(iLightSize.z); it++) {
        vec3 L = normalize(iSpotLights[it].position - i.worldPos);
        float attenuation = DistanceAttenuation(iSpotLights[it].position, iSpotLights[it].range, i.worldPos) 
                            * SpotAttenuation(iSpotLights[it].direction, iSpotLights[it].angleScale, iSpotLights[it].angleOffset, L);
        vec3 radiance = iSpotLights[it].color * iSpotLights[it].intensity * attenuation;
        Lo += CookTorranceBRDF(L, N, V, F0, albedo.xyz, metallic, roughness) * radiance;
    }
    vec3 F = FresnelSchlick(max(dot(N, V), 0.0), F0, roughness);
    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;	  
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 R = reflect(-V, N);
    #ifdef VERSION_PROFILE_ES
        vec3 prefiltered_color = texture(iSpecularPrefilterTexture, CubemapMapping(R)).rgb * iImageBasedLightIntensity;
    #else
        vec3 prefiltered_color = textureLod(iSpecularPrefilterTexture, CubemapMapping(R), roughness * 4.0).rgb * iImageBasedLightIntensity;
    #endif
    vec2 brdf_lut  = texture(iBRDFLut, vec2(max(dot(N, V), 0.0), roughness)).rg;
    vec3 specular = prefiltered_color * (F * brdf_lut.x + brdf_lut.y);
    vec3 irradiance = EvaluateSH(iIrradianceCoefficients, N) * iImageBasedLightIntensity;
    vec3 diffuse = irradiance * albedo.xyz;
    vec3 ambient = (kD * diffuse + specular) * ao;
    vec3 color = ambient + Lo;
    FragColor = vec4(color, albedo.a);
}