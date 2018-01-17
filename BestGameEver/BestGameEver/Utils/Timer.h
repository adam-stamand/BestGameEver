#pragma once
#include <stdint.h>

class Timer {
public:
  static uint32_t GetTime();
	static void IncrTimer();
	
private:
	static uint32_t globalTime;
	};