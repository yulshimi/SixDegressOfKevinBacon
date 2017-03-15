//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The implementation of "UnionFind.h"
//Assignment#: PA4
#include "UnionFind.h"
using namespace std;
bool DisjointSet::loadFromFile(const char* in_filename, ostream& outs)
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

DisjointSet::DisjointSet()
{
  m_start_point = nullptr;
  m_numOfInvalid = 0;
}

void DisjointSet::createActorConnectionGraph(string actor_name, string movie_name, int year)
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

void DisjointSet::createPriorityQueue()
{
  for(year_it = m_year_list.begin(); year_it != m_year_list.end(); ++year_it)
  {
    m_priority_queue.push(year_it->second);
  }
}

void DisjointSet::printOutConnectedYear(ostream& outs) const
{
  for(int i=0; i < m_pair_list.size(); ++i)
  {
    outs << m_pair_list[i].actor_one << "\t" << m_pair_list[i].actor_two << "\t" << m_pair_list[i].connected_year << endl;
  }     
}

void DisjointSet::destroy()
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

DisjointSet::~DisjointSet()
{
  destroy();
}
//This method finds when two specific actors are connected for the first time based on disjoint set data structure.
void DisjointSet::disjointSet()
{
  unordered_set<string>::iterator first_it;
  Edge* tempEdgePtr;
  Year* tempYearPtr;
  unsigned int comparison = m_pair_list.size() - m_numOfInvalid;
  while(0 < comparison)
  {
    tempYearPtr = m_priority_queue.top();
    m_priority_queue.pop();
    for(movie_set_it = tempYearPtr->m_edge_list.begin(); movie_set_it != tempYearPtr->m_edge_list.end(); ++movie_set_it)
    {
      movie_it = m_movie_list.find(*movie_set_it);
      tempEdgePtr = movie_it->second;
      first_it = tempEdgePtr->m_actor_list.begin();
      for(actor_set_it = tempEdgePtr->m_actor_list.begin(); actor_set_it != tempEdgePtr->m_actor_list.end(); ++actor_set_it)
      {
        disjointSetUnion(*first_it, *actor_set_it);
      }
    }
    for(unsigned int i=0; i < m_pair_list.size(); ++i)
    {
      if(m_pair_list[i].connect == false)
      {
        if(connectivity(m_pair_list[i].actor_one, m_pair_list[i].actor_two))
        {
          --comparison;
          m_pair_list[i].connected_year = tempYearPtr->m_year;
          m_pair_list[i].connect = true;
        }
      }
    }
  }
}
//This method merges two sets if they get to have the same sentinel.
bool DisjointSet::disjointSetUnion(string actor_one_name, string actor_two_name)
{
  actor_it = m_actor_list.find(actor_one_name);
  Node* actor_one = actor_it->second;
  actor_it = m_actor_list.find(actor_two_name);
  Node* actor_two = actor_it->second;
  Node* sentinel_one = disjointSetFind(actor_one);
  Node* sentinel_two = disjointSetFind(actor_two);
  if(sentinel_one != sentinel_two)
  {
    if(sentinel_one->m_size < sentinel_two->m_size)
    {
      sentinel_one->sentinel = sentinel_two->sentinel;
      sentinel_two->m_size = sentinel_two->m_size + sentinel_one->m_size;
    }
    else
    {
      sentinel_two->sentinel = sentinel_one->sentinel;
      sentinel_one->m_size = sentinel_one->m_size + sentinel_two->m_size;
    }
  }
  return true;
}
//This methods returns a sentinel of input node and does path compression for the optimized future operation.
Node* DisjointSet::disjointSetFind(Node* child)
{
  vector<Node*> childNodes;
  Node* searchPtr = child;
  while(searchPtr->m_actor_name != searchPtr->sentinel)
  {
    childNodes.push_back(searchPtr);
    actor_it = m_actor_list.find(searchPtr->sentinel);
    searchPtr = actor_it->second;
  }
  for(unsigned int i=0; i < childNodes.size(); ++i)
  {
    childNodes[i]->sentinel = searchPtr->sentinel;
  }
  return searchPtr;
}
//This methods check whether two nodes have the same sentinel or not
bool DisjointSet::connectivity(string actor_one_name, string actor_two_name) 
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
  Node* sentinel_one = disjointSetFind(actor_one);
  Node* sentinel_two = disjointSetFind(actor_two);
  return sentinel_one->sentinel == sentinel_two->sentinel;
}

































