//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: This is the extension. This is to check whether some graph is connected or not and print a result out.
//Assignment#: PA4
#include "ExtensionActorGraph.h"
using namespace std;
int main (int argc, char* argv[])
{
  if(argc != 2)
  {
    cout << "The number of argument must be 2" << endl;
  }
  ActorGraph myGraph;
  myGraph.loadFromFile(argv[1], true);
  myGraph.createActorGraph();
  if(myGraph.getNumOfGraphs() > 1)
  {
    cout << "Entire nodes are not connected!" << endl;
  }
  else
  {
    cout << "This is a connected graph!" << endl;
  }
  return 0;
}
