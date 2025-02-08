#include "world.h"
#include "renderer/camera_component.h"
#include "renderer/perspective_camera.h"
#include "renderer/orthographic_camera.h"
#include "resource/mesh_gpu_instancing_component.h"
#include "resource/skin_component.h"
#include "resource/mesh_component.h"
#include "renderer/directional_light.h"
#include "renderer/spot_light.h"
#include "renderer/image_based_light.h"
#include "renderer/light_component.h"
#include "renderer/texture_2d.h"
#include "platform/file_system.h"
#include "physics/physics_material.h"
#include "physics/sphere_shape.h"
#include "physics/rigid_body_component.h"
#include "physics/box_shape.h"
#include "core/object_handle/get_or_make.h"
World::World() 
{
    scene = std::make_shared<Scene>();
    scenes.push_back(scene);
};
static void parse_cameras(const json& gltf, std::vector<std::shared_ptr<Camera>> &cameras)
{
    if (!gltf.contains("cameras"))
    {
        return;
    }
    for (const json &cam : gltf["cameras"])
    {
        if (cam["type"] == "perspective" && cam.contains("perspective"))
        {
            cameras.push_back(std::make_shared<PerspectiveCamera>(cam));
        }
        else if (cam["type"] == "orthographic" && cam.contains("orthographic"))
        {
            cameras.push_back(std::make_shared<OrthographicCamera>(cam));
        }
        else
        {
            std::cout << "load gltf camera failed" << std::endl;
        }
    }
}
static void parse_image_based_light_images_ids(const json& gltf, std::set<int>& cubemap_img_ids)
{
    if (!gltf.contains("extensions") || !gltf["extensions"].contains("EXT_lights_image_based"))
    {
        return;
    }
    json EXT_lights_image_based = gltf["extensions"]["EXT_lights_image_based"];
    if (!EXT_lights_image_based.contains("lights"))
    {
        return;
    }
    for (const json &lit : EXT_lights_image_based["lights"])
    {
        for (const json &spec_img : lit["specularImages"]) 
        {
            std::array<int, 6> fac_imgs = spec_img.get<std::array<int, 6>>();
            cubemap_img_ids.insert(fac_imgs.begin(), fac_imgs.end());
        }
    }
}
static void parse_images(const std::string& dir, const json& gltf, std::vector<std::shared_ptr<Image>>& images)
{
    if (!gltf.contains("images"))
    {
        return;
    }
    std::set<int> cubemap_img_ids;
    parse_image_based_light_images_ids(gltf, cubemap_img_ids);
    int i = 0;
    for (const json &img : gltf["images"])
    {
        if (img.contains("uri"))
        {
            images.push_back(Image::get(dir + "/" + std::string(img["uri"]), cubemap_img_ids.count(i) == 0, true)); // if is cubemap image, then shoud not be flipped.
        }
        i++;
    }
}
static void parse_samplers(const json& gltf, std::vector<std::shared_ptr<TextureSampler>>& samplers)
{
    if (!gltf.contains("samplers"))
    {
        return;
    }
    for (const json &spl : gltf["samplers"])
    {
        samplers.push_back(std::make_shared<TextureSampler>(spl));
    }
}
static void parse_textures(const json& gltf, std::vector<std::shared_ptr<Texture>>& textures, const std::vector<std::shared_ptr<TextureSampler>>& samplers, const std::vector<std::shared_ptr<Image>>& images)
{
    if (!gltf.contains("textures"))
    {
        return;
    }
    for (const json &tex : gltf["textures"])
    {
        std::shared_ptr<TextureSampler> sampler;
        if (tex.contains("sampler"))
        {
            sampler = samplers[tex["sampler"]];
        }
        else
        {
            sampler = TextureSampler::make_linear_repeat();
        }
        std::shared_ptr<Image> source;
        if (tex.contains("source"))
        {
            source = images[tex["source"]];
        }
        else
        {
            std::cout << "gltf texture source behavior is undefined." << std::endl;
        }
        textures.push_back(Texture2D::get(source->path, true, sampler, true));
        if (tex.contains("name"))
        {
            textures.back()->name = tex["name"];
        }
    }
}
static void parse_materials(const json& gltf, std::vector<std::shared_ptr<Material>>& materials, const std::vector<std::shared_ptr<Texture>>& textures)
{
    if (!gltf.contains("materials"))
    {
        return;
    }
    for (const json &mat : gltf["materials"])
    {
        materials.push_back(std::make_shared<Material>(mat, textures));
    }
}
static void parse_meshes(const std::string& dir, const json& gltf, std::vector<std::shared_ptr<Mesh>>& meshes, const std::vector<std::shared_ptr<Material>>& materials)
{
    if (!gltf.contains("meshes"))
    {
        return;
    }
    for (const json &ms : gltf["meshes"])
    {
        meshes.push_back(std::make_shared<Mesh>(ms, gltf, dir, materials));
    }
}
static void parse_nodes(const json& gltf, std::vector<std::shared_ptr<Node>>& nodes)
{
    if (!gltf.contains("nodes"))
    {
        return;
    }
    for (const json &nd : gltf["nodes"])
    {
        nodes.push_back(std::make_shared<Node>(nd));
    }
}
static void parse_skins(const std::string& dir, const json& gltf, std::vector<std::shared_ptr<Skin>>& skins, const std::vector<std::shared_ptr<Node>>& nodes)
{
    if (!gltf.contains("skins"))
    {
        return;
    }
    for (const json &sk : gltf["skins"])
    {
        skins.push_back(std::make_shared<Skin>(sk, gltf, dir, nodes));
    }
}
static void parse_animations(const std::string& dir, const json& gltf, std::vector<std::shared_ptr<Animation>>& animations, const std::vector<std::shared_ptr<Node>>& nodes)
{
    if (!gltf.contains("animations"))
    {
        return;
    }
    for (const json &anim : gltf["animations"])
    {
        animations.push_back(std::make_shared<Animation>(anim, gltf, dir, nodes));
    }
}
static void parse_scenes(const json& gltf, std::vector<std::shared_ptr<Scene>>& scenes, const std::vector<std::shared_ptr<Node>>& nodes)
{
    if (!gltf.contains("scenes"))
    {
        return;
    }
    for (const json &sce : gltf["scenes"])
    {
        scenes.push_back(std::make_shared<Scene>(sce, nodes));
    }
}
static void parse_punctual_lights(const json& gltf, std::vector<std::shared_ptr<Light>>& punctual_lights)
{
    if (!gltf.contains("extensions") || !gltf["extensions"].contains("KHR_lights_punctual") || !gltf["extensions"]["KHR_lights_punctual"].contains("lights"))
    {
        return;
    }
    for (const json &lit : gltf["extensions"]["KHR_lights_punctual"]["lights"])
    {                
        if (lit["type"] == "directional")
        {
            punctual_lights.push_back(std::make_shared<DirectionalLight>(lit));
        }
        else if (lit["type"] == "point")
        {
            punctual_lights.push_back(std::make_shared<PointLight>(lit));
        }
        else if (lit["type"] == "spot")
        {
            punctual_lights.push_back(std::make_shared<SpotLight>(lit));
        }
        else
        {
            std::cout << "unknow light type " << lit["type"] << std::endl;
        }
    }
}
static void parse_image_based_lights(const json& gltf, std::vector<std::shared_ptr<Light>>& image_based_lights, const std::vector<std::shared_ptr<Image>>& images)
{
    if (!gltf.contains("extensions") || !gltf["extensions"].contains("EXT_lights_image_based") || !gltf["extensions"]["EXT_lights_image_based"].contains("lights"))
    {
        return;
    }
    for (const json &lit : gltf["extensions"]["EXT_lights_image_based"]["lights"])
    {
        image_based_lights.push_back(std::make_shared<ImageBasedLight>(lit, images));
    }
}
static void parse_shapes(const json& gltf, std::vector<std::shared_ptr<Shape>>& shapes)
{
    if (!gltf.contains("extensions") || !gltf["extensions"].contains("KHR_implicit_shapes") || !gltf["extensions"]["KHR_implicit_shapes"].contains("shapes"))
    {
        return;
    }
    for (const json &sh : gltf["extensions"]["KHR_implicit_shapes"]["shapes"])
    {
        if (sh["type"] == "sphere")
        {
            shapes.push_back(get_or_make(SphereShape::weak, SphereShape::hash(sh["sphere"], vec3(1.f)), [&sh](){
                return std::make_shared<SphereShape>(sh["sphere"]);
            }));
        }
        else if (sh["type"] == "box")
        {
            shapes.push_back(get_or_make(BoxShape::weak, BoxShape::hash(sh["box"], vec3(1.f)), [&sh](){
                return std::make_shared<BoxShape>(sh["box"]);
            }));
        }
    }
}
static void parse_physics_materials(const json& gltf, std::vector<std::shared_ptr<PhysicsMaterial>>& physics_materials)
{
    if (!gltf.contains("extensions") || !gltf["extensions"].contains("KHR_physics_rigid_bodies") || !gltf["extensions"]["KHR_physics_rigid_bodies"].contains("physicsMaterials"))
    {
        return;
    }
    for (const json &mat : gltf["extensions"]["KHR_physics_rigid_bodies"]["physicsMaterials"])
    {
        physics_materials.emplace_back(std::make_shared<PhysicsMaterial>(mat));
    }
}
static void setup_scene_graph(const std::string& dir, const json& gltf, std::vector<std::shared_ptr<Node>>& nodes, const std::vector<std::shared_ptr<Camera>>& cameras, const std::vector<std::shared_ptr<Skin>>& skins, const std::vector<std::shared_ptr<Mesh>>& meshes, const std::vector<std::shared_ptr<Light>>& punctual_lights, const std::vector<std::shared_ptr<Light>>& image_based_lights, const std::vector<std::shared_ptr<Shape>>& shapes, const std::vector<std::shared_ptr<PhysicsMaterial>>& physics_materials)
{
    if (!gltf.contains("nodes"))
    {
        return;
    }
    const json& nds = gltf["nodes"];
    for (int i = 0; i < nds.size(); i++)
    {
        const json& nd = nds[i];
        if (nd.contains("camera"))
        {
            nodes[i]->add_component<CameraComponent>(cameras[nd["camera"]]);
        }
        if (nd.contains("skin"))
        {
            nodes[i]->add_component<SkinComponent>(skins[nd["skin"]]);
        }
        if (nd.contains("mesh"))
        {
            nodes[i]->add_component<MeshComponent>(meshes[nd["mesh"]]);
        }
        if (nd.contains("weights"))
        {
            // nd["weights"].get<std::vector<float>>();
        }
        if (nd.contains("extras"))
        {
            // nd["extras"];
        }
    }
    for (int i = 0; i < nds.size(); i++)
    {
        const json& nd = nds[i];
        if (!nd.contains("children"))
        {
            continue;
        }
        for (auto& chil : nd["children"])
        {
            nodes[i]->add_child(nodes[chil]);
        }
    }
    for (int i = 0; i < nds.size(); i++)
    {
        const json& nd = nds[i];
        if (!nd.contains("extensions"))
        {
            continue;
        }
        const json& extensions = nd["extensions"];
        if (extensions.contains("KHR_lights_punctual") && extensions["KHR_lights_punctual"].contains("light"))
        {
            nodes[i]->add_component<LightComponent>(punctual_lights[extensions["KHR_lights_punctual"]["light"]]);
        }
        if (extensions.contains("EXT_lights_image_based") && extensions["EXT_lights_image_based"].contains("light"))
        {
            nodes[i]->add_component<LightComponent>(image_based_lights[extensions["EXT_lights_image_based"]["light"]]);
        }
        if (extensions.contains("KHR_physics_rigid_bodies"))
        {
            nodes[i]->add_component<RigidBodyComponent>(std::make_shared<RigidBody>(extensions["KHR_physics_rigid_bodies"], shapes, nodes, physics_materials, nodes[i]->local_transform.scale));
        }
        if (extensions.contains("EXT_mesh_gpu_instancing"))
        {
            nodes[i]->add_component<MeshGPUInstancingComponent>(std::make_shared<MeshGPUInstancing>(extensions["EXT_mesh_gpu_instancing"], gltf, dir, nodes[i]->get_component<MeshComponent>()->mesh.get()));
        }
    }
}
World::World(const std::string &path)
{
    json gltf = json::parse(read_file(path));
    if (gltf["asset"]["version"].empty())
    {
        return;
    }
    std::string dir = path.substr(0, path.find_last_of("/"));
    std::vector<std::shared_ptr<Image>> images;
    std::vector<std::shared_ptr<Camera>> cameras;
    std::vector<std::shared_ptr<TextureSampler>> samplers;
    std::vector<std::shared_ptr<Texture>> textures;
    std::vector<std::shared_ptr<Material>> materials;
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::vector<std::shared_ptr<Node>> nodes;
    std::vector<std::shared_ptr<Skin>> skins;    
    parse_cameras(gltf, cameras);
    parse_images(dir, gltf, images);
    parse_samplers(gltf, samplers);
    parse_textures(gltf, textures, samplers, images);
    parse_materials(gltf, materials, textures);
    parse_meshes(dir, gltf, meshes, materials);
    parse_nodes(gltf, nodes);
    parse_skins(dir, gltf, skins, nodes);
    parse_animations(dir, gltf, animations, nodes);
    parse_scenes(gltf, scenes, nodes);
    if (gltf.contains("scene"))
    {
        scene = scenes[gltf["scene"]];
    }
    std::vector<std::shared_ptr<Light>> punctual_lights;
    std::vector<std::shared_ptr<Light>> image_based_lights;
    parse_punctual_lights(gltf, punctual_lights);
    parse_image_based_lights(gltf, image_based_lights, images);
    std::vector<std::shared_ptr<Shape>> shapes;
    std::vector<std::shared_ptr<PhysicsMaterial>> physics_materials;
    parse_shapes(gltf, shapes);
    parse_physics_materials(gltf, physics_materials);
    setup_scene_graph(dir, gltf, nodes, cameras, skins, meshes, punctual_lights, image_based_lights, shapes, physics_materials);
    for (const auto& s : scenes)
    {
        for (const auto& n : s->nodes)
        {
            n->update_world_matrices();
        }
    }
}
std::shared_ptr<World> World::get(const std::string& path)
{
    return get_or_make(weak, path, [&path](){
       return std::make_shared<World>(path); 
    });
}