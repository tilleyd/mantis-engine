# Example makefile for the demo project

CFLAGS = -Wall
CC     = g++

# These are the libraries that must be included in order to have the mantis
# library compile.
LIBS   = -Llib -lmantis -lSDL2 -lSDL2_image -lSDL2_ttf -lpthread
OFILES = bin/demo.o bin/snake.o bin/snake_stage.o bin/pause_hstage.o

demo: bin $(OFILES) lib/libmantis.a
	$(CC) $(CFLAGS) -o demo $(OFILES) $(LIBS)
	@echo "Success!"

bin/demo.o: src/demo.cpp src/snake.h
	@echo
	$(CC) -c $(CFLAGS) -o bin/demo.o src/demo.cpp

bin/snake.o: src/snake.cpp src/snake.h
	$(CC) -c $(CFLAGS) -o bin/snake.o src/snake.cpp

bin/snake_stage.o: src/snake_stage.cpp src/snake.h
	$(CC) -c $(CFLAGS) -o bin/snake_stage.o src/snake_stage.cpp

bin/pause_hstage.o: src/pause_hstage.cpp src/snake.h
	$(CC) -c $(CFLAGS) -o bin/pause_hstage.o src/pause_hstage.cpp

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
