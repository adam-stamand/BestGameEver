#include "Utils/StringHash.h"


HashValue constexpr StringHash(const char * str) {
	HashValue result = 0x00;
	for (int i = 0; i < MAX_HASH_CHARS; i++) {
		result |= (str[i] - HASH_CHAR_OFFSET) << (i * BITS_PER_CHAR);
	}
	return result;
}