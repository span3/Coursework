//node.h
#ifndef NODE_H
#define NODE_H

class node{
public:	
	node();
   int color;
	bool visited;
   
   int getColor();
   bool getVisited();

   void setColor(int);
   void setVisited(bool);

private:
	
};
#endif

