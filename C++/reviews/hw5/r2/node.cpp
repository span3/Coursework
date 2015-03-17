//node.cpp
#ifndef NODE_CPP
#define NODE_CPP

#include "node.h"

node::node(void){
	visited = false;
   color = 0;
}



void node::setColor(int val){
	color = val;
}

void node::setVisited(bool foo){
	visited = foo;
}

int node::getColor(){
	return color;
}

bool node::getVisited(){
	return visited;
}

#endif
