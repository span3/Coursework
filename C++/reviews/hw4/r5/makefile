# ListDr.c makefile

all: test.exe Hex.exe


test.exe: Graph.o GraphDr.o
	g++ -o test.exe Graph.o GraphDr.o

Hex.exe: Hex.o Graph.o
	g++ -o Hex.exe Graph.o Hex.o

Hex.o: Hex.cpp
	g++ -Wall -c -g Hex.cpp

Graph.o: Graph.cpp
	g++ -Wall -c -g Graph.cpp

GraphDr.o: GraphDr.cpp
	g++ -Wall -c -g GraphDr.cpp

clean: 
	rm -rf *.o

spotless:
	rm -rf *.o
	rm -rf *.exe 