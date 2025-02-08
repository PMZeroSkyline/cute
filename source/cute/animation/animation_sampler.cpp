#include "animation_sampler.h"

AnimationSampler::AnimationSampler(const json &j, const json &gltf, const std::string& dir)
{
    json accessor = gltf["accessors"][int(j["input"])];
    if (!gltf_access(dir, gltf, accessor, &input, nullptr))
        std::cout << "failed to read animation" << std::endl;
    min = accessor["min"][0];
    max = accessor["max"][0];
    if (j.contains("interpolation"))
    {
        if (j["interpolation"] == "LINEAR") interpolation = 0;
        else if (j["interpolation"] == "STEP") interpolation = 1;
        else if (j["interpolation"] == "CUBICSPLINE") interpolation = 2;
    }
    accessor = gltf["accessors"][int(j["output"])];
    int byte_offset = accessor.value("byteOffset", 0);
    int buffer_view = accessor["bufferView"];
    int count = accessor["count"];
    if (accessor["componentType"] == GL_FLOAT && accessor["type"] == "SCALAR")
        if (!gltf_view_buffer(dir, gltf, buffer_view, byte_offset, count, &o_float)) 
            std::cout << "failed to read animation" << std::endl;
    if (accessor["componentType"] == GL_FLOAT && accessor["type"] == "VEC3")
        if (!gltf_view_buffer(dir, gltf, buffer_view, byte_offset, count, &o_vec))
            std::cout << "failed to read animation" << std::endl;
    if (accessor["componentType"] == GL_FLOAT && accessor["type"] == "VEC4")
        if (!gltf_view_buffer(dir, gltf, buffer_view, byte_offset, count, &o_quat))
            std::cout << "failed to read animation" << std::endl;
}
void AnimationSampler::at(float time, vec3& val) const
{
    float time_beg = input[0];
    float time_end = input[input.size()-1];
    if (time <= time_beg)
    {
        val = o_vec[0];
        return;
    }
    else if (time >= time_end)
    {
        val = o_vec[o_vec.size()-1];
        return;
    }
    for (int i = 0; i < input.size() - 1; i++)
    {
        float time_left = input[i];
        float time_right = input[i+1];
        if (time < time_left || time > time_right)
            continue;
        float interp = (time - time_left) / (time_right - time_left);
        val = lerp(o_vec[i], o_vec[i+1], interp);
        return;
    }
}
void AnimationSampler::at(float time, quat& val) const
{
    float time_beg = input[0];
    float time_end = input[input.size()-1];
    if (time <= time_beg)
    {
        val = o_quat[0];
        return;
    }
    else if (time >= time_end)
    {
        val = o_quat[o_quat.size()-1];
        return;
    }
    for (int i = 0; i < input.size() - 1; i++)
    {
        float time_left = input[i];
        float time_right = input[i+1];
        if (time < time_left || time > time_right)
            continue;
        float interp = (time - time_left) / (time_right - time_left);
        val = slerp(o_quat[i], o_quat[i+1], interp);
        return;
    }
}
void AnimationSampler::at(float time, std::vector<float>& weights)
{
    float time_beg = input[0];
    float time_end = input[input.size()-1];
    int stride = weights.size();
    if (time <= time_beg)
    {
        for (int i = 0; i < stride; i++)
            weights[i] = o_float[i];
        return;
    }
    else if (time >= time_end)
    {
        for (int i = 0; i < stride; i++)
            weights[i] = o_float[stride * (input.size() - 1) + i];
        return;
    }
    for (int i = 0; i < input.size() - 1; i++)
    {
        float time_left = input[i];
        float time_right = input[i+1];

        if (time < time_left || time > time_right)
            continue;
        
        float interp = (time - time_left) / (time_right - time_left);
        for (int j = 0; j < stride; j++)
            weights[j] = lerp(o_float[stride * i + j], o_float[stride * (i + 1) + j], interp);
        return;
    }
}