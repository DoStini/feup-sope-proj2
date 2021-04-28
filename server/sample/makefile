FINAL := ../../bin

all: s mainbin move

s: server.o lib.o delay.c delay.h
	gcc -Wall -DDELAY=100 -o s delay.c lib.o server.o -pthread

mainbin:
	mkdir -p $(FINAL)

move:
	mv s $(FINAL)

# c: client.c common.h
# 	gcc -Wall -o c client.c -pthread

# server.o: server.c common.h
# 	gcc -Wall -c -o server.o server.c
#
# lib.o: lib.c lib.h
# 	gcc -Wall -c -o lib.o lib.c

clean:
	rm -f $(FINAL)/s
