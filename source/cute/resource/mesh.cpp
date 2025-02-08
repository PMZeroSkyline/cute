#include "mesh.h"

Mesh::Mesh(const json& j, const json& gltf, const std::string& dir, const std::vector<std::shared_ptr<Material>>& materials)
{
    for (const json &prim : j["primitives"])
    {
        primitives.push_back(std::make_shared<MeshPrimitive>(prim, gltf, dir, materials));
    }
    if (j.contains("weights"))
    {
        weights = j["weights"].get<std::vector<float>>();
    }
    if (j.contains("name"))
    {
        name = j["name"];
    }
    update();
}
void Mesh::update()
{
    bbox = std::make_shared<AABB>();
    for (int i = 0; i != primitives.size(); i++)
    {
        if (i == 0)
        {
            *bbox = *primitives[i]->attributes->bbox;
        }
        else
        {
            bbox = AABB::make(min(bbox->get_min(), primitives[i]->attributes->bbox->get_min()), max(bbox->get_max(), primitives[i]->attributes->bbox->get_max()));
        }
    }
}