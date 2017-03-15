//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The implementation of "ExtensionActorGraph.cpp"
//Assignment#: PA4
#include "ExtensionActorGraph.h"
using namespace std;

Node::Node()
{
  actorName = "";
  isItVisited = false;
  prev = nullptr;
  dist = -1;
  groupNumber = -1;
  isItDeleted = true;  
}

Node::Node(string actor_name, string movie_title, int movie_year)
{
  actorName = actor_name;
  movieList.push_back(movie_title);
  yearList.push_back(movie_year);
  isItVisited = false;
  dist = -1;
  prev = nullptr;
  groupNumber = -1;
  isItDeleted = true;
}

bool Node::operator<(const Node& other)
{
  if(dist != other.dist)
  {
    return dist > other.dist;
  }
  return actorName < other.actorName;
}

ActorGraph::ActorGraph(void)
{
  m_currGroupNumber = 0;  
}

int ActorGraph::getNumOfGraphs() const
{
  return listOfStartNode.size();
}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) 
{
  ifstream infile(in_filename);
  bool have_header = false;
  while (infile) 
  {
    string s;
    if (!getline( infile, s ))
    { 
      break;
    }

    if (!have_header) 
    {
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss) 
    {
      string next;
      if (!getline( ss, next, '\t' ))
      { 
        break;
      }
      record.push_back( next );
    }
    
    if (record.size() != 3) 
    {
       tempVector.push_back(record[0]);
       tempVector.push_back(record[1]);
    }
    else
    {
      string actor_name(record[0]);
      string movie_title(record[1]);
      int  movie_year = stoi(record[2]);
      createListOfActors(actor_name, movie_title, movie_year);
    }
  }


  if (!infile.eof()) 
  {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }

  infile.close();

  return true;
}

void ActorGraph::createActorGraph()
{
  int index = 0;
  int x=0;
  while(0 < listOfActors.size())
  {
    index = listOfActors.size() - 1;
    for(int i = index - 1; i >= 0; --i)
    {
      if(doTheyShareMovie(listOfActors[index], listOfActors[i]) == true)
      {
        connectTwoActors(listOfActors[index], listOfActors[i]);
      }
    }
    listOfActors.pop_back();  
  }
  updateListOfStartNode();  
}

bool ActorGraph::doTheyShareMovie(Node* actor_one, Node* actor_two)
{
  for(int i=0; i < actor_one->movieList.size(); ++i)
  {
    for(int j=0; j < actor_two->movieList.size(); ++j)
    {
      if(actor_one->movieList[i] == actor_two->movieList[j] && actor_one->yearList[i] == actor_two->yearList[j])
      {
        return true;
      }
    }
  }
  return false;
}
//This method connects two actors if there is a path. If they do not have a path, they are not connected and given different group numbers.
void ActorGraph::connectTwoActors(Node* actor_one, Node* actor_two)
{
  int group_number_one = actor_one->groupNumber;
  int group_number_two = actor_two->groupNumber;
  if(group_number_one != -1 && group_number_two != -1)
  {
    if(group_number_one < group_number_two)
    {
      makeIndexEqual(actor_two, actor_one->groupNumber);
    }
    else if(group_number_two < group_number_one)
    {
      makeIndexEqual(actor_one, actor_two->groupNumber);
    }
    else
    {
    }
  }
  else if(group_number_one == -1 && group_number_two == -1)
  {
    actor_one->groupNumber = m_currGroupNumber;
    actor_two->groupNumber = m_currGroupNumber;
    ++m_currGroupNumber;
    listOfStartNode.push_back(actor_one);  
  }
  else
  {
    if(group_number_one != -1 && group_number_two == -1)
    {
      actor_two->groupNumber = actor_one->groupNumber;  
    }
    else 
    {
      actor_one->groupNumber = actor_two->groupNumber;
    }
  }
  actor_one->adjacentList.push_back(actor_two);
  actor_two->adjacentList.push_back(actor_one);
}

void ActorGraph::makeIndexEqual(Node* actorPtr, int index)
{
  bool allClear = true;
  stack<Node*> myStack;
  Node* searchPtr = actorPtr;
  searchPtr->groupNumber = index;
  myStack.push(searchPtr);
  while(!myStack.empty())
  {
    allClear = true;
    searchPtr = myStack.top();
    for(int i=0; i < searchPtr->adjacentList.size(); ++i)
    {
      if(searchPtr->adjacentList[i]->groupNumber != index)
      {
        searchPtr->adjacentList[i]->groupNumber = index;
        allClear = false;
        myStack.push(searchPtr->adjacentList[i]);  
      }
    }
    if(allClear == true)
    {
      myStack.pop();
    }
  }  
}

void ActorGraph::createListOfActors(string actor_name, string movie_title, int movie_year)
{
  bool exist = false;
  for(int i=0; i < listOfActors.size(); ++i)
  {
    if(listOfActors[i]->actorName == actor_name)
    {
      exist = true;
      listOfActors[i]->movieList.push_back(movie_title);
      listOfActors[i]->yearList.push_back(movie_year);
      break;  
    }
  }
  
  if(exist == false)
  {
    Node* newNode = new Node(actor_name, movie_title, movie_year);
    listOfActors.push_back(newNode);
  }
}

