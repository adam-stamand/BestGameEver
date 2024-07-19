#pragma once

#include <stdint.h>
#include "Globals/Globals.h"

class RateLimiter
{
public:
	RateLimiter(uint32_t ticks);
	~RateLimiter();
	
	void SetLimit(uint32_t ticks);
	bool Check();

private:
	uint32_t prevTicks = 0;
	uint32_t tickLimit = 0;
};

