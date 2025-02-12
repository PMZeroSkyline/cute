#ifndef PRECOMPUTE_IBL_H
#define PRECOMPUTE_IBL_H
#include "renderer/texture_2d.h"
#include "renderer/texture_cube.h"

std::shared_ptr<TextureCube> precompute_ibl_diffuse(const std::shared_ptr<TextureCube>& hdr_cube, int size = 32);
std::shared_ptr<TextureCube> precompute_ibl_specular(const std::shared_ptr<TextureCube>& hdr_cube, int size = 128);
std::shared_ptr<Texture2D> precompute_brdf_lut(int size = 512);

#endif