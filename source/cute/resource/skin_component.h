#ifndef SKIN_COMPONENT_H
#define SKIN_COMPONENT_H

#include "scene_graph/component.h"
#include "skin.h"

struct SkinComponent : Component
{
    std::shared_ptr<Skin> skin;
    SkinComponent(const std::shared_ptr<Skin>& _skin);
};

#endif