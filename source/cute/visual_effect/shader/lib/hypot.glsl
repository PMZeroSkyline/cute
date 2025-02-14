#ifndef HYPOT_GLSL
#define HYPOT_GLSL
// https://github.com/blender/blender/blob/main/source/blender/gpu/shaders/material/gpu_shader_material_tex_environment.glsl
float hypot(float x, float y)
{
    return sqrt(x*x + y*y);
}
#endif