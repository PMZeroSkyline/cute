#include "animation_channel.h"

AnimationChannel::AnimationChannel(const json& j, std::vector<AnimationSampler>& samplers, const std::vector<std::shared_ptr<Node>>& nodes)
{
    sampler = &samplers[j["sampler"]];
    target = AnimationChannelTarget(j["target"], nodes);
}
void AnimationChannel::update(float time)
{
    if (target.path == 0)
    {
        sampler->at(time, target.node->local_transform.position);
    }
    else if (target.path == 1)
    {
        sampler->at(time, target.node->local_transform.rotation);
    }
    else if (target.path == 2)
    {
        sampler->at(time, target.node->local_transform.scale);
    }
    else if (target.path == 3)
    {
        std::shared_ptr<MeshComponent> component = target.node->get_component<MeshComponent>();
        sampler->at(time, component->mesh->weights);
    }
}