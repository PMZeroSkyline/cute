#include "image_based_light.h"
#include "core/string/string.h"

ImageBasedLight::ImageBasedLight(const std::shared_ptr<TextureCube>& _specular_texture, const std::array<vec3, 9>& _irradiance_coefficients, const std::string& _name, const quat& _rotation, const float& _intensity) : specular_texture(_specular_texture), irradiance_coefficients(_irradiance_coefficients), name(_name), rotation(_rotation), intensity(_intensity), specular_image_size(_specular_texture->mipmaps[0][0]->x) {}
ImageBasedLight::ImageBasedLight(const json& j, const std::vector<std::shared_ptr<Image>>& images) : Light(j)
{
    if (j.contains("rotation"))
    {
        rotation = j["rotation"];
    }
    for (int i = 0; i < 9; i++)
    {
        irradiance_coefficients[i] = *(vec3*)j["irradianceCoefficients"][i].get<std::array<float, 3>>().data();
    }
    std::vector<std::string> uris;
    for (const json &specImg : j["specularImages"]) 
    {
        for (auto& facImg : specImg.get<std::array<int, 6>>())
        {
            uris.push_back(images[facImg]->path);
        }
    }
    specular_texture = TextureCube::get(merge(uris, ','), false, TextureSampler::make_linear_mipmap_clamp_to_edge(), true);
    specular_image_size = j["specularImageSize"];
}
void ImageBasedLight::read_irradiance_coefficients(vec4 coeff[9]) const
{
    for (int i = 0; i < 9; i++)
    {
        coeff[i] = irradiance_coefficients[i];
    }
}
void to_json(json& j, const ImageBasedLight& l)
{
    if (l.name != "")
    {
        j["name"] = l.name;
    }
    if (l.intensity != 1.f)
    {
        j["intensity"] = l.intensity;
    }
    if (l.rotation != quat())
    {
        j["rotation"] = l.rotation;
    }
    j["irradianceCoefficients"] = l.irradiance_coefficients;
    j["specularImageSize"] = l.specular_image_size;
}