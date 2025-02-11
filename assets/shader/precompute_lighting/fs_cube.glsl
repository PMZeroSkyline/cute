out vec4 FragColor;
in V2F {
    vec3 worldPos;
} i;
uniform float iIntensity;
uniform sampler2D iEnvironmentTexture;
// https://learnopengl.com/PBR/Lighting
const float PI = 3.14159265359;
// https://github.com/blender/blender/blob/main/source/blender/gpu/shaders/material/gpu_shader_material_tex_environment.glsl
float hypot(float x, float y)
{
    return sqrt(x*x + y*y);
}
vec2 equirectangular_mapping(/*worldPos*/vec3 v)
{
    vec3 d = normalize(v);
    vec2 uv;
    uv.x = -atan(d.y, d.x) / (2.0 * PI) + 0.5;
    uv.y = atan(d.z, hypot(d.x, d.y)) / PI + 0.5;
    return uv;
}
void main()
{
    vec3 color = texture(iEnvironmentTexture, equirectangular_mapping(i.worldPos)).rgb * iIntensity;
    FragColor = vec4(color, 1.0);
}