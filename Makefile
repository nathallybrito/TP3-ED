#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa main
# Autor		: Náthally Fernandes (nathallyfernandes@ufmg.br)
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#           : make run - compila o exécutavel 
#			: make clean - remove objetos e executável
#---------------------------------------------------------------------
CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/segTree.o
HDRS = $(INC)/segTree.hpp
CFLAGS = -Wall -c -g -I$(INC)

EXE = $(BIN)/tp3.out

run:  $(EXE)
	 ./$(EXE)

all:  $(EXE)

$(BIN)/tp3.out: $(OBJS)
	$(CC) -g -o $(BIN)/tp3.out $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/segTree.o: $(HDRS) $(SRC)/segTree.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/segTree.o $(SRC)/segTree.cpp  

 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out