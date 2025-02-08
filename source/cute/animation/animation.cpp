#include "animation.h"

Animation::Animation(const json &j, const json &gltf, const std::string& dir, const std::vector<std::shared_ptr<Node>>& nodes)
{
    for (const json &spl : j["samplers"])
    {
        samplers.emplace_back(spl, gltf, dir);
    }
    for (const json &cn : j["channels"])
    {
        channels.emplace_back(cn, samplers, nodes);
    }
    if (j.contains("name"))
    {
        name = j["name"];
    }
}
void Animation::update(float time)
{
    for (auto& channel : channels)
    {
        channel.update(time);
    }
}