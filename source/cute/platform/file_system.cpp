#include "file_system.h"

std::string read_file(const std::string& filename) 
{
    FILE* file = fopen(filename.c_str(), "rb");
    if (!file) 
    {
        std::cout << "failed opening file: " << filename << std::endl;
        return "";
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    std::string content(file_size, '\0');
    fread(&content[0], 1, file_size, file);

    fclose(file);
    return content;
}