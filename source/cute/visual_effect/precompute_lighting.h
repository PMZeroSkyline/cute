#ifndef HDR_LIGHTING_H
#define HDR_LIGHTING_H
#include "renderer/texture_2d.h"
#include "renderer/texture_cube.h"


std::shared_ptr<TextureCube> render_ibl_diffuse(const std::shared_ptr<TextureCube>& hdr_cube, int size = 32);
std::shared_ptr<TextureCube> render_ibl_specular(const std::shared_ptr<TextureCube>& hdr_cube, int size = 128);
std::shared_ptr<Texture2D> render_brdf_lut(int size = 512);


#endif