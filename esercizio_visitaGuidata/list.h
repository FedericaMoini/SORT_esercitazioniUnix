#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

#define MAX_NAME_LENGTH 30

typedef struct Guide {
    char name[MAX_NAME_LENGTH];
    int min_visitors;
    int max_visitors;
    int current_visitors;
} Guide;

typedef struct GuideNode{
    Guide guide;
    struct GuideNode* next;
} GuideNode;

typedef struct{
    int num_visitors;
} VisitorGroup;

typedef struct VisitorNode{
    VisitorGroup group;
    struct VisitorNode* next;
} VisitorNode;

GuideNode* addGuide(GuideNode* head, Guide newGuide);
GuideNode* removeGuide(GuideNode* head, const char* guideName);
GuideNode* findGuide(GuideNode* head, int numVisitors);

VisitorNode* addVisitor(VisitorNode* head, VisitorGroup newGroup);
VisitorNode* removeFirstVisitor(VisitorNode* head);
int countTotalVisitors(VisitorNode* head);

#endif