//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The implementation of "ActorYear.h"
//Assignment#: PA4
#include "ActorYear.h"
using namespace std;
Year::Year()
{
  m_year = 0;
}

Year::Year(unsigned int year)
{
  m_year = year;
}

bool Year::operator<(const Year& other)
{
  return m_year > other.m_year;
}
