all: server clientG clientV

server: server.c list.c list.h
	gcc -Wall -o server server.c list.c

clientG: clientG.c
	gcc -Wall -o clientG clientG.c

clientV: clientV.c
	gcc -Wall -o clientV clientV.c

clean:
	rm -f server clientG clientV *~
