/*What I learned
This is the first time I had to create a graph using C++, so I thought
this homework assignment was a bit challenging. For this I decided to
use the adjacency list to represent my graph. I think in the list each
vertex is listed more efficiently, even though it is slower than adjacency
matrix. For this homework, I also learned how to use the constructor
function to make a graph ADT. I learned that constructor cannot be called
explicitly and are only executed when a new object of that class is created.
I also learned that the destructor is automatically called when an object
is destroyed. Before starting this homework, I didn’t know much about Dijkstra's
algorithm, however after a lot of reading and researching. I can
say I finally has a good understand on how Dijkstra's algorithm works. Dijkstra's
algorithm produces a shortest path tree by finding paths with lowest
costs between every vertex. Even though my program is incomplete, I
still feel I learned a lot about C++.
*/
#include <vector>
#include <iostream>
#include <functional>
#include <stdlib>
#include <cstdio>
#include <ctime>
using namespace std;

class Edge
{
public:
	int weight, to, from, color, bar;

	Edge(int f, int t, int w, int c, int b ) :
		from(f), to(t), weight(w), color(c), bar(b) { }

	int returnNext(){ return to; }
};

class Vertex
{
public:
	int vID;
	vector<Edge> neighbors;
	Vertex(int vxID){ vID = vxID; }
};

class Graph
{
public:
	vector<Vertex> vList;
	Graph(double dens, int dMax, int dMin )
	{
		int i = 1;
		int colour = 0;
		//cout << "TEST1" << endl;
		for(i; i < 51; i++)
		{
			Vertex* vnew = new Vertex(i);
			vList.push_back(*vnew);
			//cout << "TEST1" << endl;
		}
		double Density = ( (50 * 49) * dens);
		double avgDensity = (Density / 50);
		int x = static_cast<int> (avgDensity + 1);

		//cout << "TEST2" << endl;
		for(int p = 1; p < 51; p++)
		{
		//cout << "TEST3" << endl;
		  for(int q = 0; q < x; q++)
		  {
			int r = (rand() % (50) + 1);
			//cout << "TEST1" << endl;
			while(true)
			{
			  int size = 0;
			  int esize = 0;
			  int check = 0;
			  //cout << "TEST1" << endl;
			  for(size; size < vList.size() ; size++)
			  {
				for(esize; esize < vList[size].neighbors.size(); esize++)
				{
					if((vList[size].neighbors[esize].to == r &&
						vList[size].neighbors[esize].from == i) || r == p)
					{
						r = (rand() % (50) + 1);
						check = 1;
						//cout << "TEST1" << endl;
					}
				}
			  }
			if(check==0) { break; }
			}
		  int colour = rand() % 2;
		  int weight = rand() % (dMax - dMin) + dMin;

		  Edge cEdge(p, r, weight, colour, 0);
		  vList[p-1].neighbors.push_back(cEdge);

		  if(p != 1)
		  {
		  Edge cEdge2(r, p, weight, colour, 0);
		  vList[r-1].neighbors.push_back(cEdge2);
		  }
		  }
		}
		//cout << "TEST1" << endl;
	}
	void display()
	{
		for(int n=0;  n<50; n++)
			cout << vList.at(n).vID << endl;
		cout << "\n" << endl;
	}
};

class nodeContent
{
public:
	int ID;
	int weight;
	int next;
	nodeContent(int i, int w, int n) :
		ID(i), weight(w), next(n) { }
};

