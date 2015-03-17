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


#include "hex.h"
using namespace std;

//prints out individual Edges
ostream& operator<<(ostream& out, Edge e)
{
	out<<setfill(' ')<<setw(3)<< e.get1()<<' '<<setw(3)<<e.get2()<<' '<<setw(6)<<e.getW()<<' '<<e.getC();
	return out;
}

//prints out individual Nodes
ostream& operator<<(ostream& out, Node n)
{
	out<<"Connected to: ";
	for(int i = 0; i < n.getListSize(); i++)
	{
		out<<n.getEdgeAt(i) << '\\';
	}
	return out;
}

//prints out forests
ostream& operator<<(ostream& out, vector<set<Edge> > s)
{
	int x = 1;
	for(vector<set<Edge> >::iterator j = s.begin(); j != s.end();j++)
	{
		out <<"Subgraph #"<<x<<endl<<"-----------"<<endl;;
		int c = 1;
		int weight = 0;
		cout << "#   N1  N2 Weight Color"<<endl;
		for(set<Edge>::iterator k = (*j).begin(); k != (*j).end(); ++k)
		{
			out<<setfill('0')<<setw(2)<<c<<" "<< (*k) << endl;
			weight+=(*k).getW();
			c++;
		}
		out<<endl<<"WEIGHT: "<<weight<<endl<<endl;
		x++;
	}
	return out;
}




int main()
{
	int boardSize = 11;
	srand(time(NULL));
	Hex h(boardSize);
	h.play();
}
