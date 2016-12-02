BIN = bin
OBJ = obj
SRC = src
TEST = test
FLAGS = -g

all:				make_directories $(BIN)/test

clean:				make_directories $(BIN)/test
				rm -rf $(OBJ)

make_directories:		$(BIN) $(OBJ)

$(BIN):
				mkdir -p $(BIN)

$(OBJ):
				mkdir -p $(OBJ)

$(BIN)/test:			$(OBJ)/test.o $(OBJ)/synthdef.o $(OBJ)/byteio.o
				gcc $(FLAGS) -o $(BIN)/test $(OBJ)/test.o $(OBJ)/synthdef.o $(OBJ)/byteio.o

$(OBJ)/test.o:			$(TEST)/test.c $(SRC)/synthdef.h
				gcc $(FLAGS) -c -o $(OBJ)/test.o $(TEST)/test.c

$(OBJ)/synthdef.o:		$(SRC)/synthdef.c $(SRC)/byteio.h $(SRC)/synthdef.h
				gcc $(FLAGS) -c -o $(OBJ)/synthdef.o $(SRC)/synthdef.c

$(OBJ)/byteio.o:		$(SRC)/byteio.c $(SRC)/byteio.h
				gcc $(FLAGS) -c -o $(OBJ)/byteio.o $(SRC)/byteio.c
