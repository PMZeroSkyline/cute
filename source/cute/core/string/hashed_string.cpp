#include "hashed_string.h"

HashedString::HashedString(const std::string& _str)
{
    size_t h = std::hash<std::string>{}(_str);
    ids[h] = _str;
    id = h;
    str = &ids[h];
}
HashedString::HashedString(char* _str) : HashedString(std::string(_str)){}
bool HashedString::operator==(const HashedString& other) const
{
    return id == other.id;
}
template struct std::hash<HashedString>;