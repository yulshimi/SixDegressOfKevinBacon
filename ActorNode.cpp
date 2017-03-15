//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The implementation of "ActorNode.h"
//Assignment#: PA4
#include "ActorNode.h"
using namespace std;
Node::Node()
{
  m_actor_name = "";
  weight = -1;
  prev = nullptr;
  prev_movie = "";
  isItVisited = false;
  sentinel = "";
}

Node::Node(string actor_name)
{
  m_actor_name = actor_name;
  weight = -1;
  prev = nullptr;
  prev_movie = "";
  isItVisited = false;
  sentinel = actor_name;
  m_size = 1;
}
//Operator overloading to make priority_queue work as supposed to
bool Node::operator<(const Node& other)
{
  if(weight != other.weight)
  {
    return weight > other.weight;
  }
  return m_actor_name < other.m_actor_name;
}
