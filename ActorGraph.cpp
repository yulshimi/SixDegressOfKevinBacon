//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The implemantation of "ActorGraph.h"
//Assignment#: PA4
#include "ActorGraph.h"
using namespace std;
bool ActorGraph::loadFromFile(const char* in_filename, ostream& outs, bool use_weighted_edges)
{
  fstream infile(in_filename);
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
      if(use_weighted_edges == false)
      {
        if(!findTheShortestPath(record[0], record[1]))
        {
          m_start_point = nullptr;
        }
      }
      else
      {
        if(!dijkstraAlgorithm(record[0], record[1]))
        {
          m_start_point = nullptr;
        }
      }
      printOutThePath(m_start_point, outs);
      if(m_start_point != nullptr)
      {
        outs << endl;
      }
      else
      {
        outs << "(" << record[0] << ")" << "--[NO PATH]-->" << "(" << record[1] << ")" << endl;
      }
      makeAllUnvisited();
    }
    else
    {
      string actor_name(record[0]);
      string movie_title(record[1]);
      unsigned int  movie_year = stoi(record[2]);
      createGraph(actor_name, movie_title, movie_year);
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

bool ActorGraph::loadFromFile(const char* in_filename, ostream& outs)
{
  fstream infile(in_filename);
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
      bool isItValid = true;
      actorPair myPair;
      myPair.actor_one = record[0];
      myPair.actor_two = record[1];
      m_pair_list.push_back(myPair);
      actor_it = m_actor_list.find(record[0]);
      if(actor_it == m_actor_list.end())
      {
        isItValid = false;   
      }
      actor_it = m_actor_list.find(record[1]);
      if(actor_it == m_actor_list.end())
      {
        isItValid = false;
      }
      if(isItValid == false)
      {
        m_pair_list[m_pair_list.size()-1].connect = true;
        ++m_numOfInvalid;
      }
    }
    else
    { 
      string actor_name(record[0]);
      string movie_title(record[1]);
      unsigned int  movie_year = stoi(record[2]);
      createActorConnectionGraph(record[0], record[1], movie_year); 
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

ActorGraph::ActorGraph()
{
  m_start_point = nullptr;
  m_numOfInvalid = 0;
}
//This method creates a graph for "pathfinder.cpp"
void ActorGraph::createGraph(string actor_name, string movie_name, int year)
{
  actor_it = m_actor_list.find(actor_name);
  string full_movie_name = movie_name + "#@" + to_string(year);
  movie_it = m_movie_list.find(full_movie_name);
  if(actor_it == m_actor_list.end())
  {
    Node* newActorNode = new Node(actor_name);
    m_actor_list[actor_name] = newActorNode;
    actor_it = m_actor_list.find(actor_name);  
  }
  if(movie_it == m_movie_list.end())
  {
    Edge* newMovieNode = new Edge(full_movie_name, year);
    m_movie_list[full_movie_name] = newMovieNode;
    movie_it = m_movie_list.find(full_movie_name);
  }
  (actor_it->second->m_movie_list).insert(full_movie_name);
  (movie_it->second->m_actor_list).insert(actor_name);
}
//This method creates a graph for "actorconnections.cpp"
void ActorGraph::createActorConnectionGraph(string actor_name, string movie_name, int year)
{ 
  actor_it = m_actor_list.find(actor_name);
  string full_movie_name = movie_name + "#@" + to_string(year);
  movie_it = m_movie_list.find(full_movie_name);
  year_it = m_year_list.find(year);
  if(actor_it == m_actor_list.end())
  { 
    Node* newActorNode = new Node(actor_name);
    m_actor_list[actor_name] = newActorNode;
    actor_it = m_actor_list.find(actor_name);
  }
  if(movie_it == m_movie_list.end())
  { 
    Edge* newMovieNode = new Edge(full_movie_name, year);
    m_movie_list[full_movie_name] = newMovieNode;
    movie_it = m_movie_list.find(full_movie_name);
  }
  if(year_it == m_year_list.end())
  {
    Year* newYearNode = new Year(year);
    m_year_list[year] = newYearNode;
    year_it = m_year_list.find(year);
  }
  (movie_it->second->m_actor_list).insert(actor_name);
  if(year_it->second->m_edge_list.find(full_movie_name) == year_it->second->m_edge_list.end())
  {
    (year_it->second->m_edge_list).insert(full_movie_name);
  }
}
//This method creates a priority queue based on what year a movie was made
void ActorGraph::createPriorityQueue()
{
  for(year_it = m_year_list.begin(); year_it != m_year_list.end(); ++year_it)
  {
    m_priority_queue.push(year_it->second);
  }
}
//This method finds the shortest path between two actors
bool ActorGraph::findTheShortestPath(string actor_one_name, string actor_two_name)
{
  actor_it = m_actor_list.find(actor_one_name);
  if(actor_it == m_actor_list.end())
  {
    return false;
  }
  Node* actor_one = actor_it->second;
  actor_it = m_actor_list.find(actor_two_name);
  if(actor_it == m_actor_list.end())
  {
    return false;
  } 
  Node* actor_two = actor_it->second;
  Node* searchPtr = actor_one;
  queue<Node*> myQueue;
  myQueue.push(searchPtr);
  searchPtr->weight = 0;
  m_visited_node.push_back(searchPtr);
  while(!myQueue.empty())
  {
    searchPtr = myQueue.front();
    if(searchPtr == actor_two)
    {
      break;
    }
    for(movie_set_it = searchPtr->m_movie_list.begin(); movie_set_it != searchPtr->m_movie_list.end(); ++movie_set_it)
    {
      movie_it = m_movie_list.find(*movie_set_it);
      Edge* tempMoviePtr = movie_it->second;
      for(actor_set_it = tempMoviePtr->m_actor_list.begin(); actor_set_it != tempMoviePtr->m_actor_list.end(); ++actor_set_it)
      {
        actor_it = m_actor_list.find(*actor_set_it);
        Node* tempActorPtr = actor_it->second;
        if(searchPtr->weight+1 < tempActorPtr->weight)
        {
          tempActorPtr->weight = searchPtr->weight + 1;
          tempActorPtr->prev = searchPtr;
          tempActorPtr->prev_movie = *movie_set_it;
          m_visited_node.push_back(tempActorPtr);
          myQueue.push(tempActorPtr);
        }
      }    
    }
    myQueue.pop();
  }
  m_start_point = actor_two;
  return true;   
}
//This method finds a path between two actors, which has the minimum weight.
bool ActorGraph::dijkstraAlgorithm(string actor_one_name, string actor_two_name)
{
  actor_it = m_actor_list.find(actor_one_name);
  if(actor_it == m_actor_list.end())
  {
    return false;
  }
  Node* actor_one = actor_it->second;
  actor_it = m_actor_list.find(actor_two_name);
  if(actor_it == m_actor_list.end())
  {
    return false;
  }
  Node* actor_two = actor_it->second;
  Node* searchPtr = actor_one;
  priority_queue<Node*, vector<Node*>, NodePtrComp> myQueue;
  myQueue.push(searchPtr);
  searchPtr->weight = 0;
  m_visited_node.push_back(searchPtr);
  while(!myQueue.empty())
  {
    searchPtr = myQueue.top();
    if(searchPtr == actor_two)
    {
      break;
    }
    for(movie_set_it = searchPtr->m_movie_list.begin(); movie_set_it != searchPtr->m_movie_list.end(); ++movie_set_it)
    {
      movie_it = m_movie_list.find(*movie_set_it);
      Edge* tempMoviePtr = movie_it->second;
      unsigned int current_weight = 2015 - tempMoviePtr->m_year + 1;
      for(actor_set_it = tempMoviePtr->m_actor_list.begin(); actor_set_it != tempMoviePtr->m_actor_list.end(); ++actor_set_it)
      {
        actor_it = m_actor_list.find(*actor_set_it);
        Node* tempActorPtr = actor_it->second;
        if(searchPtr->weight+current_weight < tempActorPtr->weight)
        {
          tempActorPtr->weight = searchPtr->weight + current_weight;
          tempActorPtr->prev = searchPtr;
          tempActorPtr->prev_movie = *movie_set_it;
          m_visited_node.push_back(tempActorPtr);
          myQueue.push(tempActorPtr);
        }
      }
    }
    myQueue.pop();
  }
  m_start_point = actor_two;
  return true;
}
//This method prints out a path between two actors
void ActorGraph::printOutThePath(Node* startPoint, ostream& outs) const
{
  stack<string> movie_name_stack;
  stack<string> actor_name_stack;
  Node* searchPtr = startPoint;
  while(searchPtr != nullptr)
  {
    actor_name_stack.push(searchPtr->m_actor_name);
    movie_name_stack.push(searchPtr->prev_movie);
    searchPtr = searchPtr->prev;
  }
  string actor_name;
  string movie_name;
  while(!actor_name_stack.empty())
  {
    actor_name = actor_name_stack.top();
    movie_name = movie_name_stack.top();
    actor_name_stack.pop();
    movie_name_stack.pop();
    if(movie_name != "")
    {
      outs << "--[" << movie_name << "]-->";
    }
    outs << "(" << actor_name << ")";
  } 
}
//This methods clear all nodes for the future operation
void ActorGraph::makeAllUnvisited()
{
  for(int i=0; i < m_visited_node.size(); ++i)
  {
    m_visited_node[i]->isItVisited = false;
    m_visited_node[i]->prev = nullptr;
    m_visited_node[i]->weight = -1;
    m_visited_node[i]->prev_movie = "";
  }
  m_visited_node.clear();
}
//This method check whether two actors are connected or not
bool ActorGraph::areTheyConnected(string actor_one_name, string actor_two_name)
{
  actor_it = m_actor_list.find(actor_one_name);
  if(actor_it == m_actor_list.end())
  {
    return false;
  }
  Node* actor_one = actor_it->second;
  actor_it = m_actor_list.find(actor_two_name);
  if(actor_it == m_actor_list.end())
  {
    return false;
  }
  Node* actor_two = actor_it->second;
  if(actor_one == actor_two)
  {
    return true;
  }
  queue<Node*> myQueue;
  Node* searchPtr = actor_one;
  myQueue.push(searchPtr);
  searchPtr->isItVisited = true;
  m_visited_node.push_back(searchPtr);
  while(!myQueue.empty())
  {
    searchPtr = myQueue.front();
    myQueue.pop();
    for(movie_set_it = searchPtr->m_movie_list.begin(); movie_set_it != searchPtr->m_movie_list.end(); ++movie_set_it)
    {
      movie_it = m_movie_list.find(*movie_set_it);
      Edge* tempMoviePtr = movie_it->second;
      for(actor_set_it = tempMoviePtr->m_actor_list.begin(); actor_set_it != tempMoviePtr->m_actor_list.end(); ++actor_set_it)
      {
        actor_it = m_actor_list.find(*actor_set_it);
        Node* tempActorPtr = actor_it->second;
        if(tempActorPtr == actor_two)
        {
          makeAllUnvisited();
          return true;
        }
        if(tempActorPtr->isItVisited == false)
        {
          tempActorPtr->isItVisited = true;
          m_visited_node.push_back(tempActorPtr);
          myQueue.push(tempActorPtr);  
        }  
      }
    }
  }
  makeAllUnvisited();
  return false;  
}
//This method finds the first year when actors are connected
void ActorGraph::actorConnection()
{
  Node* actorSearchPtr;
  Edge* edgeSearchPtr;
  Year* yearSearchPtr;
  unsigned int size_of_pair = m_pair_list.size() - m_numOfInvalid;
  while(0 < size_of_pair)
  {
    yearSearchPtr = m_priority_queue.top();
    m_priority_queue.pop();
    for(year_set_it = yearSearchPtr->m_edge_list.begin(); year_set_it != yearSearchPtr->m_edge_list.end(); ++year_set_it)
    { 
      movie_it = m_movie_list.find(*year_set_it);
      edgeSearchPtr = movie_it->second;
      for(actor_set_it = edgeSearchPtr->m_actor_list.begin(); actor_set_it != edgeSearchPtr->m_actor_list.end(); ++actor_set_it)
      {
        actor_it = m_actor_list.find(*actor_set_it);
        actorSearchPtr = actor_it->second;
        if(actorSearchPtr->m_movie_list.find(*year_set_it) == actorSearchPtr->m_movie_list.end())
        {
          actorSearchPtr->m_movie_list.insert(*year_set_it);
        }
      } 
    }
    for(unsigned int i=0; i < m_pair_list.size(); ++i)
    {
      if(m_pair_list[i].connect == false)
      {
        if(areTheyConnected(m_pair_list[i].actor_one, m_pair_list[i].actor_two))
        {
          m_pair_list[i].connected_year = yearSearchPtr->m_year;
          m_pair_list[i].connect = true;
          --size_of_pair;
        }
      }    
    }    
  }
}
//This method prints out which year two actors are connected
void ActorGraph::printOutConnectedYear(ostream& outs) const
{
  for(int i=0; i < m_pair_list.size(); ++i)
  {
    outs << m_pair_list[i].actor_one << "\t" << m_pair_list[i].actor_two << "\t" << m_pair_list[i].connected_year << endl;
  }     
}
//This is a helper method for destructor
void ActorGraph::destroy()
{
  for(actor_it = m_actor_list.begin(); actor_it != m_actor_list.end(); ++actor_it)
  {
    delete actor_it->second;  
  } 
  for(movie_it = m_movie_list.begin(); movie_it != m_movie_list.end(); ++movie_it)
  {
    delete movie_it->second;
  }
  for(year_it = m_year_list.begin(); year_it != m_year_list.end(); ++year_it)
  {
    delete year_it->second;
  }
}
//destructor
ActorGraph::~ActorGraph()
{
  destroy();
}
































