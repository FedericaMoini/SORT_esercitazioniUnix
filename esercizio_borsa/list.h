#ifndef _LIST_H
#define _LIST_H

#define BOOL int
#define TRUE 1
#define FALSE 0
#define MAX_NAME_LEN 30

typedef struct{
    char name[MAX_NAME_LEN];
    int quantity;
    double price;
    double min_price;
    double total_revenue;
} Stock;

typedef struct NODE{
    Stock stock;
    struct NODE* next;
} NODE;

typedef NODE* LIST;

LIST NewList();
LIST DeleteList(LIST l);
BOOL isEmpty(LIST l);
Stock* Find(LIST l, char* name);
LIST EnqueueOrdered(LIST l, Stock stock);
LIST Dequeue(LIST l, char* name);
void PrintList(LIST l);

#endif