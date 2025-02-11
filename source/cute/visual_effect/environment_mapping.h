#ifndef ENVIRONMENT_MAPPING_H
#define ENVIRONMENT_MAPPING_H
#include "renderer/image_based_light.h"
#include "renderer/texture_2d.h"

std::shared_ptr<TextureCube> render_texture_cube(const std::shared_ptr<Texture2D>& hdr_2d, int size);
std::shared_ptr<ImageBasedLight> make_image_based_light(const std::string& hdr_path, float intensity);

#endif