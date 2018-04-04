//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The header file of "ActorGraph.cpp"
//Assignment#: PA4
#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H
#include "ActorNode.h"
#include "ActorEdge.h"
#include "ActorYear.h"
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <string>
#include <sstream>
class NodePtrComp
{
public:
  bool operator()(Node*& lhs, Node*& rhs) const
  {
    return *lhs < *rhs;
  }
};

class YearPtrComp
{
public:
  bool operator()(Year*& lhs, Year*& rhs) const
  {
    return *lhs < *rhs;
  }
};

class actorPair
{
public:
  actorPair()
  {
    connect = false;
    connected_year = 9999;  
  }
  std::string actor_one;
  std::string actor_two;
  unsigned int connected_year;
  bool connect;
};

class ActorGraph
{
public:
  ActorGraph();
  bool loadFromFile(const char* in_filename, std::ostream& outs);
  bool loadFromFile(const char* in_filename, std::ostream& outs, bool use_weighted_edges);
  bool findTheShortestPath(std::string actor_one_name, std::string actor_two_name);
  bool dijkstraAlgorithm(std::string actor_one_name, std::string actor_two_name);
  void makeAllUnvisited();
  void createGraph(std::string actor_name, std::string movie_name, int year);
  void createActorConnectionGraph(std::string actor_name, std::string movie_name, int year);
  void createPriorityQueue();
  void printOutThePath(Node* startPoint, std::ostream& outs) const;
  void printOutConnectedYear(std::ostream& outs) const;
  bool areTheyConnected(std::string actor_one_name, std::string actor_two_name);
  void actorConnection();
  void destroy();
  ~ActorGraph();
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
