# Example makefile for the demo project

CFLAGS = -Wall
CC     = g++

# These are the libraries that must be included in order to have the mantis
# library compile.
LIBS   = -Llib -lmantis -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread

demo: bin bin/demo.o bin/snake.o lib/mantis.a
	$(CC) $(CFLAGS) -o demo bin/*.o $(LIBS)

# Here is an example of how your .o files should be stored along with the
# compiled binaries of the mantis engine .o files. The last rule here makes
# the mantis makefile and moves the compiled binaries to the bin/mantis folder.
bin/demo.o: src/demo.cpp src/snake.h
	$(CC) -c $(CFLAGS) -o bin/demo.o src/demo.cpp

bin/snake.o: src/snake.cpp src/snake.h
	$(CC) -c $(CFLAGS) -o bin/snake.o src/snake.cpp

lib/mantis.a:
	make -C src/mantis
	mv src/mantis/lib lib

# UTILS

bin:
	mkdir -p bin

clean:
	rm -rf bin demo

run: demo
	./demo
