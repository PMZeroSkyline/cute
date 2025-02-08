#ifndef WORLD_H
#define WORLD_H

#include "animation/animation.h"
#include "scene.h"

struct World
{
    std::vector<std::shared_ptr<Animation>> animations;
    std::shared_ptr<Scene> scene;
    std::vector<std::shared_ptr<Scene>> scenes;

    static inline std::shared_ptr<World> instance = std::make_shared<World>();
    static inline std::unordered_map<std::string, std::weak_ptr<World>> weak;

    World();
    World(const std::string &path);
    static std::shared_ptr<World> get(const std::string& path);

};

#endif