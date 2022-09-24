#include "list.h"
#include <iostream>
#include <cstdlib>

static void CopyNode(ElemType data, PtrNode pnode);

void BuildList(List *pList)
{
    *pList = (Node *)malloc(sizeof(Node));
    if (*pList == NULL)
    {
        std::cerr << "No memory available!\n";
        exit(EXIT_FAILURE);
    }
    else
        (*pList)->next = NULL;
}

bool ListIsEmpty(List head)
{
    return head->next == NULL;
}

bool ListIsFull(List head)
{
    PtrNode pt = (Node *)malloc(sizeof(Node));
    bool full;    
    if (pt == NULL)
        full = true;
    else
        full = false;
    free(pt);

    return full;
}

unsigned int ListCount(List head)
{
    unsigned int cnt = 0;
    PtrNode pnode = head->next;
    while(pnode != NULL)
    {
        cnt++;
        pnode = pnode->next;
    }

    return cnt;
}

static void CopyNode(ElemType data, PtrNode pnode)
{
    pnode->data = data;
}

bool InsertBegin(ElemType data, List head)
{
    PtrNode newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        std::cerr << "No memory available!\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        CopyNode(data, newNode);
        newNode->next = head->next;
        head->next = newNode;
    }
    return true;
}

bool InsertEnd(ElemType data, List head)
{
    PtrNode newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        std::cerr << "No memory available!\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        CopyNode(data, newNode);
        newNode->next = NULL;
        PtrNode ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }
    return true;
}

bool InsertOrderly
(List head, ElemType newData, int (*pfun)(ElemType a, ElemType b))
{
    
    PtrNode ptr = head;
    while(ptr != NULL &&
        ptr->next != NULL &&
        (*pfun)(newData, ptr->next->data) > 0) {
        ptr = ptr->next;
    }
    if (ptr == NULL)
    {
        std::cerr << "List doesn't have a node!\n";
        exit(EXIT_FAILURE);
    }
    PtrNode newNode = (Node *)malloc(sizeof(Node));
    if( newNode == NULL )
    {
        std::cerr << "No memory available!\n";
        exit(EXIT_FAILURE);
    }
    else
    {
        CopyNode(newData, newNode);
        newNode->next = ptr->next;
        ptr->next = newNode;
    }
    return true;
}

void Reverse(List head)
{
    PtrNode ptr = head->next;
    head->next = NULL;
    while (ptr != NULL)
    {
        PtrNode tmp = ptr;
        ptr = ptr->next;
        tmp->next = head->next;
        head->next = tmp;
    }
}

bool DeleteElem(List head, int k)
{
    if (k <= 0)
    {
        std::cerr << "Invalid Input!\n";
        exit(EXIT_FAILURE);
    }
    
    if (ListIsEmpty(head))
    {
        std::cerr << "The list is empty!\n";
        exit(EXIT_FAILURE);
    }

    PtrNode ptr = head;
    int i = 1;
    while (ptr->next != NULL && i < k)
    {
        ptr = ptr->next;
        i++;
    }
    if (ptr->next != NULL && i == k)
    {   
        PtrNode tmp = ptr->next;
        ptr->next = tmp->next;
        free(tmp);
        return true;
    }
    else
        return false;
    
}

void ShowAddress(const List *pList)
{
    using namespace std;
    cout << "\n\nhead: " << pList << endl;
    cout << "empty node : " << *pList << endl;
    int i = 1;
    PtrNode ptr;
    for (ptr = (*pList)->next; ptr != NULL; ptr = ptr->next)
    {
        cout << i++ << "st element: " << ptr << endl;
    }
}

void Traverse(List head, void(*pfun)(ElemType data))
{
    if (ListIsEmpty(head))
    {
        std::cout << "The list is empty!" << std::endl;
        return;
    }

    PtrNode ptr = head->next;
    while(ptr != NULL)
    {
        (*pfun)(ptr->data);
        ptr = ptr->next;
    }
}

void DestroyList(List *pList)
{
    PtrNode psave = NULL;
    while (*pList != NULL)
    {
        psave = (*pList)->next;
        free(*pList);
        *pList = psave;
    }
    
}

bool hasCycle(List head)
{
    if (ListIsEmpty(head))
        return false;
    PtrNode fast = head->next->next;
    PtrNode slow = head->next;
    while (slow != fast) {
        if (fast == NULL || fast->next == NULL)
            return false;
        fast = fast->next->next;
        slow = slow->next;
    }
    return true;
}

ElemType GetElem(List head, int i)
{
    int j = 1;
    PtrNode ptr = head->next;
    while((ptr != NULL) && (j < i))
    {
        ptr = ptr->next;
        j++;
    }

    if (ptr != NULL && j == i)
        return ptr->data;
    else
        return -1; // ElemType: int

}