class ShortestPath
{
public:
	vector <nodeContent> contents;
	ShortestPath(int origin, int toend, Graph graph, int col)
	{
	int i = 0;
	//cout << "hello1" << endl;
	  for(graph.vList[0].neighbors[i].from;
		graph.vList[0].neighbors[i].from == origin; i++)
	  {
	  //cout << "hello" << endl;
		if( (col == 2) || graph.vList[0].neighbors[i].color == col)
		{
		nodeContent* content = new nodeContent
			(graph.vList[0].neighbors[i].from, graph.vList[0].neighbors[i].weight,
			 graph.vList[0].neighbors[i].to);
			contents.push_back(*content);
			//cout << "P0" <<endl;
			graph.vList[0].neighbors[i].bar = 1;
		}
	  }
	  //cout << "hello" << endl;
	int count = 0;
	int lee = 0;
	//cout << "P1" <<endl;
	while(true)
	{
	if(count != 0 && contents.size() == 1) { break; }
	if(contents[count].next == toend)
	{
		count++;
		lee++;
	}else
	{
		int nextVertex = contents[count].next;
		int sizevOf = graph.vList[nextVertex-1].neighbors.size();
		for(int z = 0; z < (sizevOf); z++)
		{
		if(graph.vList[nextVertex-1].neighbors[z].bar != 1
			&& ((col == 2) || graph.vList[nextVertex-1].neighbors[z].color == col))
		{
		int money = 0;
		money = contents[count].weight + graph.vList[nextVertex-1].neighbors[z].weight;
		nodeContent* foo = new nodeContent(graph.vList[nextVertex-1].neighbors[z].from,
						money, graph.vList[nextVertex-1].neighbors[z].to);
		graph.vList[nextVertex-1].neighbors[z].bar = 1;
		contents.push_back(*foo);
		}else { //cout << test <<endl;
		 }
		}
		if(count == contents.size()) { break; }

		if(contents[count].next != toend)
		{
			contents.erase(contents.begin() + count);
		}
	}
		//cout << "P2" <<endl;

		int terminate = 0;
		for(int zz = 1; zz < contents.size(); zz++)
		 {
			if(count == zz) { zz++; }
			if(contents[count].next == contents[zz+count].next)
			{
				if(contents[count].weight < contents[count+ zz].weight)
				{
				 contents.erase(contents.begin() + (count+zz));
				 //cout << "P3" <<endl;
				}else{
				contents.erase(contents.begin() + (count));
				}
			}
			if(contents[zz].next == toend)
			{ terminate++; }
		  }
		  if(terminate == contents.size()) { break; }
	}
	//cout << "P4" <<endl;

	while(true)
	 {
	 int yy = 0;
	  if(contents.size() == 1) { break; }
	  if(contents[yy].next == contents[yy+1].next) {
	    if(contents[yy].weight > contents[yy+1].weight)
		{
		  contents.erase(contents.begin());
		  //cout << "P5" <<endl;
		}else {
			contents.erase(contents.begin() + (yy+1));
			//cout << "P6" <<endl;
			  }
		}
	 }
	}
	int smallestVertex() { return contents[0].weight; }
};




main()
{
// 0 = RED, 1 == BLACK, 2 = BOTH
	srand(time(NULL));
	Graph g(.20, 10, 1);
	cout << "20% Density:" << endl;

	//RED
	int average = 0;
	int a = 2;
	//cout << "P5" <<endl;
	for(a; a < 51; a++) {
	//cout << "P8" <<endl;
		int b = ShortestPath(1, a, g, 0).smallestVertex();
		average = average + b;
		//cout << "P5" << b <<endl;
	}
	double avg = average/49.0;
	cout << "Red: " << avg << endl;

	//BLACK
	int average1 = 0;
	int a1 = 2;
	//cout << "P5" <<endl;
	for(a1; a1 < 51; a1++) {
	//cout << "P8" <<endl;
		int b1 = ShortestPath(1, a1, g, 1).smallestVertex();
		average1 = average1 + b1;
		//cout << "P5" <<endl;
	}
	//cout << "hello" << endl;
	double avg1 = average1/49.0;
	cout << "Black: " << avg1 << endl;

	int average12 = 0;
	int a12 = 2;
	//cout << "P5" <<endl;
	for(a12; a12 < 51; a12++) {
	//cout << "P8" <<endl;
		int b12 = ShortestPath(1, a12, g, 2).smallestVertex();
		average12 = average12 + b12;
		//cout << "P5" <<endl;
	}
	//cout << "hello" << endl;
	double avg12 = average12/49.0;
	cout << "Both: " << avg12 << endl;
	cout << "\n" <<endl;

	Graph g1(.40, 10, 1);
	cout << "40% Density:" << endl;
	//RED
	int averag = 0;
	int a2 = 2;
	//cout << "P5" <<endl;
	for(a2; a2 < 51; a2++) {
	//cout << "P8" <<endl;
		int b2 = ShortestPath(1, a2, g1, 0).smallestVertex();
		averag = averag + b2;
		//cout << "P5" << b <<endl;
	}
	double avg2 = averag/49.0;
	cout << "Red: " << avg2 << endl;

	int avera = 0;
	int a3 = 2;
	//cout << "P5" <<endl;
	for(a3; a3 < 51; a3++) {
	//cout << "P8" <<endl;
		int b3 = ShortestPath(1, a3, g1, 1).smallestVertex();
		avera = avera + b3;
		//cout << "P5" << b <<endl;
	}
	double avg3 = avera/49.0;
	cout << "Black: " << avg3 << endl;

	int aver = 0;
	int a31 = 2;
	//cout << "P5" <<endl;
	for(a31; a31 < 51; a31++) {
	//cout << "P8" <<endl;
		int b31 = ShortestPath(1, a31, g1, 2).smallestVertex();
		aver = aver + b31;
		//cout << "P5" << b <<endl;
	}
	double avg31 = aver/49.0;
	cout << "Both: " << avg31 << endl;
}
