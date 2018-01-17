#include "Utils/Timer.h"

uint32_t Timer::globalTime = 0;

uint32_t Timer::GetTime()			{ return Timer::globalTime; }
void Timer::IncrTimer()				{ Timer::globalTime++; }

