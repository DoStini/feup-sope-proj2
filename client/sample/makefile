FINAL := ../../bin

all: c mainbin move

# s: server.o lib.o delay.c delay.h
# 	gcc -Wall -DDELAY=100 -o s delay.c lib.o server.o -pthread

c: client.c common.h
	gcc -Wall -o c client.c -pthread

mainbin:
	mkdir -p $(FINAL)

move:
	mv c $(FINAL)

clean:
	rm -f $(FINAL)/c
