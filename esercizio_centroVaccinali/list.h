#ifndef _LIST_H
#define _LIST_H

#define BOOL int
#define FALSE 0
#define TRUE 1
#define MAX_NAME_LEN 50

/* Struttura per i fornitori */
typedef struct{
    char name[MAX_NAME_LEN];
    int supply;
    int min_demand;
} Supplier;

/* Struttura per i centri vaccinali */
typedef struct{
    char name[MAX_NAME_LEN];
    int demand;
} Center;

/* Nodo per la lista */
typedef struct NODE {
    void* data;
    struct NODE* next;
} NODE;

typedef NODE* LIST;

/* Funzioni per la gestione delle liste */
LIST NewList();
LIST DeleteList(LIST l);
BOOL isEmpty(LIST l);
int getLength(LIST l);
void* Find(LIST l, char* name, int isSupplier);
LIST EnqueueOrdered(LIST l, void* data, int isSupplier);
LIST Dequeue(LIST l, char* name);
void PrintSuppliers(LIST l);
void PrintCenters(LIST l);

#endif