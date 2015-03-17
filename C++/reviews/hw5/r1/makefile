EXE = hex
CPPS = main.cpp edge.cpp node.cpp graph.cpp hex.cpp
OBJS = main.o edge.o node.o graph.o hex.o

Default: main.o edge.o node.o graph.o hex.o
	g++ -o $(EXE) -O3 $(OBJS) 

all:
	g++ -c -O3 -g $(CPPS) 
	g++ -o $(EXE) $(OBJS)
	
c11:
	g++ -std=c++11 -O3 -c $(CPPS)
	g++ -o $(EXE) $(OBJS)
	
main.o: main.cpp hex.h graph.h node.h edge.h color.h
	g++ -c -g -O3 main.cpp
	
edge.o: edge.cpp edge.h color.h
	g++ -c -g -O3 edge.cpp

node.o: node.cpp node.h edge.h color.h
	g++ -c -g -O3 node.cpp

graph.o: graph.cpp graph.h node.h edge.h color.h
	g++ -c -g -O3 graph.cpp
	
hex.o: hex.cpp graph.h node.h edge.h color.h
	g++ -c -g -O3 hex.cpp

open:
	open makefile main.cpp edge.cpp node.cpp graph.cpp hex.cpp
	open edge.h node.h graph.h hex.h color.h
	open readme.tex
clean:
	rm *.o $(EXE)
	
run:
	./$(EXE)

val:
	valgrind ./$(EXE)
	
tex:
	pdflatex readme.tex
	open readme.pdf