void ActorGraph::updateListOfStartNode()
{
  vector<Node*> neo_list;
  neo_list.push_back(listOfStartNode[0]);
  bool sameExist = false;
  for(int i=1; i < listOfStartNode.size(); ++i)
  {
    sameExist = false;
    for(int j=0; j < neo_list.size(); ++j)
    {
      if(listOfStartNode[i]->groupNumber == neo_list[j]->groupNumber)
      {
        sameExist = true;
        break;
      }
    }
    if(sameExist == false)
    {
      neo_list.push_back(listOfStartNode[i]);
    }
  }
  listOfStartNode.clear();
  listOfStartNode = neo_list;   

}
pair<vector<string>, vector<int>> ActorGraph::sharedMovieList(Node* actor_one, Node* actor_two) const
{
  pair<vector<string>, vector<int> > myPair;
  vector<string> myVector_one;
  vector<int> myVector_two; 
  for(int i=0; i < actor_one->movieList.size(); ++i)
  {
    for(int j=0; j < actor_two->movieList.size(); ++j)
    {
      if(actor_one->movieList[i] == actor_two->movieList[j] && actor_one->yearList[i] == actor_two->yearList[j])
      {
        myVector_one.push_back(actor_one->movieList[i]);
        myVector_two.push_back(actor_two->yearList[i]);    
      }
    }
  }
  myPair.first = myVector_one;
  myPair.second = myVector_two;
  return myPair;  
}

Node* ActorGraph::getNodePtr(string actor_name) 
{
  bool allVisited;
  Node* nodePtr = nullptr;
  stack<Node*> myStack;
  for(int i=0; i < listOfStartNode.size(); ++i)
  {
    nodePtr = listOfStartNode[i];
    makeAllUnvisited(nodePtr);
    myStack.push(nodePtr);
    nodePtr->isItVisited = true;
    while(!myStack.empty())
    {
      nodePtr = myStack.top();

      if(nodePtr->actorName == actor_name)
      {
        return nodePtr;
      }

      allVisited = true;
      for(int j=0; j < nodePtr->adjacentList.size(); ++j)
      {
        if(nodePtr->adjacentList[j]->isItVisited == false)
        {
          allVisited = false;
          nodePtr = nodePtr->adjacentList[j];
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
  }
  return nullptr;  
}

void ActorGraph::makeAllUnvisited(Node* startPoint)
{
  bool allVisited;
  Node* searchPtr = startPoint;
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

pair<stack<string>, stack<string> > ActorGraph::findTheShortestPath(string actor_one, string actor_two) 
{
  priority_queue<Node*, vector<Node*>, NodePtrComp>  myQueue;
  Node* startPoint = getNodePtr(actor_one);
  Node* endPoint = getNodePtr(actor_two);
  stack<string> actor_name_stack;
  stack<string> movie_title_stack;
  pair<stack<string>, stack<string> > stack_pair;
  if(startPoint == nullptr || endPoint == nullptr)
  {
    return stack_pair;
  }
  if(startPoint->groupNumber != endPoint->groupNumber)
  {
    return stack_pair;
  }
  Node* searchPtr = startPoint;
  searchPtr->dist = 0;
  myQueue.push(searchPtr);
  while(!myQueue.empty())
  {
    searchPtr = myQueue.top();
    myQueue.pop();  
    if(searchPtr == endPoint)
    {
      break;
    }
    for(int i=0; i < searchPtr->adjacentList.size(); ++i)
    {
      if(searchPtr->dist + 1 < searchPtr->adjacentList[i]->dist)
      {
        searchPtr->adjacentList[i]->dist = searchPtr->dist + 1;
        searchPtr->adjacentList[i]->prev = searchPtr;
        myQueue.push(searchPtr->adjacentList[i]);
      }
    }
  }
  searchPtr = endPoint;
  while(1)
  {
    pair<string, int> movie_pair;
    actor_name_stack.push(searchPtr->actorName);
    if(searchPtr == startPoint)
    {
      break;
    }
    movie_pair = getSharedMovie(searchPtr, searchPtr->prev);
    string year = to_string(movie_pair.second);
    string full_movie_name = movie_pair.first + "#@" + year;
    movie_title_stack.push(full_movie_name);
    searchPtr = searchPtr->prev;
  }
  stack_pair.first = actor_name_stack;
  stack_pair.second = movie_title_stack;
  initialize(startPoint); 
  return stack_pair;
}

pair<string, int> ActorGraph::getSharedMovie(Node* actor_one, Node* actor_two)
{
  pair<string, int> myPair;
  for(int i=0; i < actor_one->movieList.size(); ++i)
  {
    for(int j=0; j < actor_two->movieList.size(); ++j)
    {
      if(actor_one->movieList[i] == actor_two->movieList[j] && actor_one->yearList[i] == actor_two->yearList[j])
      {
        myPair.first = actor_one->movieList[i];
        myPair.second = actor_one->yearList[i];
        return myPair;
      }
    }
  }  
}

void ActorGraph::initialize(Node* nodePtr)
{
  queue<Node*> myQueue;
  Node* searchPtr = nodePtr;
  myQueue.push(searchPtr);
  searchPtr->prev = nullptr;
  searchPtr->dist = -1;
  while(!myQueue.empty())
  {
    searchPtr = myQueue.front();
    myQueue.pop();
    for(int i=0; i < searchPtr->adjacentList.size(); ++i)
    {
      if(searchPtr->adjacentList[i]->prev != nullptr)
      {
        searchPtr->prev = nullptr;
        searchPtr->dist = -1;
        myQueue.push(searchPtr->adjacentList[i]);
      }
    }
  }  
}

void ActorGraph::deleteAll(Node* nodePtr)
{
  nodePtr->isItVisited = true;
  for(int i=0; i < nodePtr->adjacentList.size(); ++i)
  {
    if(nodePtr->adjacentList[i]->isItDeleted == 1)
    { 
      if(nodePtr->adjacentList[i]->isItVisited == false)
      {
        deleteAll(nodePtr->adjacentList[i]);
      }
    }
  }
  delete nodePtr;
}

ActorGraph::~ActorGraph()
{
  for(int i=0; i < listOfStartNode.size(); ++i)
  {
    deleteAll(listOfStartNode[i]);
  }
}













































 
