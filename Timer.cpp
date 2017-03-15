//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The implementation of "Timer.cpp"
//Assignment#: PA4
#include "Timer.h"
void Timer::begin_timer() 
{
  start = std::chrono::high_resolution_clock::now();
}

long long Timer::end_timer() 
{
  std::chrono::time_point<std::chrono::high_resolution_clock> end;
  end = std::chrono::high_resolution_clock::now();
  return (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
}

