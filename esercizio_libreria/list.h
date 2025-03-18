#ifndef _LIST_H
#define _LIST_H

#define BOOL int
#define FALSE 0
#define MAX_TITLE_LEN 50

/* Definizione struttura book */
typedef struct {
    char title[MAX_TITLE_LEN];
    int quantity;
} Book;

/* Definizione struttura nodo della lista */
typedef struct NODE{
    Book book;
    struct NODE* next;
} NODE;

typedef NODE* LIST;

LIST NewList();
LIST DeleteList(LIST l);
BOOL isEmpty(LIST l);
int getLength(LIST l);
Book* Find(LIST l, char* title);
LIST EnqueueOrdered(LIST l, Book book);
LIST Dequeue(LIST l, char* title);
void PrintList(LIST l);
#endif