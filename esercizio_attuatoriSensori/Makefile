all: serverH serverS clientH clientS

serverH: serverH.c list.c list.h
	gcc -Wall -o serverH serverH.c list.c

serverS: serverS.c list.c list.h
	gcc -Wall -o serverS serverS.c list.c

clientH: clientH.c list.c list.h
	gcc -Wall -o clientH clientH.c list.c

clientS: clientS.c list.c list.h
	gcc -Wall -o clientS clientS.c list.c

clean:
	rm -f serverH serverS clientH clientS *~
