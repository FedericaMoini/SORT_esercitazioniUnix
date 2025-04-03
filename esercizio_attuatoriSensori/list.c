#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int itemCompare(ItemType item1, ItemType item2){
    if(item1.value > item2.value) return 1;
    else if(item1.value < item2.value) return -1;
    else return 0;
}

NODE* createNode(ItemType item){
    NODE* p = (NODE*)malloc(sizeof(NODE));
    assert(p != NULL);

    p->item = item;
    p->next = NULL;
    return p;
}

void deleteNode(NODE* p){
    free(p);
}

LIST NewList(){
    return NULL;
}

LIST DeleteList(LIST l){
    LIST tmp = l;
    while(!isEmpty(tmp)){
        NODE* todel = tmp;
        tmp = tmp->next;
        deleteNode(todel);
    }
    return NewList();
}

BOOL isEmpty(LIST l){
    return l == NULL;
}

int getLength(LIST l){
    int size = 0;
    LIST tmp = l;
    while(!isEmpty(tmp)){
        ++size;
        tmp = tmp->next;
    }
    return size;
}

ItemType getHead(LIST l){
    assert(!isEmpty(l));
    return l->item;
}

ItemType getTail(LIST l){
    NODE* tmp = l;
    assert(!isEmpty(l));
    while(!isEmpty(tmp->next)){
        tmp = tmp->next;
    }
    return tmp->item;
}

ItemType* Find(LIST l, ItemType item){
    LIST tmp = l;
    while(tmp != NULL && itemCompare(tmp->item, item) != 0){
        tmp = tmp->next;
    }
    if(tmp == NULL) return NULL;
    return &(tmp->item);
}

LIST EnqueueFirst(LIST l, ItemType item){
    NODE* new_node = createNode(item);
    new_node->next = l;
    return new_node;
}

LIST EnqueueLast(LIST l, ItemType item){
    NODE* new_node = createNode(item);
    if(isEmpty(l)) return new_node;
    LIST tmp = l;
    while(!isEmpty(tmp->next)) tmp = tmp->next;
    tmp->next = new_node;
    return l;
}

LIST EnqueueOrdered(LIST l, ItemType item){
    NODE* new_node = createNode(item);
    if(isEmpty(l) || itemCompare(item, l->item) < 0){
        new_node->next = l;
        return new_node;
    }
    LIST tmp = l;
    while(!isEmpty(tmp->next) && itemCompare(tmp->next->item, item) < 0){
        tmp = tmp->next;
    }
    new_node->next = tmp->next;
    tmp->next = new_node;
    return l;
}

LIST DequeueFirst(LIST l){
    if(!isEmpty(l)){
        NODE* todel = l;
        l = l->next;
        deleteNode(todel);
    }
    return l;
}

LIST DequeueLast(LIST l){
    if(isEmpty(l)) return l;
    if(l->next == NULL){
        deleteNode(l);
        return NULL;
    }

    LIST tmp = l;
    while(tmp->next->next != NULL) tmp = tmp->next;
    deleteNode(tmp->next);
    tmp->next = NULL;
    return l;
}

LIST Dequeue(LIST l, ItemType item){
    if(isEmpty(l)){
        if(itemCompare(l->item, item) == 0){
            NODE* todel = l;
            l = l->next;
            deleteNode(todel);
        } else{
            LIST tmp = l;
            while(!isEmpty(tmp->next) && itemCompare(tmp->next->item, item) != 0) tmp = tmp->next;
            if(!isEmpty(tmp->next)){
                NODE* todel = tmp->next;
                tmp->next = tmp->next->next;
                deleteNode(todel);
            }
        }
    }
    return l;
}

void PrintItem(ItemType item){
    printf("%f", item.value);
}

void PrintList(LIST l){
    LIST tmp = l;
    while(!isEmpty(tmp)){
        PrintItem(tmp->item);
        tmp = tmp->next;
        if(!isEmpty(tmp)) printf(" ");
    }
}