//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The header file of "ActorYear.cpp". This class contains a list of movie based on year.
//Assignment#: PA4
#ifndef ACTORYEAR_H
#define ACTORYEAR_H
#include <unordered_set>
#include <string>
class Year
{
public:
  Year();
  Year(unsigned year);
  unsigned int m_year;
  std::unordered_set<std::string> m_edge_list;
  bool operator<(const Year& other);
};
#endif
