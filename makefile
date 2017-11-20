# Example makefile for the demo project

CFLAGS = -Wall
CC     = g++

# These are the libraries that must be included in order to link the mantis
# .o files to your executable.
LIBS   = -lSDL2 -lSDL2_image -lpthread

demo: bin bin/demo.o bin/menu.o bin/mantis
	$(CC) $(CFLAGS) -o demo bin/*.o bin/mantis/*.o $(LIBS)

# Here is an example of how your .o files should be stored along with the
# compiled binaries of the mantis engine .o files. The last rule here makes
# the mantis makefile and moves the compiled binaries to the bin/mantis folder.
bin/demo.o: src/demo.cpp src/menu.h
	$(CC) -c $(CFLAGS) -o bin/demo.o src/demo.cpp

bin/menu.o: src/menu.cpp src/menu.h
	$(CC) -c $(CFLAGS) -o bin/menu.o src/menu.cpp

bin/mantis:
	make -C src/mantis
	mv src/mantis/bin bin/mantis

# UTILS

bin:
	mkdir -p bin

clean:
	rm -rf bin demo

run: demo
	./demo
