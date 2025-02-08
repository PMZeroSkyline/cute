#include "gltf_access.h"
#include "core/math/mat4.h"

template bool gltf_view_buffer<unsigned int>(const std::string& dir, const json& gltf, int buffer_view_id, int byte_offset, int count, std::vector<unsigned int>* dst);
template bool gltf_view_buffer<float>(const std::string& dir, const json& gltf, int buffer_view_id, int byte_offset, int count, std::vector<float>* dst);
template bool gltf_view_buffer<vec2>(const std::string& dir, const json& gltf, int buffer_view_id, int byte_offset, int count, std::vector<vec2>* dst);
template bool gltf_view_buffer<vec3>(const std::string& dir, const json& gltf, int buffer_view_id, int byte_offset, int count, std::vector<vec3>* dst);
template bool gltf_view_buffer<vec4>(const std::string& dir, const json& gltf, int buffer_view_id, int byte_offset, int count, std::vector<vec4>* dst);
template bool gltf_view_buffer<quat>(const std::string& dir, const json& gltf, int buffer_view_id, int byte_offset, int count, std::vector<quat>* dst);

template bool gltf_view_buffer_cast<u8vec4, vec4>(const std::string& dir, const json& gltf, int buffer_view_id, int byte_offset, int count, std::vector<vec4>* dst);
template bool gltf_view_buffer_cast<unsigned short, unsigned int>(const std::string& dir, const json& gltf, int buffer_view_id, int byte_offset, int count, std::vector<unsigned int>* dst);

template bool gltf_access<unsigned int>(const std::string& dir, const json& gltf, const json& accessor, std::vector<unsigned int>* dst, std::vector<unsigned int>* sparse_indices);
template bool gltf_access<float>(const std::string& dir, const json& gltf, const json& accessor, std::vector<float>* dst, std::vector<unsigned int>* sparse_indices);
template bool gltf_access<vec2>(const std::string& dir, const json& gltf, const json& accessor, std::vector<vec2>* dst, std::vector<unsigned int>* sparse_indices);
template bool gltf_access<vec3>(const std::string& dir, const json& gltf, const json& accessor, std::vector<vec3>* dst, std::vector<unsigned int>* sparse_indices);
template bool gltf_access<vec4>(const std::string& dir, const json& gltf, const json& accessor, std::vector<vec4>* dst, std::vector<unsigned int>* sparse_indices);
template bool gltf_access<quat>(const std::string& dir, const json& gltf, const json& accessor, std::vector<quat>* dst, std::vector<unsigned int>* sparse_indices);
template bool gltf_access<mat4>(const std::string& dir, const json& gltf, const json& accessor, std::vector<mat4>* dst, std::vector<unsigned int>* sparse_indices);
