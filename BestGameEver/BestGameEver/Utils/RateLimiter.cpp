#include "RateLimiter.h"



RateLimiter::RateLimiter(uint32_t ticks)
{
	this->tickLimit = ticks;
}


RateLimiter::~RateLimiter()
{
}


void RateLimiter::SetLimit(uint32_t ticks) {
	this->tickLimit = ticks;
}


bool RateLimiter::Check() {
	uint32_t timeDiff = Globals::GetTimer() - this->prevTicks;
	
	// Handle Wrap around of globalTimer
	if (timeDiff <= 0) {
		this->prevTicks = 0;
	}

	if (timeDiff > this->tickLimit) {
		this->prevTicks = Globals::GetTimer();
		return true;
	}

	return false;
}