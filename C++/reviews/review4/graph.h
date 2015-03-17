#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <iostream>
#include <string>

/* these are stored internally as a bit in an integer so we can easily
 * specify any combination of colors */
const int COLOR_RED   = 1;
const int COLOR_GREEN = 2;
const int COLOR_BLUE  = 4;

class undirected_edge
{
	public:
		undirected_edge(int _u, int _v, int c, int len)
		{
			u = _u;
			v = _v;
			color = c;
			length = len;
		}
		int u, v, color, length;
};

class graph
{
	public:
		graph(int n) {
			num = n;
			edges = 0;
			conn.assign(n, std::vector<double>(n));
			color.assign(n, std::vector<int>(n));
			std::cout << "allocated new graph, nodes=" << n << std::endl;
		}
		graph(std::string filename);
		int shortest_path(int start, int end, bool, int, std::vector<int> &, std::vector<double> &);
		void generate_random(double, int, int, bool, bool);
		void print_matrix();
		void print_backtrace(int, int, std::vector<int>, std::vector<double>);
		double mst(int, std::set<undirected_edge *> &mst);
		int size() { return num; }
	private:
		int num;
		int edges;
		/* 2-D matrix of path lengths */
		std::vector< std::vector<double> > conn;
		/* 2-D matrix of colors of paths */
		std::vector< std::vector<int> > color;
};

#endif
