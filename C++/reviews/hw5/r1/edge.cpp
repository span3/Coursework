#include<iostream>
#include<iomanip>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<limits>
#include<fstream>
#include<string>
#include<sstream>
#include<algorithm>
#include<set>

#include "edge.h"
using namespace std;

Edge::Edge()
{
	weight = numeric_limits<int>::max(); //default const.
}

Edge::Edge(int n1, int n2, int w, Color c)
{
	node1 = n1;
	node2 = n2;
	weight = w;
	col = c;
}