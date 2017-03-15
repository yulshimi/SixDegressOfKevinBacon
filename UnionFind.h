//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The header file of "UnionFind.cpp"
//Assignment#: PA4
#ifndef UNIONFIND_H
#define UNIONFIND_H
#include "ActorNode.h"
#include "ActorEdge.h"
#include "ActorYear.h"
#include "ActorGraph.h"
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <string>
#include <sstream>
class DisjointSet
{
public:
  DisjointSet();
  bool loadFromFile(const char* in_filename, std::ostream& outs);
  void createActorConnectionGraph(std::string actor_name, std::string movie_name, int year);
  void createPriorityQueue();
  void printOutConnectedYear(std::ostream& outs) const;
  void destroy();
  void disjointSet();
  bool disjointSetUnion(std::string actor_one_name, std::string actor_two_name);
  Node* disjointSetFind(Node* child);
  bool connectivity(std::string actor_one_name, std::string actor_two_name);
  ~DisjointSet();
private:
  std::unordered_set<std::string>::iterator year_set_it;
  std::unordered_set<std::string>::iterator actor_set_it;
  std::unordered_set<std::string>::iterator movie_set_it;
  std::unordered_map<std::string, Node*>::iterator actor_it;
  std::unordered_map<std::string, Edge*>::iterator movie_it;
  std::unordered_map<unsigned int, Year*>::iterator year_it;
  std::unordered_map<std::string, Node*> m_actor_list;
  std::unordered_map<std::string, Edge*> m_movie_list;
  std::unordered_map<unsigned int, Year*> m_year_list;
  std::vector<Node*> m_visited_node;
  std::vector<actorPair> m_pair_list;
  Node* m_start_point;
  int m_numOfInvalid;
  std::priority_queue<Year*, std::vector<Year*>, YearPtrComp> m_priority_queue;
};
#endif
