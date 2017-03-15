//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: This program is to find when specific two actors are connected for the first time and print it out to an output file.
//Assignment#: PA4
#include "ActorGraph.h"
#include "Timer.h"
#include <fstream>
#include <iostream>
#include <string>
#include "UnionFind.h"
#include <cstring>
using namespace std;
int main (int argc, char* argv[])
{
  //long long time; //all codes related to Timer are commented out
  //Timer myTimer;
  if(argc < 4 || argc > 5)
  {
    cout << "wrong argument" << endl;
    return 0;
  }
  ofstream out_stream;
  out_stream.open(argv[3]);
  if(strcmp(argv[4], "bfs") == 0)
  {
    ActorGraph myGraph;
    myGraph.loadFromFile(argv[1], cout);
    myGraph.loadFromFile(argv[2], cout);
    myGraph.createPriorityQueue();
    //myTimer.begin_timer();
    myGraph.actorConnection();
    //time = myTimer.end_timer();
    //cout << "bfs: " << time << "nanoseconds" << endl;
    out_stream << "Actor1\t" << "Actor2\t" << "Year\n";
    myGraph.printOutConnectedYear(out_stream);
    out_stream.close();  
  }
  else
  {
    DisjointSet mySet;
    mySet.loadFromFile(argv[1], cout);
    mySet.loadFromFile(argv[2], cout);
    mySet.createPriorityQueue();
    //myTimer.begin_timer();
    mySet.disjointSet();
    //time = myTimer.end_timer();
    //cout << "ufind: " << time << "nanoseconds" << endl;
    out_stream << "Actor1\t" << "Actor2\t" << "Year\n";
    mySet.printOutConnectedYear(out_stream);
    out_stream.close();
  } 
  return 0;
}
