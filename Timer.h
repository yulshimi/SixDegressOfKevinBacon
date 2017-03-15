//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: This is the header file of "Timer.cpp"
//Assignment#: PA4
#ifndef TIMER_H
#define TIMER_H
#include <chrono>
class Timer
{
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:

  void begin_timer();
  long long end_timer();
};
#endif
