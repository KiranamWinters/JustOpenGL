#Compiler
CC = clang

#Shell 
SHELL = /bin/sh

#Name of Target
NAME = Graphics

OBJFILE = objs/

#flags
CFLAGS = -Wall

#Object Files
OBJECTS = $(wildcard objs/*.o)

#Source files
SRC = $(wildcard src/*.c)

#include path
INCLUDE = -Iheader

#libraries
LIBS = -L/home/kiranam/Projects/OpenGL/lib -lGL -lglfw3 -lX11 -lpthread -lXrandr -lXi -ldl


Graphics:
	$(CC) $(CFLAG) `pkg-config --static --libs glfw3` $(INCLUDE)  -o $(NAME) $(SRC) $(LIBS) && ./Graphics
	
clean:
	rm -f objs/*.o Graphics
