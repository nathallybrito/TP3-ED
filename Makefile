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
OBJS = $(OBJ)/main.o $(OBJ)/grafo.o
HDRS = $(INC)/grafo.hpp
CFLAGS = -Wall -c -g -I$(INC)

EXE = $(BIN)/tp2.out

run:  $(EXE)
	 ./$(EXE)

all:  $(EXE)


	
$(BIN)/tp2.out: $(OBJS)
	$(CC) -g -o $(BIN)/tp2.out $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/grafo.o: $(HDRS) $(SRC)/grafo.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/grafo.o $(SRC)/grafo.cpp  

 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out