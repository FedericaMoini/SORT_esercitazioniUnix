#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

LIST NewList() {return NULL;}

LIST DeleteList(LIST l){
    NODE* tmp;
    while(l){
        tmp = l;
        l = l->next;
        free(tmp);
    }
    return NULL;
}

BOOL isEmpty(LIST l){return l == NULL;}

int getLength(LIST l){
    int count = 0;
    while(l){
        count++;
        l = l ->next;
    }
    return count;
}

Book* Find(LIST l, char* title){
    while(l){
        if(strcmp(l->book.title, title) == 0){
            return &(l->book);
        }
        l = l->next;
    }
    return NULL;
}

LIST EnqueueOrdered(LIST l, Book book){
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    assert(new_node);
    new_node->book = book;
    new_node->next = NULL;
    if(!l || strcmp(book.title, l->book.title) < 0){
        new_node->next = l;
        return new_node;
    }

    NODE* curr = l;
    while(curr->next
     && strcmp(curr->next->book.title, book.title) < 0){
        curr = curr->next;
     }
     new_node->next = curr->next;
     curr->next = new_node;
     return l;
}

LIST Dequeue(LIST l, char* title){
    if(!l) return NULL;
    if(strcmp(l->book.title, title) == 0){
        NODE* tmp = l;
        l = l->next;
        free(tmp);
        return l;
    }

    NODE* curr = l;
    while(curr->next && strcmp(curr->next->book.title, title) != 0){
        curr = curr->next;
    }
    if(curr->next){
        NODE* tmp = curr->next;
        curr->next = tmp->next;
        free(tmp);
    }
    return l;
}

void PrintList(LIST l){
    while(l){
        printf("%s: %d copies\n", l->book.title, l->book.quantity);
        l = l->next;
    }
}