#ifndef HASHED_STRING_H
#define HASHED_STRING_H

#include <string>
#include <unordered_map>
#include <memory>

struct HashedString
{
    size_t id = 0;
    std::string* str = nullptr;

    static inline std::unordered_map<size_t, std::string> ids = std::unordered_map<size_t, std::string>();
    HashedString() = default;
    HashedString(const std::string& _str);
    HashedString(char* _str);

    bool operator==(const HashedString& other) const;
};
template <>
struct std::hash<HashedString> {
    std::size_t operator()(const HashedString& s) const {
        return s.id;
    }
};
#endif