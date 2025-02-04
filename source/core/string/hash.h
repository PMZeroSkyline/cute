#ifndef HASH_H
#define HASH_H

#include <string>

void encrypt_decrypt(std::string &input, const std::string &key);
size_t mul31(const std::string& input);

#endif