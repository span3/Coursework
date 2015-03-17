//What gets printed?
// ostream_iterator example
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

int main () {
  vector<int> mystery;
  for (int i=1; i<10; ++i) mystery.push_back(i*2);

  ostream_iterator<int> out_it (cout, "\t");
  copy ( mystery.begin(), mystery.end(), out_it );
  return 0;
}
