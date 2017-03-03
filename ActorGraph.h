/*
 * ActorGraph.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
// Maybe include some data structures here

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
protected:
  vector<Node*> listOfActors;
  vector<Node*> listOfStartNode;
public:
  vector<string> tempVector;
  ActorGraph(void);
  ~ActorGraph();
  // Maybe add some more methods here
  
  /** You can modify this method definition as you wish
   *
   * Load the graph from a tab-delimited file of actor->movie relationships.
   *
   * in_filename - input filename
   * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
   *
   * return true if file was loaded sucessfully, false otherwise
   */
  bool loadFromFile(const char* in_filename, bool use_weighted_edges);
  //bool unweightedBFS() const;
  void deleteAll(Node* nodePtr);
  void makeAllUnvisited(Node* startPoint);
  Node* getNodePtr(string actor_name);
  //void updateAdjacentList(bool fromEmpty, Node* currNode, string movie_title, int movie_year);
  bool insert(string actor_name, string movie_title, int movie_year);
  void createActorGraph();
  bool doTheyShareMovie(Node* actor_one, Node* actor_two);
  void connectTwoActors(Node* actor_one, Node* actor_two);
  void makeIndexEqual(Node* actorPtr, int index);
  void createListOfActors(string actor_name, string movie_title, int movie_year);
  void updateListOfStartNode();
  void initialize(Node* nodePtr);
  pair<string, int> getSharedMovie(Node* actor_one, Node* actor_two); 
  pair<vector<string>, vector<int>> sharedMovieList(Node* actor_one, Node* actor_two) const;
  pair<stack<string>, stack<string> > findTheShortestPath(string actor_one, string actor_two);  
private:
  int m_currGroupNumber; 
};


#endif // ACTORGRAPH_H
