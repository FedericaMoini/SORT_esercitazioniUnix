#ifndef _LIST_H
#define _LIST_H

#define BOOL int
#define FALSE 0
#define TRUE (!FALSE)

typedef struct{
    double value;
} ItemType;

struct LINKED_LIST_NODE{
    ItemType item;
    struct LINKED_LIST_NODE* next;
};

typedef struct LINKED_LIST_NODE NODE;

typedef NODE* LIST;

LIST NewList();
LIST DeleteList(LIST l);

BOOL isEmpty(LIST l);
int getLength(LIST l);

ItemType getHead(LIST l);
ItemType getTail(LIST l);
ItemType* Find(LIST l, ItemType item);

LIST EnqueueFirst(LIST l, ItemType item);
LIST EnqueueLast(LIST l, ItemType item);
LIST EnqueueOrdered(LIST l, ItemType item);
LIST DequeueFirst(LIST l);
LIST DequeueLast(LIST l);
LIST Dequeue(LIST l, ItemType item);

void PrintItem(ItemType item);
void PrintList(LIST l);

#endif