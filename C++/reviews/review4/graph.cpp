#include <iostream>
#include <cmath>
#include <vector>
#include <climits>
#include <set>
#include <iterator>
#include <ctime>
#include <cstdlib>
#include <cfloat>
#include <stdexcept>
#include <fstream>
#include "graph.h"

using namespace std;

int graph::shortest_path(int start, int end, bool find_all_paths, int colorbits, vector<int> &prev, vector<double> &dist)
{
	dist.clear();
	dist.assign(num, INFINITY);
	std::set<int>::iterator it;
	
	dist[start] = 0;
	prev.clear();
	prev.assign(num, -1);
	int count=0;
	set<int> unvisited;
	for(int i=0;i<num;i++) {
		unvisited.insert(i);
	}
	
	while(!unvisited.empty())
	{
		/* get lowest value in dist */
		int min=-1;
		for(int i=0;i<num;i++)
		{
			if(((min == -1) || dist[i] < dist[min]) && (unvisited.find(i) != unvisited.end())) min = i;
		}
		/* get and remove the minimum of dist from the unvisited set */
		int current = *(it = unvisited.find(min));
		unvisited.erase(it);
		if(current == end && !find_all_paths)
			break;
		cout << "visiting " << ++count << " of " << num << " nodes." << "\r";
		/* no point in continuing from here */
		if(dist[current] == INFINITY)
			break;
		/* loop through all nodes to find neighbors */
		for (int i=0;i<num;i++)
		{
			double length = conn[current][i];
			/* if we are connected, and we aren't ignoring this path... */
			if(length != INFINITY && (color[current][i] & colorbits))
			{
				/* calculate the distance from here */
				double newdist = dist[current] + length;
				if(newdist < dist[i])
				{
					/* swap it out if we've beaten the previous distance */
					dist[i] = newdist;
					prev[i] = current;
				}
			}
		}
		
	}
	cout << endl;
	return(dist[end] != INFINITY);
}

double graph::mst(int colorbits, set<undirected_edge *> &mst)
{
	double cost = 0;
	set<undirected_edge *> paths;
	/* create a set of all edges in the graph. We assume an undirected
	 * graph, and so ignore half of the matrix */
	for(int i=0;i<num;i++)
	{
		for(int j=i;j<num;j++)
		{
			if(conn[i][j] != INFINITY) {
				undirected_edge *e = new undirected_edge(i, j, color[i][j], conn[i][j]);
				paths.insert(e);
			}
		}
	}
	set<int> visited;
	std::set<undirected_edge *>::iterator it, shortest;
	/* All the paths!!! */
	while(!paths.empty()) {
		shortest = paths.end();
		for(it = paths.begin();it != paths.end();++it)
		{
			if((shortest == paths.end() || (*shortest)->length > (*it)->length) && ((*it)->color & colorbits))
				shortest = it;
		}
		if(shortest == paths.end())
			break;
		/* shortest path that doesn't add a node that we've already
		 * visited */
		undirected_edge *e = *shortest;
		paths.erase(shortest);
		
		if(visited.find(e->u) == visited.end())
		{
			visited.insert(e->u);
			mst.insert(e);
			cost += e->length;
		}
	}
	/* freeeeeee! */
	for(it = paths.begin();it != paths.end();++it)
	{
		delete (*it);
	}
	return cost;
}

graph::graph(string filename)
{
	cout << "open: " << filename << endl;
	ifstream input (filename.c_str());
	if(input.is_open())
	{
		input >> num;
		cout << "reading graph of size " << num << endl;
		/* ok, yeah, lets set up the matricies.. */
		conn.assign(num, std::vector<double>(num));
		color.assign(num, std::vector<int>(num));
		
		double length;
		int x, y, col;
		
		while(!input.eof()) {
			input >> x;
			input >> y;
			input >> length;
			input >> col;
			if(input.eof()) break;
			//cout << "adding edge (" << x << "," << y << ") of length " << length << " color " << col << endl;
			conn[x][y] = length;
			conn[y][x] = length;
			color[x][y] = 1 << col;
			color[y][x] = 1 << col;
			edges++;
		}
	}
	
}

void graph::generate_random(double density, int min_length, int max_length, bool undirected, bool loops)
{
	cout << "generating graph with density=" << density << ", paths from " << min_length << " to " << max_length << endl;
	cout << (undirected ? "undirected" : "directed") << " with" << (loops ? " " : "out ") << "loops" << endl;
	for(int i=0;i<num;i++)
	{
		/* if we're undirected, only fill out half the matrix, and then copy
		 * the element over to form a symmetric matrix */
		for(int j=(undirected ? i : 0);j<num;j++)
		{
			if(((double)rand() / (unsigned)RAND_MAX) < density && (loops || (i != j)))
			{
				/* random double between min_length and max_length */
				double length = ((double)rand() / (unsigned)RAND_MAX) * (max_length - min_length) + min_length + 1;
				int col = 1 << (rand() % 3);
				conn[i][j] = length;
				color[i][j] = col;
				if(undirected) 
				{
					conn[j][i] = length;
					color[j][i] = col;
				}
				edges++;
			} else {
				conn[i][j] = INFINITY;
				color[i][j] = 0;
				if(undirected) 
				{
					conn[j][i] = INFINITY;
					color[j][i] = 0;
				}
			}	
		}
	}
}

void graph::print_matrix()
{
	cout << "CONNECTIVITY MATRIX:" << endl << "(path_length:color)" << endl;
	cout << "x|\t";
	for(int i=0;i<num;i++)
		cout << i << "\t";
	cout << endl << "-+";
	for(int i=0;i<num*8;i++)
		cout << "-";
	cout << endl;
	for(int i=0;i<num;i++)
	{
		cout << i << "|\t";
		for(int j=0;j<num;j++)
		{
			cout << conn[i][j] << ":" << color[i][j] << '\t';
		}
		cout << endl;
	}
}

void graph::print_backtrace(int start, int end, vector<int> prev, vector<double> dist)
{
	int x = end;
	cout << "Backtrace:" << endl;
	while(x >= 0)
	{
		cout << x << " ";
		if(x == start) cout << "(START)\t";
		else if(x == end) cout << "  (END)\t";
		else cout << "\t\t";
		cout << "dist=" << dist[x] << "\n";
		x = prev[x];
	}
}

double calculate_average(vector<double> arr, int num)
{
	int relevant=num;
	double total=0;
	for(int i=0;i<num;i++)
	{
		/* ignore INFINITY */
		if(arr[i] == INFINITY)
			relevant--;
		else
			total += arr[i];
	}
	if(total == 0) return INFINITY;
	return (total / relevant);
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	
	graph g("Mstdata");
	const int start=0;
	
	cout << "Dijkstra path averages with varying colors (red=bit 0, green=bit 1, blue=bit 2):" << endl;
	cout << "color:average" << endl;
	for(int i=1;i<8;i++)
	{
		vector<int> prev;
		vector<double> dist;
		g.shortest_path(start, 0, true, i, prev, dist);
		double a = calculate_average(dist, g.size());
		cout << i << ":" << a << endl;
	}
	
	
	set<undirected_edge *> mst;
	double c = g.mst(7, mst);
	
	std::set<undirected_edge *>::iterator it;
	cout << "MST edge list:" << endl;
	for(it = mst.begin();it != mst.end();++it)
	{
		undirected_edge *e = *it;
		printf("%d %d %d %d\n", e->u, e->v, e->length, e->color);
	}
	
	cout << "MST total cost: " << c << endl;
	
	return 0;
}
