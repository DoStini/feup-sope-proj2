CC = gcc

prog = s
SRC := src
INCLUDES := .
COMMON := ../
OBJ := bin
FINAL := ../bin

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

flags = -g -Wall 
libs = -pthread -lrt

s: bin s_inner move

s_inner: $(OBJECTS) lib/lib.o lib/delay.o
	$(CC) $(flags)  $^ -o s $(libs) -I $(INCLUDES)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(SRC) $(flags)  -c $< -o $@ $(libs) -I $(INCLUDES) -I $(COMMON)

bin: 
	mkdir -p bin

mainbin:
	mkdir -p $(FINAL)

move:
	mv s $(FINAL)

clean:
	rm -f $(OBJ)/*.o $(FINAL)/s
