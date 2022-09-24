/*
有头结点的单链表
*/

#ifndef LIST_H
#define LIST_H

typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node *next;
} Node;
typedef Node *PtrNode;
typedef Node *List;

void BuildList(List *pList);

bool ListIsEmpty(List head);

bool ListIsFull(List head);

unsigned int ListCount(List head);

bool InsertBegin(ElemType data, List head);

bool InsertEnd(ElemType data, List head);

bool InsertOrderly
(List head, ElemType newData, int (*pfun)(ElemType a, ElemType b));

void Reverse(List head);

bool DeleteElem(List head, int k);

void ShowAddress(const List *pList);

void Traverse(List head, void(*pfun)(ElemType data));

void DestroyList(List *pList);

bool hasCycle(List head);

ElemType GetElem(List head, int i);


#endif // LIST_H