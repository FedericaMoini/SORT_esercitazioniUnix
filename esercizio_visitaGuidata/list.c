#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

GuideNode* addGuide(GuideNode* head, Guide newGuide){
    GuideNode* newNode = (GuideNode*)malloc(sizeof(GuideNode));
    if(!newNode) return head;

    newNode->guide = newGuide;
    newNode->next = head;

    return newNode;
}

GuideNode* removeGuide(GuideNode* head, const char* guideName){
    GuideNode* curr = head;
    GuideNode* prev = NULL;

    while(curr && strcmp(curr->guide.name, guideName) != 0){
        prev = curr;
        curr = curr->next;
    }

    if(curr){
        if(prev){
            prev->next = curr->next;
        } else {
            head = curr->next;
        }
        free(curr);
    }
    return head;
}

GuideNode* findGuide(GuideNode* head, int numVisitors){
    GuideNode* bestGuide = NULL;

    while(head){
        if(head->guide.current_visitors + numVisitors <= head->guide.max_visitors){
            if(!bestGuide || head->guide.max_visitors < bestGuide->guide.max_visitors){
                bestGuide = head;
            }
        }

        head = head->next;
    }

    return bestGuide;
}

VisitorNode* addVisitor(VisitorNode* head, VisitorGroup newGroup){
    VisitorNode* newNode = (VisitorNode*)malloc(sizeof(VisitorNode));
    if(!newNode) return head;

    newNode->group = newGroup;
    newNode->next = head;
    return newNode;
}

VisitorNode* removeFirstVisitor(VisitorNode* head){
    if(!head) return NULL;

    VisitorNode* tmp = head;
    head = head->next;
    free(tmp);
    return head;
}

int countTotalVisitors(VisitorNode* head){
    int count = 0;
    while(head){
        count += head->group.num_visitors;
        head = head->next;
    }
    return count;
}