#OBJS specifies which files to compile as part of the project
OBJS = 3dv2.cpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = e

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) -Iinclude/SDL2 -L/lib -w -g -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o build/$(OBJ_NAME)