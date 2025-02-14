#include "render_world.h"
#include "device/app.h"
#include "resource/world.h"
#include "resource/mesh_component.h"
#include "resource/skin_component.h"
#include "resource/mesh_gpu_instancing_component.h"
#include "renderer/perspective_camera.h"
#include "renderer/orthographic_camera.h"
#include "renderer/camera_component.h"
#include "renderer/directional_light.h"
#include "renderer/point_light.h"
#include "renderer/spot_light.h"
#include "renderer/image_based_light.h"
#include "renderer/light_component.h"

RenderWorld::RenderWorld() {}
void RenderWorld::update() 
{
    render_objects.clear();
    perspective_camera_components.clear();
    orthographic_camera_components.clear();
    directional_light_components.clear();
    point_light_components.clear();
    spot_light_components.clear();
    image_based_light_components.clear();
    std::vector<CameraComponent*> camera_components;
    std::vector<LightComponent*> light_components;
    std::vector<MeshComponent*> mesh_components;
    World::instance->scene->walk_tree([&camera_components, &light_components, &mesh_components](Node* n){
        if (std::shared_ptr<CameraComponent> c = n->get_component<CameraComponent>()) {
            camera_components.push_back(c.get());
        }
        if (std::shared_ptr<LightComponent> c = n->get_component<LightComponent>()) {
            light_components.push_back(c.get());
        }
        if (std::shared_ptr<MeshComponent> c = n->get_component<MeshComponent>()) {
            mesh_components.push_back(c.get());
        }
    });
    std::vector<std::pair<MeshComponent*, float>> distance_pairs;
    distance_pairs.reserve(mesh_components.size());
    for (MeshComponent* mesh_component : mesh_components) {
        distance_pairs.emplace_back(mesh_component, square(vec3(mesh_component->owner->world_matrix.col(3)) - vec3(mesh_component->owner->world_matrix.col(3))));
    }
    std::sort(distance_pairs.begin(), distance_pairs.end(), [](const std::pair<MeshComponent*, float>& a, const std::pair<MeshComponent*, float>& b) {
        return a.second < b.second;
    });
    for (int i = 0; i != distance_pairs.size(); i++) {
        const std::pair<MeshComponent*, float>& pair = distance_pairs[i];
        Node* node = pair.first->owner;
        MeshComponent* mesh_component = pair.first;
        SkinComponent* skin_component = node->get_component<SkinComponent>().get();
        MeshGPUInstancingComponent* mesh_gpu_instancing_component = node->get_component<MeshGPUInstancingComponent>().get();
        render_objects.push_back({node, mesh_component->mesh.get(), skin_component ? skin_component->skin.get() : nullptr, mesh_gpu_instancing_component ? mesh_gpu_instancing_component->mesh_gpu_instancing.get() : nullptr, pair.second});
    }
    for (CameraComponent* camera_component : camera_components) {
        if (PerspectiveCamera* perspective_camera = dynamic_cast<PerspectiveCamera*>(camera_component->camera.get())) {
            ivec2 size = App::instance->window->render_size;
            perspective_camera->aspect_ratio = (float)size.x / (float)size.y;
            perspective_camera_components.push_back(camera_component);
        }
        else if (OrthographicCamera* orthographic_camera = dynamic_cast<OrthographicCamera*>(camera_component->camera.get())) {
            orthographic_camera_components.push_back(camera_component);
        }
    }
    for (auto& light_component : light_components) {
        if (DirectionalLight* l = dynamic_cast<DirectionalLight*>(light_component->light.get())) {
            directional_light_components.push_back(light_component);
        }
        else if (PointLight* l = dynamic_cast<PointLight*>(light_component->light.get())) {
            point_light_components.push_back(light_component);
        }
        else if (SpotLight* l = dynamic_cast<SpotLight*>(light_component->light.get())) {
            spot_light_components.push_back(light_component);
        }
        else if (ImageBasedLight* l = dynamic_cast<ImageBasedLight*>(light_component->light.get())) {
            image_based_light_components.push_back(light_component);
        }
    }
}