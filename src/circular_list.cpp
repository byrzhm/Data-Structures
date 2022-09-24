#include "circular_list.h"
#include <iostream>
#include <cstdlib>

using std::cout;
using std::cerr;
using std::endl;

static void CopyData(ElemType data, Ptrnode pnode);

void BuildList(List *pList)
{
    (*pList).head = (Node *)malloc(sizeof(Node));
    if ((*pList).head == NULL)
    {
        cerr << "No memory available!\n";
        exit(EXIT_FAILURE);
    }
    (*pList).head->next = (*pList).head;
    (*pList).tail = (*pList).head;
    (*pList).size = 0;
}

bool ListIsEmpty(const List *pList)
{
    // return (*pList).head->next == (*pList).head;
    return (*pList).size == 0;
}

bool ListIsFull()
{
    bool full;
    Ptrnode tp = (Node *)malloc(sizeof(Node));
    if(tp == NULL)
        full = true;
    else
        full = false;
    return full;
}

static void CopyData(ElemType data, Ptrnode pnode)
{
    pnode->data = data;
}

bool InsertEnd(ElemType data, List *pList)
{
    Ptrnode pnode = (Node *)malloc(sizeof(Node));
    if (pnode == NULL)
    {
        cerr << "No memory available!\n";
        exit(EXIT_FAILURE);
    }
    
    CopyData(data, pnode);
    pnode->next = (*pList).tail->next;
    (*pList).tail->next = pnode;
    (*pList).size++;
    (*pList).tail = pnode;

    return true;
}

bool InsertBegin(ElemType data, List *pList)
{
    Ptrnode pnode = (Node *)malloc(sizeof(Node));
    if (pnode == NULL)
    {
        cerr << "No memory available!\n";
        exit(EXIT_FAILURE);
    }
    CopyData(data, pnode);
    pnode->next = (*pList).head->next;
    (*pList).head->next = pnode;
    if (ListIsEmpty(pList))   
        (*pList).tail = pnode;
    (*pList).size++;
    return true;
}

bool InsertOrderly
(List *pList, ElemType newData, int (*pfun)(ElemType a, ElemType b))
{
    Ptrnode newNode = (Node *)malloc(sizeof(Node));
    if( newNode == NULL )
    {
        cerr << "No memory available!\n";
        exit(EXIT_FAILURE);
    }
    Ptrnode ptr = (*pList).head;
    while(ptr->next != (*pList).head &&
        (*pfun)(newData, ptr->next->data) > 0) {
        ptr = ptr->next;
    }
    if (ptr->next == (*pList).head)
        (*pList).tail = newNode;
    CopyData(newData, newNode);
    newNode->next = ptr->next;
    ptr->next = newNode;
    (*pList).size++;
    return true;
}

void Reverse(List *pList)
{
    bool ChangeTail = true;
    if (pList->size < 2)
        return;
    Ptrnode ptr = (*pList).head->next;
    (*pList).head->next = (*pList).head;
    while(ptr != (*pList).head)
    {
        Ptrnode tp = ptr;
        ptr = ptr->next;
        tp->next = (*pList).head->next;
        (*pList).head->next = tp;
        if (ChangeTail)
        {
            (*pList).tail = tp;
            ChangeTail = false;
        }
    }
}

bool DeleteElem(List *pList, int k)
{
    if (k <= 0 || k > pList->size)
    {
        cerr << "Invalid Input!\n";
        return false;
    }
    int i = 1;
    Ptrnode pnode = (*pList).head;
    while(i < k) {
        pnode = pnode->next;
        i++;
    }
    Ptrnode tp = pnode->next;
    pnode->next = tp->next;
    if (k == (*pList).size)
        (*pList).tail = pnode;
    free(tp);
    (*pList).size--;
    return true;
}

void Traverse(const List *pList, void(*pfun)(ElemType data))
{
    if (ListIsEmpty(pList))
    {
        cout << "The list is empty!" << endl;
        return;
    }

    Ptrnode ptr = (*pList).head->next;
    while(ptr != (*pList).head)
    {
        (*pfun)(ptr->data);
        ptr = ptr->next;
    }
}

void DestroyList(List *pList)
{
    Ptrnode pSave = NULL, head = (*pList).head;
    (*pList).head = NULL;
    (*pList).tail->next = NULL;
    (*pList).size = 0;
    while (head != NULL)
    {
        pSave = head->next;
        free(head);
        head = pSave;
    }
}