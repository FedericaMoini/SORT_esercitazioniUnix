#ifndef LIST_H
#define LIST_H

typedef struct {
	char name[50]; // player name
	int games_played; // number games playes
	int score; 
} Player;

typedef struct Node {
	Player player;
	struct Node* next;
} Node;

typedef Node* LIST;

LIST NewList();
LIST EnqueueLast(LIST list, Player p);
LIST DeleteList(LIST list);
int getLength(LIST list);
Player* Find(LIST list, char* name);
void PrintList(LIST list);


#endif
