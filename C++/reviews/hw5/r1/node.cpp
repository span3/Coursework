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

#include "node.h"
using namespace std;



//Constructors:
Node::Node()
{
	tempDist = numeric_limits<int>::max();
	visited = false;
	playedInHex = NOCOLOR;
}

Node::Node(int t)
{
	tempDist = t;
}

//Methods:
void Node::append(Edge e)
{
	edgeList.push_back(e);
}

int Node::getNodeAt(int index, int nodeNum)
{
	if(edgeList[index].get1() == nodeNum)
	{
		return edgeList[index].get2();
	}
	else
	{
		return edgeList[index].get1();
	}
}

inline bool Node::operator> (const Node n) const
{
	return tempDist > n.getTempDist();
}

int Node::getNodeIndexFromEdgeAt(int i, int currentNode)
{
	if(edgeList[i].get1() == currentNode)
	{
		return edgeList[i].get2();
	}
	else
	{
		return edgeList[i].get1();
	}
}

int Node::getWeightFromEdgeAt(int i)
{
	return edgeList[i].getW();
}

void Node::addToTempDist(int i, int j) //i is the edge weight, j is the previous nodes weight
{
	if(tempDist == numeric_limits<int>::max())
	{
		tempDist = i + j;
	}
	else
	{
		if(i+j < tempDist)
		{
			tempDist = i+j;
		}
		else
		{

		}

	}
}

int Node::getEdgeIndexFromList(int node)
{
	for(int i = 0; i < edgeList.size(); i++)
	{
		if(edgeList[i].get1() == node || edgeList[i].get2() == node)
		{
			return i;
		}
	}
}