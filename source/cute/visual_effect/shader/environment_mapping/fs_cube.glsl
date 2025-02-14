out vec4 FragColor;
in V2F {
    vec3 worldPos;
} i;
uniform float iIntensity;
uniform sampler2D iEnvironmentTexture;
#include "../lib/equirectangular_mapping.glsl"
void main()
{
    vec3 color = texture(iEnvironmentTexture, equirectangular_mapping(i.worldPos)).rgb * iIntensity;
    FragColor = vec4(color, 1.0);
}