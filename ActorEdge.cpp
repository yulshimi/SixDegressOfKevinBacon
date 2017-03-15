//Name: Phillip Jo, San Kang
//Date: 03/15/2017
//Overview: The impletation of "ActorEdge.h"
//Assignment#: PA4
#include "ActorEdge.h"
using namespace std;
Edge::Edge()
{
  m_movie_name = "";
  m_year = 0;
}

Edge::Edge(string movie_name, int year)
{
  m_movie_name = movie_name;
  m_year = year;  
}
