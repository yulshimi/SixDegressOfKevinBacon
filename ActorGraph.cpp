/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"
using namespace std;

Node::Node()
{
  actorName = "";
  isItVisited = false;
  prev = "";
  dist = -1;  
}

Node::Node(string actor_name, string movie_title, int movie_year)
{
  actorName = actor_name;
  movieList.push_back(movie_title);
  yearList.push_back(movie_year);
  isItVisited = false;
  dist = -1;
  prev = "";
}

ActorGraph::ActorGraph(void)
{
  m_startNode = nullptr;
  m_size = 0;
}

bool ActorGraph::isItEmpty() const
{
  return m_size == 0;
}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) 
{
  // Initialize the file stream
  ifstream infile(in_filename);

  bool have_header = false;
  
  // keep reading lines until the end of file is reached
  while (infile) 
  {
    string s;
    
    // get the next line
    if (!getline( infile, s ))
    { 
      break;
    }

    if (!have_header) 
    {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss) 
    {
      string next;
      
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' ))
      { 
        break;
      }
      record.push_back( next );
    }
    
    if (record.size() != 3) 
    {
      // we should have exactly 3 columns
      continue;
    }

    string actor_name(record[0]);
    string movie_title(record[1]);
    int  movie_year = stoi(record[2]);
    // we have an actor/movie relationship, now what?
    insert(actor_name, movie_title, movie_year);
  }

  if (!infile.eof()) 
  {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();

  return true;
}

bool ActorGraph::insert(string actor_name, string movie_title, int movie_year)
{
  if(isEmpty())
  {
    Node* newNode = new Node(actor_name, movie_title, movie_year);
    m_startNode = newNode;
    return true;
  }
  Node* searchPtr = getNodePtr(actor_name);
  if(searchPtr != nullptr)
  {
    searchPtr->movieList.push_back(movie_title);
    searchPtr->yearList.push_back(movie_year);
    updateAdjacentList(false, searchPtr, movie_title, movie_year);
  }
  else
  {
    Node* newNode = new Node(actor_name, movie_title, movie_year);
    searchPtr = newNode;
    updatedAdjacentList(true, searchPtr, movie_title, movie_year);
    ++m_size;
  }
  return true;  
}

void ActorGraph::updateAdjacentList(bool fromEmpty, Node* currNode, string movie_title, int movie_year)
{
  Node* searchPtr;
  if(fromEmpty)
  {
    searchPtr = m_startNode;
  }
  else
  {
    searchPtr = currNode;
  }
  stack<Node*> myStack;
  bool allVisited;
  searchPtr->isItVisited = true;
  myStack.push(searchPtr)
  while(!myStack.empty())
  {
    searchPtr = myStack.top();
    if(searchPtr != currNode)
    {
      for(int i=0; i < searchPtr->movieList.size(); ++i)
      {
        if(searchPtr->movieList[i] == movie_title && searchPtr->yearList[i] == movie_year)
        {
          currNode->adjacentList.push_back(searchPtr);
          searchPtr->adjacentList.push_back(currNode);
        }
      }
    }
    allVisited = true;
    for(int i=0; i < searchPtr->adjacentList.size(); ++i)
    {
      if(searchPtr->adjacentList[i]->isItVisited == false)
      {
        allVisited = false;
        searchPtr = searchPtr->adjacentList[i];
        break;
      }
    }
    if(allVisited == true)
    {
      myStack.pop();
    }
    else
    {
      searchPtr->isItVisited = true;
      myStack.push(searchPtr);   
    }  
  }
  makeAllUnvisited(); 
}

Node* ActorGraph::getNodePtr(string actor_name) const
{
  bool allVisited;
  Node* nodePtr = m_startNode;
  stack<Node*> myStack;
  myStack.push(nodePtr);
  nodePtr->isItVisited = true;
  while(!myStack.empty())
  {
    nodePtr = myStack.top();
    if(nodePtr->actorName == actor_name)
    {
      makeAllUnvisited();
      return nodePtr;
    }
    allVisited = true;
    for(int i=0; i < nodePtr->adjacentList.size(); ++i)
    {
      if(nodePtr->adjacentList[i]->isItVisited == false)
      {
        allVisited = false;
        nodePtr = nodePtr->adjacentList[i];
        break;
      }
    }
    if(allVisited == true)
    {
      myStack.pop();
    }
    else
    {
      nodePtr->isItVisited = true;
      myStack.push(nodePtr);
    }
  }
  makeAllUnvisited();
  return nullptr;  
}

void ActorGraph::makeAllUnvisited()
{
  bool allVisited;
  Node* searchPtr = m_startNode;
  stack<Node*> myStack;
  myStack.push(searchPtr);
  while(!myStack.empty())
  {
    searchPtr = myStack.top();
    if(searchPtr->isItVisited == true)
    {
      searchPtr->isItVisited = false;
    }
    allVisited = true;
    for(int i=0; i < searchPtr->adjacentList.size(); ++i)
    {
      if(searchPtr->adjacentList[i]->isItVisited == true)
      {
        allVisited = false;
        searchPtr = searchPtr->adjacentList[i];
        break;
      }
    }
    if(allVisited == true)
    {
      myStack.pop();
    }
    else
    {
      myStack.push(searchPtr);
    }
  }
}

bool ActorGraph::unweightedBFS() const
{
  if(isItEmpty())
  {
    return false;
  }
  queue<Node*> myQueue;
  Node* searchPtr = m_startNode; 
  searchPtr->dist = 0;
  myQueue.push(searchPtr)
  while(!myQueue.empty())
  {
    searchPtr = myQueue.top();
    for(int i=0; i < searchPtr->adjacentList.size(); ++i)
    {
      if(searchPtr->dist + 1 < searchPtr->adjacentList[i]->dist)
      {
        searchPtr->adjacentList[i]->dist = searchPtr->dist + 1;
        searchPtr->adjacentList[i]->prev = searchPtr->actorName;
        myQueue.push(searchPtr->adjacentList[i]);
      }
    }
    myQueue.pop();
  }
  return true; 
}

void ActorGraph::deleteAll(Node* nodePtr)
{
  nodePtr->isItVisited = true;
  for(int i=0; i < nodePtr->adjacentList.size(); ++i)
  {
    if(nodePtr->adjacentList[i]->isItVisited == false)
    {
      deleteAll(nodePtr->adjacentList[i]);
    }
  }
  delete nodePtr;
}

ActorGraph::~ActorGraph()
{
  deleteAll(m_startNode);
  m_size = 0;
  m_startNode = nullptr;
}













































 
