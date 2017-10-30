# Makefile for the Mantis Engine project
# Author  : Duncan Tilley
# Modified: 2017 Oct 30

SRC    = src
BIN    = bin
CFLAGS = -Wall
LIBS   = -lSDL2
CC     = g++
OFILES = $(BIN)/demo.o $(BIN)/exception.o $(BIN)/window.o

demo: $(BIN) $(OFILES)
	$(CC) $(CFLAGS) -o demo $(OFILES) $(LIBS)

$(BIN)/demo.o: $(SRC)/demo.cpp $(SRC)/mantis.h
	$(CC) -c $(CFLAGS) -o $(BIN)/demo.o $(SRC)/demo.cpp

$(BIN)/exception.o: $(SRC)/exception.cpp $(SRC)/mantis.h
	$(CC) -c $(CFLAGS) -o $(BIN)/exception.o $(SRC)/exception.cpp

$(BIN)/window.o: $(SRC)/window.cpp $(SRC)/mantis.h
	$(CC) -c $(CFLAGS) -o $(BIN)/window.o $(SRC)/window.cpp
