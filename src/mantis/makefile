# Makefile for the Mantis Engine project

# The main target creates the .a library file inside the lib directory. You
# should move the folder or the contents of the folder to the rest of your
# library files and link the library. See the demo makefile for an example.

# MACROS

CFLAGS = -Wall
CC     = g++
LIBNAME = libmantis.a
OFILES = lib/framework.o lib/exception.o lib/window.o lib/loop.o \
	lib/interval_loop.o lib/uncapped_loop.o lib/thread.o lib/image.o \
	lib/image_sheet.o lib/stage.o lib/graphics.o lib/rectangle.o \
	lib/ui_component.o lib/ui_button.o lib/vector2d.o lib/image_bank.o

mantis: lib lib/$(LIBNAME)

lib/$(LIBNAME): $(OFILES)
	ar -rcs lib/$(LIBNAME) $(OFILES)
	rm lib/*.o

# MANTIS_H

lib/framework.o: framework.cpp mantis.h
	$(CC) -c $(CFLAGS) -o lib/framework.o framework.cpp

lib/graphics.o: graphics.cpp mantis.h
	$(CC) -c $(CFLAGS) -o lib/graphics.o graphics.cpp

lib/window.o: window.cpp mantis.h
	$(CC) -c $(CFLAGS) -o lib/window.o window.cpp

# MANTIS_STAGE_H

lib/stage.o: stage.cpp mantis_stage.h
	$(CC) -c $(CFLAGS) -o lib/stage.o stage.cpp

# MANTIS_EXCEPTION_H

lib/exception.o: exception.cpp mantis.h
	$(CC) -c $(CFLAGS) -o lib/exception.o exception.cpp

# MANTIS_LOOP_H

lib/loop.o: loop.cpp mantis_loop.h
	$(CC) -c $(CFLAGS) -o lib/loop.o loop.cpp

lib/interval_loop.o: interval_loop.cpp mantis_loop.h
	$(CC) -c $(CFLAGS) -o lib/interval_loop.o interval_loop.cpp

lib/uncapped_loop.o: uncapped_loop.cpp mantis_loop.h
	$(CC) -c $(CFLAGS) -o lib/uncapped_loop.o uncapped_loop.cpp

# MANTIS_THREAD_H

lib/thread.o: thread.cpp mantis_thread.h
	$(CC) -c $(CFLAGS) -o lib/thread.o thread.cpp

# MANTIS_IMAGE_H

lib/image.o: image.cpp mantis_image.h
	$(CC) -c $(CFLAGS) -o lib/image.o image.cpp

lib/image_sheet.o: image_sheet.cpp mantis_image.h
	$(CC) -c $(CFLAGS) -o lib/image_sheet.o image_sheet.cpp

lib/image_bank.o: image_bank.cpp mantis_image.h
	$(CC) -c $(CFLAGS) -o lib/image_bank.o image_bank.cpp

# MANTIS_UI_H

lib/ui_component.o: ui_component.cpp mantis_ui.h
	$(CC) -c $(CFLAGS) -o lib/ui_component.o ui_component.cpp

lib/ui_button.o: ui_button.cpp mantis_ui.h
	$(CC) -c $(CFLAGS) -o lib/ui_button.o ui_button.cpp

# MANTIS_MATH_H

lib/rectangle.o: math/rectangle.cpp math/mantis_math.h
	$(CC) -c $(CFLAGS) -o lib/rectangle.o math/rectangle.cpp

lib/vector2d.o: math/vector2d.cpp math/mantis_math.h
	$(CC) -c $(CFLAGS) -o lib/vector2d.o math/vector2d.cpp

# UTILS

lib:
	mkdir lib
