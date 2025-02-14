#ifndef DISTANCE_ATTENUATION_GLSL
#define DISTANCE_ATTENUATION_GLSL
// https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Khronos/KHR_lights_punctual/README.md
float distance_attenuation(vec3 position, float range, vec3 world_pos) {
    float current_distance = distance(position, world_pos);
    float attenuation = max( min( 1.0 - pow4(current_distance / range), 1.0 ), 0.0 ) / square(current_distance);
    return attenuation;
}
#endif