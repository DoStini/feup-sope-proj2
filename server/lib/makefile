# all: s c

# s: server.o lib.o delay.c delay.h
# 	gcc -Wall -DDELAY=100 -o s delay.c lib.o server.o -pthread
#
# c: client.c common.h
# 	gcc -Wall -o c client.c -pthread
#
# server.o: server.c common.h
# 	gcc -Wall -c -o server.o server.c

all: delay.o lib.o

lib.o: lib.c lib.h
	gcc -Wall -c -o lib.o lib.c

delay.o: delay.c delay.h
	gcc -Wall -c -o delay.o delay.c

clean:
	rm -f lib.o
