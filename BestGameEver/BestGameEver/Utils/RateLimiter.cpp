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
	// Handle Wrap around of globalTimer
	if ((Globals::GetTimer() - this->prevTicks) <= 0) {
		this->prevTicks = 0;
	}

	if ((Globals::GetTimer() - this->prevTicks) > this->tickLimit) {
		this->prevTicks = Globals::GetTimer();
		return true;
	}

	return false;
}