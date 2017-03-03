#include <iostream>
#include <queue>
using namespace std;
int main ()
{
  queue<int> myq;
  myq.push(100);
  myq.push(200);
  cout << myq.front() << endl;
  return 0;
}
