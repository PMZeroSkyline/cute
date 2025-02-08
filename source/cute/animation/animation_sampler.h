#ifndef ANIMATION_SAMPLER_H
#define ANIMATION_SAMPLER_H

#include <iostream>
#include "core/parser/json.h"
#include "resource/gltf_access.h"
#include "platform/graphics_wrapper/gl_validation.h"
#include "core/math/quat.h"

struct AnimationSampler
{
    std::vector<float> input;
    int interpolation; // LINEAR STEP CUBICSPLINE
    std::vector<vec3> o_vec;
    std::vector<quat> o_quat;
    std::vector<float> o_float;
    float min = -1;
    float max = -1;
    AnimationSampler() = default;
    AnimationSampler(const json &j, const json &gltf, const std::string& dir);    
    void at(float time, vec3& val) const;
    void at(float time, quat& val) const;
    void at(float time, std::vector<float>& weights);    
};

#endif