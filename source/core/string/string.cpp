#include "string.h"

template std::string merge<std::vector<std::string>>(const std::vector<std::string>& tokens, char delim);
template std::string merge<std::set<std::string>>(const std::set<std::string>& tokens, char delim);
