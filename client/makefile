CC = gcc

prog = c
SRC := src
COMMON := ../common
OBJ := bin
FINAL := ../bin

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

flags = -g -Wall 
libs = -pthread -lrt

c: bin c_inner move

c_inner: $(OBJECTS)
	$(CC) $(flags)  $^ -o c $(libs)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -I$(SRC) $(flags)  -c $< -o $@ $(libs)

bin: 
	mkdir bin

mainbin:
	mkdir -p $(FINAL)

move:
	mv c $(FINAL)

clean:
	rm -f $(OBJ)/*.o $(FINAL)/c
