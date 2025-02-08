#ifndef ANIMATION_H
#define ANIMATION_H

#include "animation_channel.h"

struct Animation
{
    std::vector<AnimationChannel> channels;
    std::vector<AnimationSampler> samplers;
    std::string name;
    Animation() = default;
    Animation(const json &j, const json &gltf, const std::string& dir, const std::vector<std::shared_ptr<Node>>& nodes);
    void update(float time);
};

#endif