all: player server

player: player.c list.c
	gcc -Wall -o player player.c list.c

server: server.c list.c
	gcc -Wall -o server server.c list.c

clean:
	rm -f player servr *~
