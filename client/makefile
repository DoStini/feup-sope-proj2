CC = gcc

prog = c
SRC := src
OBJ := bin

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

flags = -g -Wall -pthread
libs =

c: bin c_inner

c_inner: $(OBJECTS)
	$(CC) $(flags)  $^ -o c

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(SRC) $(flags)  -c $< -o $@

bin: 
	mkdir bin

clean:
	rm -f $(OBJ)/*.o c 
