#ifndef IMAGE_BASED_LIGHTING_H
#define IMAGE_BASED_LIGHTING_H
#include "renderer/image_based_light.h"

std::shared_ptr<ImageBasedLight> make_image_based_light(const std::string& hdr_path, float intensity);

#endif