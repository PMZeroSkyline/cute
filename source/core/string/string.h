#ifndef STRING_H
#define STRING_H

#include <vector>
#include <set>
#include <string>
#include <sstream>

template <typename T>
std::string merge(const T& tokens, char delim)
{
    std::string result;
    for (const auto& token : tokens) {
        if (result.size() != 0) {
            result += delim;
        }
        result += token;
    }
    return result;
}
std::vector<std::string> split(const std::string &s, char delim);
bool replace(std::string& str, const std::string& search, const std::string& replacement);

#endif