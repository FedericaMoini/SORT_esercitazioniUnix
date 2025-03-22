all: server clientA clientI

server: server.c list.c
		gcc -Wall -o server server.c list.c

clientA: clientA.c
		gcc -Wall -o clientA clientA.c

clientI: clientI.c
		gcc -Wall -o clientI clientI.c

clean:
		rm -f server clientA clientI *~

