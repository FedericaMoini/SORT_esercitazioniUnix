#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

LIST NewList(){return NULL;}

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

Stock* Find(LIST l, char* name){
    while(l){
        if(strcmp(l->stock.name, name) == 0){
            return &(l->stock);
        }
        l = l->next;
    }
    return NULL;
}

LIST EnqueueOrdered(LIST l, Stock stock){
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    assert(new_node);
    new_node->stock = stock;
    new_node->next = NULL;

    if(!l || stock.price > l->stock.price){
        new_node->next = l;
        return new_node;
    }

    NODE* curr = l;
    while(curr->next && curr->next->stock.price >= stock.price){
        curr = curr->next;
    }

    new_node->next = curr->next;
    curr->next = new_node;
    return l;
}

LIST Dequeue(LIST l, char* name){
    if(!l) return NULL;
    if(strcmp(l->stock.name, name) == 0){
        NODE* tmp = l;
        l = l->next;
        free(tmp);
        return l; 
    }

    NODE* curr = l;
    while(curr->next && strcmp(curr->next->stock.name, name) != 0){
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
    printf("Titoli quotati:\n");
    while(l){
        printf("%s - Quantità: %d, Prezzo: %.2f, Min Prezzo: %.2f\n", l->stock.name, l->stock.quantity, l->stock.price, l->stock.min_price);
        l= l->next;
    }
}