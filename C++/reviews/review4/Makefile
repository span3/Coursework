export CXXFLAGS = -Wall -g
OBJ=graph.o

all: graph

clean:
	-rm *.o graph 

graph: graph.o
	g++ $(CXXFLAGS) graph.o -o graph

graph.o: graph.cpp graph.h
