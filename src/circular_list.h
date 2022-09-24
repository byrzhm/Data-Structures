#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

typedef int ElemType;

typedef struct node
{
    ElemType data;
    struct node *next;
} Node;

typedef Node *Ptrnode;
typedef struct list
{
    int size;
    Ptrnode head;
    Ptrnode tail;
} List;

void BuildList(List *pList);

bool ListIsEmpty(const List *pList);

bool ListIsFull();

bool InsertEnd(ElemType data, List *pList);

bool InsertBegin(ElemType data, List *pList);

bool InsertOrderly
(List *pList, ElemType newData, int (*pfun)(ElemType a, ElemType b));

void Reverse(List *pList);

bool DeleteElem(List *pList, int k);

void Traverse(const List *pList, void(*pfun)(ElemType data));

void DestroyList(List *pList);

#endif // !CIRCULAR_LIST_H
