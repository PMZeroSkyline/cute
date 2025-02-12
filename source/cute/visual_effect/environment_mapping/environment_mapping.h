#ifndef ENVIRONMENT_MAPPING_H
#define ENVIRONMENT_MAPPING_H
#include "renderer/texture_2d.h"
#include "renderer/texture_cube.h"

std::shared_ptr<TextureCube> render_texture_cube(const std::shared_ptr<Texture2D>& hdr_2d, int size);


#endif