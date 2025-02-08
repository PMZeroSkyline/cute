#ifndef ANIMATION_CHANNEL_H
#define ANIMATION_CHANNEL_H

#include "animation_sampler.h"
#include "animation_channel_target.h"
#include "resource/mesh_component.h"
struct AnimationChannel
{
    AnimationSampler* sampler;
    AnimationChannelTarget target;
    AnimationChannel() = default;
    AnimationChannel(const json& j, std::vector<AnimationSampler>& samplers, const std::vector<std::shared_ptr<Node>>& nodes);
    void update(float time);
};

#endif