#pragma once
#include <string>

#define MAX_HASH_CHARS 12
#define BITS_PER_CHAR 5
#define HASH_CHAR_OFFSET 65


typedef uint64_t HashValue;
HashValue constexpr StringHash(const char * str);