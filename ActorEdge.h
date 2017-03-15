//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The header file of "ActorEdge.cpp"
//Assignment#: PA4
#ifndef ACTOR_EDGE_H
#define ACTOR_EDGE_H
#include <string>
#include <unordered_set>
class Edge
{
public:
  Edge();
  Edge(std::string movie_name, int year);
  std::string m_movie_name;
  unsigned int m_year;
  std::unordered_set<std::string> m_actor_list; 
};
#endif
