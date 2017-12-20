# Example makefile for the demo project

CFLAGS = -Wall
CC     = g++

# These are the libraries that must be included in order to have the mantis
# library compile.
LIBS   = -Llib -lmantis -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread

demo: bin bin/demo.o bin/snake.o bin/snake_stage.o lib/libmantis.a
	$(CC) $(CFLAGS) -o demo bin/*.o $(LIBS)
	@echo "Success!"

bin/demo.o: src/demo.cpp src/snake.h
	@echo
	$(CC) -c $(CFLAGS) -o bin/demo.o src/demo.cpp

bin/snake.o: src/snake.cpp src/snake.h
	$(CC) -c $(CFLAGS) -o bin/snake.o src/snake.cpp

bin/snake_stage.o: src/snake_stage.cpp src/snake.h
	$(CC) -c $(CFLAGS) -o bin/snake_stage.o src/snake_stage.cpp

lib/libmantis.a:
	rm -rf lib
	make -C src/mantis
	mv src/mantis/lib lib

# UTILS

bin:
	mkdir -p bin

clean:
	rm -rf bin demo lib

run: demo
	./demo
