CC = gcc

prog = s
SRC := src
COMMON := ../common
OBJ := bin
FINAL := ../bin

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

flags = -g -Wall 
libs = -pthread -lrt

s: bin mainbin s_inner move

s_inner: $(OBJECTS)
	$(CC) $(flags)  $^ -o s $(libs)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(SRC) $(flags)  -c $< -o $@ $(libs)

bin: 
	mkdir -p bin

mainbin:
	mkdir -p $(FINAL)

move:
	mv s $(FINAL)

clean:
	rm -f $(OBJ)/*.o $(FINAL)/s
