#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Create new list
LIST NewList(){
	return NULL;
}

// Adds player to the queue
LIST EnqueueLast(LIST list, Player p) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->player = p;
	newNode->next = NULL;

	if(list == NULL) return newNode;

	Node* temp = list;
	while (temp->next != NULL) temp = temp->next;
	temp->next = newNode;

	return list;
}

// Delete list
LIST DeleteList(LIST list) {
	Node* temp;
	while (list != NULL) {
		temp = list;
		list = list->next;
		free(temp);
	}
	return NULL;
}

// Count items number in the list
int getLength(LIST list) {
	int count = 0;
	while (list != NULL) {
		count++;
		list = list->next;
	}
	return count;
}

// Find a player in the list
Player* Find(LIST list, char* name) {
	while (list != NULL) {
		if(strcmp(list->player.name, name) == 0)
			return &list->player;
		list = list->next;
	}
	return NULL;
}

// Print the list
void PrintList(LIST list) {
	while (list != NULL) {
		printf("%s - Game: %d, Score: %d\n",
			list->player.name, list->player.games_played, list->player.score);
		list = list->next;
	}
}
