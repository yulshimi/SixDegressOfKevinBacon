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
// Maybe include some data structures here

using namespace std;
class Node
{
public:
  Node();
  Node(string actor_name, string movie_title, int movie_year);
  string actorName;
  vector<string> movieList;
  vector<int> yearList;
  vector<Node*> adjacentList;
  bool isItVisited; 
  unsigned int dist;
  string prev;
};
class ActorGraph 
{
protected:
  
    // Maybe add class data structure(s) here

public:
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
  bool unweightedBFS() const;
  void deleteAll(Node* nodePtr);
  void makeAllUnvisited();
  Node* getNodePtr(string actor_name) const;
  void updateAdjacentList(bool fromEmpty, Node* currNode, string movie_title, int movie_year);
  bool insert(string actor_name, string movie_title, int movie_year);
  bool isItEmpty() const;  
private:
  int m_size; 
  Node* m_startNode; 
};


#endif // ACTORGRAPH_H
