all: server clientC clientL

server: server.c list.c
	gcc -Wall -o server server.c list.c

clientC: clientC.c
	gcc -Wall -o clientC clientC.c

clientL: clientL.c
	gcc -Wall -o clientL clientL.c

clean:
	rm -f server clientC clientL *~