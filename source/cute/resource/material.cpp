#include "material.h"
#include "core/string/string.h"
#include "renderer/texture_2d.h"

Material::Material(const std::shared_ptr<Program>& _program) 
{
    programs[HashedString()] = _program;
}
Material::Material(const json& j, const std::vector<std::shared_ptr<Texture>>& _textures)
{
    std::set<std::string> fs_defs;
    std::string vs_path = "assets/shader/primitive.vert";
    std::string fs_path = "assets/shader/pbr.frag";
    if (j.contains("name")) name = j["name"];
    if (j.contains("pbrMetallicRoughness"))
    {
        json pbr = j["pbrMetallicRoughness"];
        vec4s["iBaseColorFactor"] = pbr.contains("baseColorFactor") ? pbr["baseColorFactor"] : vec4(1.0);
        if (pbr.contains("baseColorTexture"))
        {
            json tex = pbr["baseColorTexture"];
            textures["iBaseColorTexture"] = _textures[tex["index"]];
            fs_defs.insert("BASE_COLOR_TEXTURE_TEXCOORD " + std::to_string(tex.contains("texCoord") ? int(tex["texCoord"]) : 0));
        }
        floats["iMetallicFactor"] = pbr.contains("metallicFactor") ? pbr["metallicFactor"] : 1.f;
        floats["iRoughnessFactor"] = pbr.contains("roughnessFactor") ? pbr["roughnessFactor"] : 1.f;
        if (pbr.contains("metallicRoughnessTexture"))
        {
            json tex = pbr["metallicRoughnessTexture"];
            textures["iMetallicRoughnessTexture"] = _textures[tex["index"]];
            fs_defs.insert("METALLIC_ROUGHNESS_TEXTURE_TEXCOORD " + std::to_string(tex.contains("texCoord") ? int(tex["texCoord"]) : 0));
        }
    }
    if (j.contains("normalTexture"))
    {
        json tex = j["normalTexture"];
        textures["iNormalTexture"] = _textures[tex["index"]];
        floats["iNormalTextureScale"] = tex.contains("scale") ? tex["scale"] : 1.f;
        fs_defs.insert("NORMAL_TEXTURE_TEXCOORD " + std::to_string(tex.contains("texCoord") ? int(tex["texCoord"]) : 0));
    }
    if (j.contains("occlusionTexture"))
    {
        json tex = j["occlusionTexture"];
        textures["iOcclusionTexture"] = _textures[tex["index"]];
        floats["iOcclusionTextureStrength"] = tex.contains("strength") ? tex["strength"] : 1.f;
        fs_defs.insert("OCCLUSION_TEXTURE_TEXCOORD " + std::to_string(tex.contains("texCoord") ? int(tex["texCoord"]) : 0));
    }
    if (j.contains("emissiveTexture"))
    {
        json tex = j["emissiveTexture"];
        textures["iEmissiveTexture"] = _textures[tex["index"]];
        fs_defs.insert("EMISSIVE_TEXTURE_TEXCOORD " + std::to_string(tex.contains("texCoord") ? int(tex["texCoord"]) : 0));
    }
    if (j.contains("emissiveFactor")) vec3s["iEmissiveFactor"] = j["emissiveFactor"];
    if (j.contains("alphaMode"))
    {
        const std::string mode = j["alphaMode"];
        if (mode == "OPAQUE") alpha_mode = OPAQUE_ALPHA_BIT;
        else if (mode == "MASK") alpha_mode = MASK_ALPHA_BIT;
        else if (mode == "BLEND") alpha_mode = BLEND_ALPHA_BIT;
    }
    if (j.contains("alphaCutoff")) floats["iAlphaCutoff"] = j["alphaCutoff"];
    if (j.contains("doubleSided")) cull_face = j["doubleSided"] == false;
    if (alpha_mode == OPAQUE_ALPHA_BIT) depth_test = GL_TRUE;
    else if (alpha_mode == MASK_ALPHA_BIT)
    {
        depth_test = GL_TRUE;
        fs_defs.insert("MASK");
    }
    else if (alpha_mode == BLEND_ALPHA_BIT)
    {
        depth_test = GL_TRUE;
        blend = GL_TRUE;
        blend_func_sfactor = GL_SRC_ALPHA;
        blend_func_dfactor = GL_ONE_MINUS_SRC_ALPHA;
    }
    if (j.contains("extras"))
    {
        json extras = j["extras"];
        if (extras.contains("program"))
        {
            json _program = extras["program"];
            vs_path = _program["vertex"];
            fs_path = _program["fragment"];
        }
        if (extras.contains("floats")) for (auto& item : extras["floats"].items()) floats[item.key()] = item.value();
        if (extras.contains("vec2s")) for (auto& item : extras["vec2s"].items()) vec2s[item.key()] = item.value();
        if (extras.contains("vec3s")) for (auto& item : extras["vec3s"].items()) vec3s[item.key()] = item.value();
        if (extras.contains("vec4s")) for (auto& item : extras["vec4s"].items()) vec4s[item.key()] = item.value();
        if (extras.contains("textures")) for (auto& item : extras["textures"].items()) textures[item.key()] = Texture2D::get(item.value()["image"], true, item.value().contains("sampler") ? std::make_shared<TextureSampler>(item.value()["sampler"]) : TextureSampler::make_linear_mipmap_repeat(4), true);
        if (extras.contains("material"))
        {
            json _material = extras["material"];
            if (_material.contains("depthTest")) depth_test = _material["depthTest"];
            if (_material.contains("depthMask")) depth_mask = _material["depthMask"];
            if (_material.contains("depthFunc")) depth_func = _material["depthFunc"];
            if (_material.contains("blend")) blend = _material["blend"];
            if (_material.contains("blendFunc_sfactor")) blend_func_sfactor = _material["blendFunc_sfactor"];
            if (_material.contains("blendFunc_dfactor")) blend_func_dfactor = _material["blendFunc_dfactor"];
            if (_material.contains("cullFace")) cull_face = _material["cullFace"];
            if (_material.contains("cullFace_mode")) cull_face_mode = _material["cullFace_mode"];
            if (_material.contains("polygonMode_face")) polygon_mode_face = _material["polygonMode_face"];
            if (_material.contains("polygonMode_mode")) polygon_mode_mode = _material["polygonMode_mode"];
        }
    }
    programs[HashedString()] = Program::get(vs_path, fs_path+(fs_defs.size()? ",":"")+merge(fs_defs,','));
}
void Material::context_state()
{
    // https://stackoverflow.com/questions/7505018/repeated-state-changes-in-opengl
    if (depth_test)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(depth_func);
        glDepthMask(depth_mask);
    }
    else
    {
        glDisable(GL_DEPTH_TEST);
    }
    if (blend)
    {
        glEnable(GL_BLEND);
        glBlendFunc(blend_func_sfactor, blend_func_dfactor);
    }
    else
    {
        glDisable(GL_BLEND);
    }
    if (cull_face)
    {
        glEnable(GL_CULL_FACE);
        glCullFace(cull_face_mode);
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }
    glPolygonMode(polygon_mode_face, polygon_mode_mode);
}
void Material::uniform(Program* program)
{
    int samplerSocket = 0;
    for (const auto &pair : textures)
    {
        glActiveTexture(GL_TEXTURE0 + samplerSocket);
        pair.second->bind();
        program->uniform1i(pair.first, samplerSocket);
        samplerSocket++;
    }
    for (const auto &pair : g_textures)
    {
        glActiveTexture(GL_TEXTURE0 + samplerSocket);
        pair.second->bind();
        program->uniform1i(pair.first, samplerSocket);
        samplerSocket++;
    }
    for (const auto &pair : floats) program->uniform1f(pair.first, pair.second);
    for (const auto &pair : vec2s) program->uniform2f(pair.first, pair.second);
    for (const auto &pair : vec3s) program->uniform3f(pair.first, pair.second);
    for (const auto &pair : vec4s) program->uniform4f(pair.first, pair.second);
}
void Material::update(Program* program)
{
    context_state();
    program->use();
    uniform(program);
}
std::shared_ptr<Material> Material::make_default()
{
    std::shared_ptr<Material> material = std::make_shared<Material>(Program::get("assets/shader/primitive.vert", "assets/shader/pbr.frag"));
    material->depth_test = GL_TRUE;
    material->vec3s["iEmissiveFactor"] = vec3();
    material->vec4s["iBaseColorFactor"] = vec4(1.f);
    material->floats["iMetallicFactor"] = 1.f;
    material->floats["iRoughnessFactor"] = 1.f;
    return material;
}
