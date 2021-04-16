CC = gcc

prog = c
SRC := src
OBJ := bin
FINAL := ../bin

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

flags = -g -Wall -pthread
libs =

c: bin mainbin c_inner move

c_inner: $(OBJECTS)
	$(CC) $(flags)  $^ -o c

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(SRC) $(flags)  -c $< -o $@

bin: 
	mkdir bin

mainbin:
	mkdir -p $(FINAL)

move:
	mv c $(FINAL)

clean:
	rm -f $(OBJ)/*.o $(FINAL)/c
