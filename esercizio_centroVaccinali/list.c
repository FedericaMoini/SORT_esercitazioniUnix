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
        free(tmp->data);
        free(tmp);
    }

    return NULL;
}

BOOL isEmpty(LIST l){return l == NULL;}

int getLength(LIST l){
    int count = 0;
    while(l){
        count++;
        l = l->next;
    }
    return count;
}

void* Find(LIST l, char* name, int isSupplier){
    while(l){
        if(isSupplier){
            Supplier* s = (Supplier*)l->data;
            if(strcmp(s->name, name) == 0){
                return s;
            }
        } else {
            Center* c = (Center*)l->data;
            if(strcmp(c->name, name) == 0){
                return c;
            }
        }
        l = l->next;
    }
    return NULL;
}

LIST EnqueueOrdered(LIST l, void* data, int isSupplier){
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    assert(new_node);
    new_node->data = data;
    new_node->next = NULL;

    if(!l) return new_node;

    NODE* curr = l;
    if(isSupplier){
        Supplier* new_supplier = (Supplier*)data;
        Supplier* first_supplier = (Supplier*)curr->data;
        if(new_supplier->supply > first_supplier->supply){
            new_node->next = l;
            return new_node;
        }
    } else {
        Center* new_center = (Center*)data;
        Center* first_center = (Center*)curr->data;
        if(new_center->demand > first_center->demand){
            new_node->next = l;
            return new_node;
        }
    }

    while(curr->next){
        if(isSupplier){
            Supplier* next_supplier = (Supplier*)curr->next->data;
            if(((Supplier*)data)->supply > next_supplier->supply) break;
        } else {
            Center* next_center = (Center*)curr->next->data;
            if(((Center*)data)->demand > next_center->demand) break;
        }
        curr = curr->next;
    }

    new_node->next = curr->next;
    curr->next = new_node;
    return l;
}

LIST Dequeue(LIST l, char* name){
    if(!l) return NULL;

    if(strcmp(((Supplier*)l->data)->name, name) == 0 || strcmp(((Center*)l->data)->name, name) == 0){
        NODE* tmp = l;
        l = l->next;
        free(tmp->data);
        free(tmp);
        return l;
    }

    NODE* curr = l;
    while(curr->next){
        if(strcmp(((Supplier*)curr->next->data)->name, name) == 0 || strcmp(((Center*)curr->next->data)->name, name) == 0){
            NODE* tmp = curr->next;
            curr->next = tmp->next;
            free(tmp->data);
            free(tmp);
            return l;
        }
        curr = curr->next;
    }
    return l;
}

void PrintSuppliers(LIST l){
    printf("Lista Fornitori:\n");
    while(l){
        Supplier* s = (Supplier*)l->data;
        printf("Fornitore: %s, Vaccini: %d, Min Richiesta: %d\n", s->name, s->supply, s->min_demand);
        l = l->next;
    }
}

void PrintCenters(LIST l){
    printf("Lista Centri Vaccinali:\n");
    while(l){
        Center* c = (Center*)l->data;
        printf("Centro: %s, Richiesta: %d\n", c->name, c->demand);
        l = l->next;
    }
}