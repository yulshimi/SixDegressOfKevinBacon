#include <utility>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
int main ()
{
  pair<vector<string>, vector<int> > myPair;
  vector<string> string_vector;
  vector<int> int_vector;
  for(int i=0; i < 10; ++i)
  {
    string_vector.push_back("abcd");
    int_vector.push_back(100);
  }
  myPair.first = string_vector;
  myPair.second = int_vector;
  for(int i=0; i < myPair.first.size(); ++i)
  {
    cout << myPair.first[i] << endl;
  }
  return 0;
}
