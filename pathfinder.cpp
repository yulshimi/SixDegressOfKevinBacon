//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: This is to find the shortest path based on distance or weight between two actors.
//Assignment#: PA4
#include "ActorGraph.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int main(int argc, char* argv[])
{
  if(argc != 5)
  {
    cout << "Wrong number of command line argument" << endl;
    return 0;
  }
  ActorGraph myGraph;
  myGraph.loadFromFile(argv[1], cout, true); //The graph is created here
  ofstream out_stream;
  out_stream.open(argv[4]);
  out_stream << "(actor)--[movie#@year]-->(actor)--..." << endl;
  if(strcmp(argv[2], "u") == 0)
  {
    myGraph.loadFromFile(argv[3], out_stream, false);
  }
  else
  {
    myGraph.loadFromFile(argv[3], out_stream, true);
  }
  return 0;
}
