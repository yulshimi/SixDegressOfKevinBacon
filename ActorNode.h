//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The header file of "ActorNode.cpp"
//Assignment#: PA4
#ifndef ACTORNODE_H
#define ACTORNODE_H
#include <string>
#include <unordered_set>
class Node
{
public:
  Node();
  Node(std::string actor_name);
  std::string m_actor_name;
  std::string prev_movie;
  unsigned int weight;
  Node* prev;
  std::unordered_set<std::string> m_movie_list;
  bool isItVisited;
  bool operator<(const Node& other);
  std::string sentinel;
  unsigned int m_size;
};
#endif
