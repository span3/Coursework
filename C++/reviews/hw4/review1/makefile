#makefile for CMPS109 hw4

hw4: main.o graph.o
	g++ -o hw4 main.o graph.o

main.o: main.cpp graph.h
	g++ -c main.cpp

graph.o: graph.h graph.cpp
	g++ -c graph.cpp

clean:
	rm hw4 main.o graph.o