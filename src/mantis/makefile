# Makefile for the Mantis Engine project
# Modified: 2017 Nov 20

# The main target creates all the .o files inside the bin directory. You should
# move the folder or the contents of the folder to the rest of your compiled
# .o files. See the demo makefile for an example.

# MACROS

CFLAGS = -Wall
CC     = g++
OFILES = bin/framework.o bin/exception.o bin/window.o \
	bin/interval.o bin/thread.o bin/image.o bin/image_bank.o bin/stage.o

mantis: bin $(OFILES)

# MANTIS_H

bin/framework.o: framework.cpp mantis.h
	$(CC) -c $(CFLAGS) -o bin/framework.o framework.cpp

bin/window.o: window.cpp mantis.h
	$(CC) -c $(CFLAGS) -o bin/window.o window.cpp

bin/stage.o: stage.cpp mantis.h
	$(CC) -c $(CFLAGS) -o bin/stage.o stage.cpp

# MANTIS_EXCEPTION_H

bin/exception.o: exception.cpp mantis.h
	$(CC) -c $(CFLAGS) -o bin/exception.o exception.cpp

# MANTIS_TIMING_H

bin/interval.o: interval.cpp mantis_timer.h
	$(CC) -c $(CFLAGS) -o bin/interval.o interval.cpp

# MANTIS_THREAD_H

bin/thread.o: thread.cpp mantis_thread.h
	$(CC) -c $(CFLAGS) -o bin/thread.o thread.cpp

# MANTIS_IMAGE_H

bin/image.o: image.cpp mantis_image.h
	$(CC) -c $(CFLAGS) -o bin/image.o image.cpp

bin/image_bank.o: image_bank.cpp mantis_image.h
	$(CC) -c $(CFLAGS) -o bin/image_bank.o image_bank.cpp

# UTILS

bin:
	mkdir -p bin

clean:
	rm -rf bin
