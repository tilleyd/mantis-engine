# Makefile for the Mantis Engine project
# Modified: 2017 Nov 20

# The main target creates all the .o files inside the bin directory. You should
# move the folder or the contents of the folder to the rest of your compiled
# .o files. See the demo makefile for an example.

# MACROS

CFLAGS = -Wall
CC     = g++
OFILES = bin/framework.o bin/exception.o bin/window.o bin/loop.o \
	bin/interval_loop.o bin/uncapped_loop.o bin/thread.o bin/image.o \
	bin/image_sheet.o bin/stage.o bin/graphics.o bin/rectangle.o

mantis: bin $(OFILES)

# MANTIS_H

bin/framework.o: framework.cpp mantis.h
	$(CC) -c $(CFLAGS) -o bin/framework.o framework.cpp

bin/graphics.o: graphics.cpp mantis.h
	$(CC) -c $(CFLAGS) -o bin/graphics.o graphics.cpp

bin/window.o: window.cpp mantis.h
	$(CC) -c $(CFLAGS) -o bin/window.o window.cpp

bin/stage.o: stage.cpp mantis.h
	$(CC) -c $(CFLAGS) -o bin/stage.o stage.cpp

# MANTIS_EXCEPTION_H

bin/exception.o: exception.cpp mantis.h
	$(CC) -c $(CFLAGS) -o bin/exception.o exception.cpp

# MANTIS_LOOP_H

bin/loop.o: loop.cpp mantis_loop.h
	$(CC) -c $(CFLAGS) -o bin/loop.o loop.cpp

bin/interval_loop.o: interval_loop.cpp mantis_loop.h
	$(CC) -c $(CFLAGS) -o bin/interval_loop.o interval_loop.cpp

bin/uncapped_loop.o: uncapped_loop.cpp mantis_loop.h
	$(CC) -c $(CFLAGS) -o bin/uncapped_loop.o uncapped_loop.cpp

# MANTIS_THREAD_H

bin/thread.o: thread.cpp mantis_thread.h
	$(CC) -c $(CFLAGS) -o bin/thread.o thread.cpp

# MANTIS_IMAGE_H

bin/image.o: image.cpp mantis_image.h
	$(CC) -c $(CFLAGS) -o bin/image.o image.cpp

bin/image_sheet.o: image_sheet.cpp mantis_image.h
	$(CC) -c $(CFLAGS) -o bin/image_sheet.o image_sheet.cpp

# MANTIS_MATH_H

bin/rectangle.o: math/rectangle.cpp math/mantis_math.h
	$(CC) -c $(CFLAGS) -o bin/rectangle.o math/rectangle.cpp

# UTILS

bin:
	mkdir bin
