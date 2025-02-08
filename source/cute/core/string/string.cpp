#include "string.h"
#include <set>
#include <sstream>

template std::string merge<std::vector<std::string>>(const std::vector<std::string>& tokens, char delim);
template std::string merge<std::set<std::string>>(const std::set<std::string>& tokens, char delim);

std::vector<std::string> split(const std::string &s, char delim) 
{
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}
bool replace(std::string& str, const std::string& search, const std::string& replacement) 
{
    size_t pos = str.find(search);
    if (pos != std::string::npos) 
    {
        str.replace(pos, search.length(), replacement);
        return true;
    }
    return false;
}
void replace_all(std::string& str, const std::string& search, const std::string& replacement) 
{
    while (replace(str, search, replacement)) {}
}
void encrypt_decrypt(std::string &input, const std::string &key) 
{
    for (size_t i = 0; i < input.size(); ++i) 
    {
        input[i] = input[i] ^ key[i % key.size()];
    }
}
size_t md31(const std::string& input) 
{
    size_t hash = 0;
    for (char c : input) {
        hash = hash * 31 + static_cast<unsigned int>(c);
    }
    return hash;
}