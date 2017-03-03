#include "ActorGraph.h"
#include <iostream>
#include <stack>
using namespace std;
int main(int argc, char* argv[])
{
  if(argc != 5)
  {
    cout << "Wrong number of command line argument" << endl;
    return 0;
  }
  ActorGraph myGraph;
  myGraph.loadFromFile(argv[1], true);
  myGraph.createActorGraph();
/*
  for(int i=0; i < myGraph.listOfStartNode.size(); ++i)
  {
    cout << myGraph.listOfStartNode[i] << endl;
  }
  stack<Node*> myStack;
  Node* nodePtr = myGraph.listOfStartNode[0];
  myGraph.makeAllUnvisited(nodePtr);
  myStack.push(nodePtr);
  nodePtr->isItVisited = true;
  bool allVisited = true;
  while(!myStack.empty())
  {
    nodePtr = myStack.top();
    allVisited = true;
    for(int i=0; i < nodePtr->adjacentList.size(); ++i)
    {
      if(nodePtr->adjacentList[i]->isItVisited == false)
      {
        allVisited = false;
        nodePtr = nodePtr->adjacentList[i];
        nodePtr->isItVisited = true;
        myStack.push(nodePtr);  
      }
    }
    if(allVisited == true)
    {
      cout << nodePtr->actorName << endl;
      for(int j=0; j < nodePtr->adjacentList.size(); ++j)
      {
        cout << "Adjacent of " << nodePtr->actorName << ", " << nodePtr->adjacentList[j]->actorName << endl;
      }
      for(int j=0; j < nodePtr->movieList.size(); ++j)
      {
        cout << "MovieList of " << nodePtr->actorName << ", " << nodePtr->movieList[j] << nodePtr->yearList[j] << endl;
      }
      myStack.pop();
    }
  }
*/
  ofstream out_stream;
  out_stream.open(argv[4]);
  myGraph.loadFromFile(argv[3], true);
  out_stream << "(actor)--[movie#@year]-->(actor)--..." << endl;
  for(int i=0; i < myGraph.tempVector.size(); ++i)
  {
    pair<stack<string>, stack<string> > pairStack;
    pairStack = myGraph.findTheShortestPath(myGraph.tempVector[i], myGraph.tempVector[i+1]);
    if(pairStack.first.empty())
    {
      out_stream << "NO PATH" << endl;
    }
    while(!pairStack.first.empty())
    {
      string actor_name = pairStack.first.top();
      out_stream << "(" << actor_name << ")";
      pairStack.first.pop();
      if(!pairStack.second.empty())
      {
        string movieName = pairStack.second.top();
        out_stream << "--[" << movieName << "]-->";
        pairStack.second.pop();
      }
    }
    ++i;
    out_stream << endl;
  }
 
  return 0;
}
