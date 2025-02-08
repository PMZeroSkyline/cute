#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "scene_graph/component.h"
#include "camera.h"

struct CameraComponent : Component
{
    std::shared_ptr<Camera> camera;
    CameraComponent() = default;
    CameraComponent(const std::shared_ptr<Camera>& _camera);
};

#endif