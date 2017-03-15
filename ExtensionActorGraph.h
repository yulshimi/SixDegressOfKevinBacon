//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The header file of "ExtensionActorGraph.cpp". This checkes whether all vertices in a file are connected or not.
//Assignment#: PA4
#ifndef EXTENSION_ACTORGRAPH_H
#define EXTENSION_ACTORGRAPH_H
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
using namespace std;

class Node
{
public:
  Node();
  Node(string actor_name, string movie_title, int movie_year);
  bool isItDeleted;
  string actorName;
  vector<string> movieList;
  vector<int> yearList;
  vector<Node*> adjacentList;
  bool isItVisited; 
  unsigned int dist;
  Node* prev;
  bool operator<(const Node& other);
  int groupNumber;
};

class NodePtrComp
{
public:
  bool operator()(Node*& lhs, Node*& rhs) const
  {
    return *lhs < *rhs;
  }
};

class ActorGraph 
{
private:
  vector<Node*> listOfActors;
  vector<Node*> listOfStartNode;
public:
  vector<string> tempVector;
  ActorGraph(void);
  ~ActorGraph();
  bool loadFromFile(const char* in_filename, bool use_weighted_edges);
  void deleteAll(Node* nodePtr);
  void makeAllUnvisited(Node* startPoint);
  Node* getNodePtr(string actor_name);
  bool insert(string actor_name, string movie_title, int movie_year);
  void createActorGraph();
  bool doTheyShareMovie(Node* actor_one, Node* actor_two);
  void connectTwoActors(Node* actor_one, Node* actor_two);
  void makeIndexEqual(Node* actorPtr, int index);
  void createListOfActors(string actor_name, string movie_title, int movie_year);
  void updateListOfStartNode();
  int getNumOfGraphs() const;
  void initialize(Node* nodePtr);
  pair<string, int> getSharedMovie(Node* actor_one, Node* actor_two); 
  pair<vector<string>, vector<int>> sharedMovieList(Node* actor_one, Node* actor_two) const;
  pair<stack<string>, stack<string> > findTheShortestPath(string actor_one, string actor_two);  
private:
  int m_currGroupNumber; 
};
#endif // ACTORGRAPH_H
