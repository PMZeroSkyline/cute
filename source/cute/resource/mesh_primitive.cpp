#include "mesh_primitive.h"
#include "core/object_handle/get_or_make.h"

MeshPrimitive::MeshPrimitive(const json& j, const json& gltf, const std::string& dir, const std::vector<std::shared_ptr<Material>>& materials)
{
    attributes = std::make_shared<MeshPrimitiveAttributes>(j["attributes"], gltf, dir);
    if (j.contains("indices"))
    {
        json accessor = gltf["accessors"][int(j["indices"])];
        indices = std::make_shared<std::vector<unsigned int>>();
        if (!gltf_access(dir, gltf, accessor, indices.get(), nullptr))
            std::cout << "failed to read mesh" << std::endl;
    }
    if (j.contains("material"))
    {
        material = materials[j["material"]];
    }
    if (j.contains("targets"))
    {
        targets = std::make_shared<std::vector<MeshPrimitiveTarget>>();
        for (const json &tag : j["targets"])
            targets->emplace_back(tag, gltf, dir);
    }
    update(nullptr);
}
void MeshPrimitive::update(std::vector<float>* weights)
{
    vertex_array = std::make_shared<VertexArray>();
    array_buffer = std::make_shared<Buffer>(GL_ARRAY_BUFFER);
    element_array_buffer = std::make_shared<Buffer>(GL_ELEMENT_ARRAY_BUFFER);
    array_buffer->bind();
    array_buffer_data(GL_STATIC_DRAW, weights);
    vertex_array->bind();
    vertex_attrib();
    element_array_buffer->bind();
    element_buffer_data(GL_STATIC_DRAW);
}
void MeshPrimitive::array_buffer_data(GLenum usage, std::vector<float>* weights) const
{
    int oPOSITION, oNORMAL, oTANGENT, oTEXCOORD_0, oTEXCOORD_1, oTEXCOORD_2, oTEXCOORD_3, oCOLOR_0, oJOINTS_0, oWEIGHTS_0;
    int stride = 0;
    oPOSITION = stride;
    stride += sizeof(vec3);
    if (attributes->NORMAL.size())
    {
        oNORMAL = stride;
        stride += sizeof(vec3);
    }
    if (attributes->TANGENT.size())
    {
        oTANGENT = stride;
        stride += sizeof(vec4);
    }
    if (attributes->TEXCOORD_0.size())
    {
        oTEXCOORD_0 = stride;
        stride += sizeof(vec2);
    }
    if (attributes->TEXCOORD_1.size())
    {
        oTEXCOORD_1 = stride;
        stride += sizeof(vec2);
    }
    if (attributes->TEXCOORD_2.size())
    {
        oTEXCOORD_2 = stride;
        stride += sizeof(vec2);
    }
    if (attributes->TEXCOORD_3.size())
    {
        oTEXCOORD_3 = stride;
        stride += sizeof(vec2);
    }
    if (attributes->COLOR_0.size())
    {
        oCOLOR_0 = stride;
        stride += sizeof(vec3);
    }
    if (attributes->JOINTS_0.size())
    {
        oJOINTS_0 = stride;
        stride += sizeof(vec4);
    }
    if (attributes->WEIGHTS_0.size())
    {
        oWEIGHTS_0 = stride;
        stride += sizeof(vec4);
    }
    char *buf = (char *)malloc(stride * attributes->POSITION.size());
    for (int i = 0; i < attributes->POSITION.size(); i++)
    {
        if (attributes->POSITION.size())
        {
            memcpy(buf + stride * i + oPOSITION, &attributes->POSITION[i], sizeof(vec3));
        }
        if (attributes->NORMAL.size())
        {
            memcpy(buf + stride * i + oNORMAL, &attributes->NORMAL[i], sizeof(vec3));
        }
        if (attributes->TANGENT.size())
        {
            memcpy(buf + stride * i + oTANGENT, &attributes->TANGENT[i], sizeof(vec4));
        }
        if (attributes->TEXCOORD_0.size())
        {
            memcpy(buf + stride * i + oTEXCOORD_0, &attributes->TEXCOORD_0[i], sizeof(vec2));
        }
        if (attributes->TEXCOORD_1.size())
        {
            memcpy(buf + stride * i + oTEXCOORD_1, &attributes->TEXCOORD_1[i], sizeof(vec2));
        }
        if (attributes->TEXCOORD_2.size())
        {
            memcpy(buf + stride * i + oTEXCOORD_2, &attributes->TEXCOORD_2[i], sizeof(vec2));
        }
        if (attributes->TEXCOORD_3.size())
        {
            memcpy(buf + stride * i + oTEXCOORD_3, &attributes->TEXCOORD_3[i], sizeof(vec2));
        }
        if (attributes->COLOR_0.size())
        {
            memcpy(buf + stride * i + oCOLOR_0, &attributes->COLOR_0[i], sizeof(vec3));
        }
        if (attributes->JOINTS_0.size())
        {
            memcpy(buf + stride * i + oJOINTS_0, &attributes->JOINTS_0[i], sizeof(vec4));
        }
        if (attributes->WEIGHTS_0.size())
        {
            memcpy(buf + stride * i + oWEIGHTS_0, &attributes->WEIGHTS_0[i], sizeof(vec4));
        }
    }
    if (weights && targets && weights->size() == targets->size())
    {
        for (int i = 0; i < weights->size(); i++)
        {
            float weight = (*weights)[i];
            if (weight == 0.f)
            {
                continue;
            }
            const MeshPrimitiveTarget& target = (*targets)[i];
            if (target.POSITION.size())
            {
                if (target.position_indices.size())
                {
                    for (int j = 0; j < target.position_indices.size(); j++)
                    {
                        unsigned int id = target.position_indices[j];
                        *(vec3*)(buf + stride * id + oPOSITION) += target.POSITION[j] * weight;
                    }
                }
                else
                {
                    for (int j = 0; j < target.POSITION.size(); j++)
                    {
                        *(vec3*)(buf + stride * j + oPOSITION) += target.POSITION[j] * weight;
                    }
                }
            }
            if (target.NORMAL.size())
            {
                if (target.normal_indices.size())
                {
                    for (int j = 0; j < target.normal_indices.size(); j++)
                    {
                        unsigned int id = target.normal_indices[j];
                        *(vec3*)(buf + stride * id + oNORMAL) += target.NORMAL[j] * weight;
                    }
                }
                else
                {
                    for (int j = 0; j < target.NORMAL.size(); j++)
                    {
                        *(vec3*)(buf + stride * j + oNORMAL) += target.NORMAL[j] * weight;
                    }
                }
            }
            if (target.TANGENT.size())
            {
                if (target.tangent_indices.size())
                {
                    for (int j = 0; j < target.tangent_indices.size(); j++)
                    {
                        unsigned int id = target.tangent_indices[j];
                        *(vec4*)(buf + stride * id + oTANGENT) += target.TANGENT[j] * weight;
                    }
                }
                else
                {
                    for (int j = 0; j < target.TANGENT.size(); j++)
                    {
                        *(vec4*)(buf + stride * j + oTANGENT) += target.TANGENT[j] * weight;
                    }
                }
            }
        }
    }
    glBufferData(GL_ARRAY_BUFFER, stride * attributes->POSITION.size(), buf, usage);
    free(buf);
}    
void MeshPrimitive::vertex_attrib() const
{
    int oPOSITION, oNORMAL, oTANGENT, oTEXCOORD_0, oTEXCOORD_1, oTEXCOORD_2, oTEXCOORD_3, oCOLOR_0, oJOINTS_0, oWEIGHTS_0;
    int stride = 0;
    oPOSITION = stride;
    stride += sizeof(vec3);
    if (attributes->NORMAL.size())
    {
        oNORMAL = stride;
        stride += sizeof(vec3);
    }
    if (attributes->TANGENT.size())
    {
        oTANGENT = stride;
        stride += sizeof(vec4);
    }
    if (attributes->TEXCOORD_0.size())
    {
        oTEXCOORD_0 = stride;
        stride += sizeof(vec2);
    }
    if (attributes->TEXCOORD_1.size())
    {
        oTEXCOORD_1 = stride;
        stride += sizeof(vec2);
    }
    if (attributes->TEXCOORD_2.size())
    {
        oTEXCOORD_2 = stride;
        stride += sizeof(vec2);
    }
    if (attributes->TEXCOORD_3.size())
    {
        oTEXCOORD_3 = stride;
        stride += sizeof(vec2);
    }
    if (attributes->COLOR_0.size())
    {
        oCOLOR_0 = stride;
        stride += sizeof(vec3);
    }
    if (attributes->JOINTS_0.size())
    {
        oJOINTS_0 = stride;
        stride += sizeof(vec4);
    }
    if (attributes->WEIGHTS_0.size())
    {
        oWEIGHTS_0 = stride;
        stride += sizeof(vec4);
    }
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(oPOSITION));
    if (attributes->NORMAL.size())
    {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(oNORMAL));
    }
    else
    {
        glDisableVertexAttribArray(1);
    }
    if (attributes->TANGENT.size())
    {
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(oTANGENT));
    }
    else
    {
        glDisableVertexAttribArray(2);
    }
    if (attributes->TEXCOORD_0.size())
    {
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(oTEXCOORD_0));
    }
    else
    {
        glDisableVertexAttribArray(3);
    }
    if (attributes->TEXCOORD_1.size())
    {
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(oTEXCOORD_1));
    }
    else
    {
        glDisableVertexAttribArray(4);
    }
    if (attributes->TEXCOORD_2.size())
    {
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(oTEXCOORD_2));
    }
    else
    {
        glDisableVertexAttribArray(5);
    }
    if (attributes->TEXCOORD_3.size())
    {
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(oTEXCOORD_3));
    }
    else
    {
        glDisableVertexAttribArray(6);
    }
    if (attributes->COLOR_0.size())
    {
        glEnableVertexAttribArray(7);
        glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(oCOLOR_0));
    }
    else
    {
        glDisableVertexAttribArray(7);
    }
    if (attributes->JOINTS_0.size())
    {
        glEnableVertexAttribArray(8);
        glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(oJOINTS_0));
    }
    else
    {
        glDisableVertexAttribArray(8);
    }
    if (attributes->WEIGHTS_0.size())
    {
        glEnableVertexAttribArray(9);
        glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void *>(oWEIGHTS_0));
    }
    else
    {
        glDisableVertexAttribArray(9);
    }
}    
void MeshPrimitive::element_buffer_data(GLenum usage) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(unsigned int), &(*indices)[0], usage);
}
std::shared_ptr<MeshPrimitive> MeshPrimitive::make_plane()
{
    std::shared_ptr<MeshPrimitive> primitive = std::make_shared<MeshPrimitive>();
    primitive->attributes = std::make_shared<MeshPrimitiveAttributes>();
    primitive->indices = std::make_shared<std::vector<unsigned int>>();
    primitive->attributes->POSITION = {
        {-1, -1, 0},
        {-1, 1, 0},
        {1, -1, 0},
        {1, 1, 0}
    };
    for (auto& v : primitive->attributes->POSITION)
    {
        primitive->attributes->TEXCOORD_0.push_back(vec2(v.x, v.y) * 0.5 + 0.5);
    }
    for (int i = 0; i < 4; i++)
    {
        primitive->attributes->NORMAL.push_back(vec3(0, 0, 1));
    }
    (*primitive->indices) = {1, 2, 3, 1, 0, 2};
    primitive->update(nullptr);
    return primitive;
}
std::shared_ptr<MeshPrimitive> MeshPrimitive::make_cube()
{
    std::shared_ptr<MeshPrimitive> primitive = std::make_shared<MeshPrimitive>();
    primitive->attributes = std::make_shared<MeshPrimitiveAttributes>();
    primitive->indices = std::make_shared<std::vector<unsigned int>>();
    std::vector<vec3> normals = {
        {1, 0, 0},
        {-1, 0, 0},
        {0, 1, 0},
        {0, -1, 0},
        {0, 0, 1},
        {0, 0, -1}
    };
    std::vector<vec2> corners = {
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1}
    };
    std::vector<int> corner_indices = {1, 2, 3, 1, 0, 2};
    for (int i = 0; i != normals.size(); i++)
    {
        vec3& normal = normals[i];
        vec3 bitangent = vec3(0, 0, 1);
        if (abs(dot(vec3(0, 0, 1), normal)) >= 0.99)
        {
            bitangent = vec3(1, 0, 0);
        }
        vec3 tangent = cross(bitangent, normal);
        for (auto& corner : corners)
        {
            primitive->attributes->POSITION.push_back(normal + tangent * corner.x + bitangent * corner.y);
            primitive->attributes->TEXCOORD_0.push_back(vec2(corner.x, corner.y) * 0.5 + 0.5);
            primitive->attributes->NORMAL.push_back(normal);
        }
        for (auto& indices : corner_indices)
        {
            primitive->indices->push_back(i * corners.size() + indices);
        }
    }
    primitive->update(nullptr);
    return primitive;
}
std::shared_ptr<MeshPrimitive> make_sphere(int phi_slice, int theta_slice)
{
    std::shared_ptr<MeshPrimitive> primitive = std::make_shared<MeshPrimitive>();
    primitive->attributes = std::make_shared<MeshPrimitiveAttributes>();
    primitive->indices = std::make_shared<std::vector<unsigned int>>();
    for (int i = 0; i < phi_slice; i++)
    {
        float phi_fac = (float)i / (float)phi_slice;
        float phi = PI * 2.0 * phi_fac;
        float phi_next_fac = (float)(i + 1) / float(phi_slice);
        float phi_next = PI * 2.0 * phi_next_fac;
        for (int j = 0; j < theta_slice; j++)
        {
            float theta_fac = (float)j / (theta_slice);
            float theta = PI * (theta_fac - 0.5);
            float theta_next_fac = (float)(j + 1) / (theta_slice);
            float theta_next = PI * (theta_next_fac - 0.5);
            vec3 p0 = vec3(sin(phi) * cos(theta), cos(phi) * cos(theta), sin(theta));
            vec3 p1 = vec3(sin(phi) * cos(theta_next), cos(phi) * cos(theta_next), sin(theta_next));
            vec3 p2 = vec3(sin(phi_next) * cos(theta), cos(phi_next) * cos(theta), sin(theta));
            vec3 p3 = vec3(sin(phi_next) * cos(theta_next), cos(phi_next) * cos(theta_next), sin(theta_next));
            vec3 normal = (p0 + p1 + p2 + p3) / 4.0;
            primitive->attributes->POSITION.push_back(p0);
            primitive->attributes->POSITION.push_back(p1);
            primitive->attributes->POSITION.push_back(p2);
            primitive->attributes->POSITION.push_back(p3);
            primitive->attributes->TEXCOORD_0.push_back(vec2(phi_fac, theta_fac));
            primitive->attributes->TEXCOORD_0.push_back(vec2(phi_fac, theta_next_fac));
            primitive->attributes->TEXCOORD_0.push_back(vec2(phi_next_fac, theta_fac));
            primitive->attributes->TEXCOORD_0.push_back(vec2(phi_next_fac, theta_next_fac));
            primitive->attributes->NORMAL.push_back(normal);
            primitive->attributes->NORMAL.push_back(normal);
            primitive->attributes->NORMAL.push_back(normal);
            primitive->attributes->NORMAL.push_back(normal);
            int vertCount = (i * theta_slice + j) * 4;
            primitive->indices->push_back(vertCount + 3);
            primitive->indices->push_back(vertCount + 2);
            primitive->indices->push_back(vertCount + 0);
            primitive->indices->push_back(vertCount + 3);
            primitive->indices->push_back(vertCount + 0);
            primitive->indices->push_back(vertCount + 1);
        }
    }
    primitive->update(nullptr);
    return primitive;
}
std::shared_ptr<MeshPrimitive> MeshPrimitive::get_plane()
{
    return get_or_make(weak, "plane", [](){
        return make_plane();
    });
}    