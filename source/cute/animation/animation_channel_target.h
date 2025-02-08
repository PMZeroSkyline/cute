#ifndef ANIMATION_CHANNEL_TARGET_H
#define ANIMATION_CHANNEL_TARGET_H

#include "scene_graph/node.h"

struct AnimationChannelTarget
{
    Node* node = nullptr;
    int path; // "translation 0" "rotation 1" "scale 2" "weights 3"
    AnimationChannelTarget() = default;
    AnimationChannelTarget(const json& j, const std::vector<std::shared_ptr<Node>>& nodes);
};

#endif