#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <stdio.h>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

std::string read_file(const std::string& filename);

#endif