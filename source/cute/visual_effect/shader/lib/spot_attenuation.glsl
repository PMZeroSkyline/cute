#ifndef SPOT_ATTENUATION_GLSL
#define SPOT_ATTENUATION_GLSL
// https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Khronos/KHR_lights_punctual/README.md
float spot_attenuation(vec3 direction, float angle_scale, float angle_offset, vec3 L) {
    float cd = dot(-direction, L);
    float angular_attenuation = clamp(cd * angle_scale + angle_offset, 0.0, 1.0);
    angular_attenuation *= angular_attenuation;
    return angular_attenuation;
}
#endif