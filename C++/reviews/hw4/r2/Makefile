TARGET= asg5
CC= g++
CFLAGS= -std=c++0x
DEPS = game.h player.h hexBoard.h hexGraph.h
OBJ = main.o game.o player.o  hexBoard.o hexGraph.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
	rm -f $(TARGET)

.PHONY: default all clean

