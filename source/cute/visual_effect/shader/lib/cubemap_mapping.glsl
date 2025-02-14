#ifndef CUBEMAP_MAPPING_GLSL
#define CUBEMAP_MAPPING_GLSL
// https://www.khronos.org/opengl/wiki/Cubemap_Texture
vec3 cubemap_mapping(vec3 v)
{
    return vec3(v.x, v.z, v.y);
}
#endif