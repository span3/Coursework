#include<iostream>
#include "color.h"

using namespace std;
class Edge
{
	public:
		Edge();
		Edge(int,int,int,Color);
		int get1() const {return node1;}
		void set1(int n){node1 = n;}
		int get2() const {return node2;}
		void set2(int n){node2 = n;}
		int getW() const {return weight;}
		void setW(int w){weight = w;}
		Color getC(){return col;}
		void setC(Color c){col = c;}
		friend ostream& operator<<(ostream& out, Edge e);
	private:
		int node1;
		int node2;
		int weight;
		Color col;
};