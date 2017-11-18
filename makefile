# Makefile for the Mantis Engine project
# Author  : Duncan Tilley
# Modified: 2017 Oct 30

SRC    = src
BIN    = bin
CFLAGS = -Wall
LIBS   = -lSDL2 -lpthread
CC     = g++
OFILES = $(BIN)/demo.o $(BIN)/framework.o $(BIN)/exception.o $(BIN)/window.o \
	$(BIN)/interval.o $(BIN)/thread.o $(BIN)/image.o $(BIN)/image_bank.o

demo: $(BIN) $(OFILES)
	$(CC) $(CFLAGS) -o demo $(OFILES) $(LIBS)

# DEMO

$(BIN)/demo.o: $(SRC)/demo.cpp $(SRC)/mantis.h
	$(CC) -c $(CFLAGS) -o $(BIN)/demo.o $(SRC)/demo.cpp

# MANTIS_H

$(BIN)/framework.o: $(SRC)/framework.cpp $(SRC)/mantis.h
	$(CC) -c $(CFLAGS) -o $(BIN)/framework.o $(SRC)/framework.cpp

$(BIN)/exception.o: $(SRC)/exception.cpp $(SRC)/mantis.h
	$(CC) -c $(CFLAGS) -o $(BIN)/exception.o $(SRC)/exception.cpp

$(BIN)/window.o: $(SRC)/window.cpp $(SRC)/mantis.h
	$(CC) -c $(CFLAGS) -o $(BIN)/window.o $(SRC)/window.cpp

# MANTIS_TIMING_H

$(BIN)/interval.o: $(SRC)/interval.cpp $(SRC)/mantis_timer.h
	$(CC) -c $(CFLAGS) -o $(BIN)/interval.o $(SRC)/interval.cpp

# MANTIS_THREAD_H

$(BIN)/thread.o: $(SRC)/thread.cpp $(SRC)/mantis_thread.h
	$(CC) -c $(CFLAGS) -o $(BIN)/thread.o $(SRC)/thread.cpp

# MANTIS_IMAGE_H

$(BIN)/image.o: $(SRC)/image.cpp $(SRC)/mantis_image.h
	$(CC) -c $(CFLAGS) -o $(BIN)/image.o $(SRC)/image.cpp

$(BIN)/image_bank.o: $(SRC)/image_bank.cpp $(SRC)/mantis_image.h
	$(CC) -c $(CFLAGS) -o $(BIN)/image_bank.o $(SRC)/image_bank.cpp

# UTILS

$(BIN):
	mkdir $(BIN)

clean:
	rm -rf $(BIN) demo

run: demo
	./demo
