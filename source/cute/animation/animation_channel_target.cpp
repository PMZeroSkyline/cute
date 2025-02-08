#include "animation_channel_target.h"

AnimationChannelTarget::AnimationChannelTarget(const json& j, const std::vector<std::shared_ptr<Node>>& nodes)
{
    if (j.contains("node"))
    {
        node = nodes[j["node"]].get();
    }
    if (j.contains("path"))
    {
        if (j["path"] == "translation")
        {
            path = 0;
        }
        else if (j["path"] == "rotation")
        {
            path = 1;
        }
        else if (j["path"] == "scale")
        {
            path = 2;
        }
        else if (j["path"] == "weights")
        {
            path = 3;
        }
    }
}
