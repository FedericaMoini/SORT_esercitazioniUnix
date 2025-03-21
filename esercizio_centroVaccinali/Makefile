all: server clientF clientC

server: server.c list.c
	gcc -Wall -o server server.c list.c

clientF: clientF.c
	gcc -Wall -o clientF clientF.c

clientC: clientC.c
	gcc -Wall -o clientC clientC.c

clean:
	rm -f server clientF clientC *~
