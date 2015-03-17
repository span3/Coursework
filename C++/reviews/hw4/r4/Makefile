CXX=g++
CXXFLAGS=-Wall -Wno-deprecated -pedantic-errors -g
SOURCES=asg4.cpp graph.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<
