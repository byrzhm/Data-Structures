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

typedef struct pair
{
    Ptrnode parent;
    Ptrnode child;
} Pair;

// 为单循环链表分配存储空间
void BuildList(List *pList);

bool ListIsEmpty(const List *pList);

bool ListIsFull();

bool InsertEnd(ElemType data, List *pList);

bool InsertBegin(ElemType data, List *pList);

bool InsertOrderly
(List *pList, ElemType newData, int (*pfun)(ElemType a, ElemType b));

void Reverse(List *pList);

ElemType GetElem(List list, int k);

bool DeleteElem(List *pList, int k);

/*
返回两个指针, pair.child 和 pair.parent 
其中 pair.child 指向第k个节点, pair.parent 是它的前驱
*/ 
Pair GetPointer(List list, int k);

/* 删除pair.child 所指的节点 */
bool DeletePointer(List *pList, Pair pair);

void Traverse(const List *pList, void(*pfun)(ElemType data));

void DestroyList(List *pList);

#endif // !CIRCULAR_LIST_H
