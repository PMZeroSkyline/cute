#ifndef IMAGE_BASED_LIGHT_H
#define IMAGE_BASED_LIGHT_H

#include "light.h"
#include "texture_cube.h"

struct ImageBasedLight : Light
{
    // https://github.com/KhronosGroup/glTF/blob/main/extensions/2.0/Vendor/EXT_lights_image_based/README.md
    std::string name;
    quat rotation;
    float intensity = 1.f;
    std::array<vec3, 9> irradiance_coefficients;
    std::shared_ptr<TextureCube> specular_texture;
    int specular_image_size;
    ImageBasedLight() = default;
    ImageBasedLight(const std::shared_ptr<TextureCube>& _specular_texture, const std::array<vec3, 9>& _irradiance_coefficients, const float& _intensity = 1.f, const std::string& _name = "", const quat& _rotation = quat());
    ImageBasedLight(const json& j, const std::vector<std::shared_ptr<Image>>& images);
    void to_json(json& j, const ImageBasedLight& l);
    void read_irradiance_coefficients(vec4 coeff[9]) const;
};

#endif
