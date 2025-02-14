#ifndef LIGHT_GLSL
#define LIGHT_GLSL
struct DirectionalLight
{
    vec3 direction;
    vec3 color;
    float intensity;
};
struct PointLight
{
    vec3 position;
    float range;
    vec3 color;
    float intensity;
};
struct SpotLight
{
    vec3 position;
    float range;
    vec3 direction;
    float intensity;
    vec3 color;
    float angleScale;
    float angleOffset; 
};
#endif