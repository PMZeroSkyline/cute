#include "hash.h"

void encrypt_decrypt(std::string &input, const std::string &key) 
{
    for (size_t i = 0; i < input.size(); ++i) 
    {
        input[i] = input[i] ^ key[i % key.size()];
    }
}
size_t mul31(const std::string& input) 
{
    size_t hash = 0;
    for (char c : input) {
        hash = hash * 31 + static_cast<unsigned int>(c);
    }
    return hash;
}