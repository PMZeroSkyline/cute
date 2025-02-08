#include "shader.h"
#include "platform/graphics_wrapper/gl_api.h"
#include "core/string/string.h"
#include "platform/platform_detection.h"
#include "platform/file_system.h"
#include <regex>

Shader::Shader(const std::string& uri)
{
    std::vector<std::string> tokens = split(uri, ',');
    path = tokens[0];
    if (tokens.size() == 1)
        return;
    defines = std::set<std::string>(tokens.begin() + 1, tokens.end());
}
Shader::~Shader()
{
    if (id != -1)
        glDeleteShader(id);
}
std::string Shader::uri() const
{
    return path + "," + merge(defines, ',');
}
void Shader::compile()
{
    std::string code;
    std::vector<std::string> file_names;
    preprocessor(path, code, file_names);
    compile(code, &file_names);
}
void Shader::preprocessor(const std::string& path, std::string& code, std::vector<std::string>& file_names)
{
    int line_id = 1;
    int file_id = file_names.size();
    file_names.push_back(path);
    if (file_id == 0)
    {
        code += "#version " + std::to_string(((OpenglAPI*)GraphicsAPI::instance.get())->language_version) + " " + ((OpenglAPI*)GraphicsAPI::instance.get())->version_profile + "\n";
        for (const auto& define : defines) 
        {
            code += "#define " + define + "\n";
        }
    }
    code += "#line " + std::to_string(line_id) + " " + std::to_string(file_id) + "\n";
    for (const auto& line : split(read_file(path), '\n')) 
    {
        if (line.rfind("#include", 0) == 0) 
        {
            size_t first = line.find('\"');
            size_t second = line.find('\"', first + 1);
            if (first == std::string::npos || second == std::string::npos) continue;
            preprocessor(path.substr(0, path.find_last_of("/")) + "/" + line.substr(first+1, second-first-1), code, file_names);
            line_id++;
            code += "#line " + std::to_string(line_id) + " " + std::to_string(file_id) + "\n";
        }
        else 
        {
            line_id++;
            code += line + '\n';
        }
    }
}
void Shader::compile(const std::string& code, std::vector<std::string>* files)
{
    GLchar *cstr = (GLchar *)code.c_str();
    GLint len = code.size();
    glShaderSource(id, 1, &cstr, &len);
    glCompileShader(id);

    int succ;
    char info[1024];
    glGetShaderiv(id, GL_COMPILE_STATUS, &succ);
    if (!succ)
    {
        glGetShaderInfoLog(id, 1024, NULL, info);
        glDeleteShader(id);
        id = -1;
        std::cout << "failed to compile " << path << std::endl;
        #ifdef WIN_OS
        std::regex err(R"(^\s*(\d+)\((\d+)\)\s*:\s*error\s*(.*))");
        #else
        std::regex err(R"(ERROR:\s*(\d+):(\d+):\s*(.*))");
        #endif
        std::smatch match;
        std::string log = info;
        while (std::regex_search(log, match, err)) 
        {
            int file_id = std::stoi(match[1].str());
            int line_id = std::stoi(match[2].str());
            std::string err_msg = match[3].str();
            std::string name = files ? (*files)[file_id] : "";
            std::cout << "ERROR: " << name << ":" << line_id << ": " << err_msg << std::endl;
            log = match.suffix().str();
        }
        
    }
}