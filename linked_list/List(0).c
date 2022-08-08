#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define ElemType int

struct Node
{
    ElemType data;
    struct Node *next;
};

typedef struct Node *PtrNode;


int main(void)
{
    struct Node *head = NULL;

    while(true)
    {
        ElemType value;
        printf("Enter an integer: ");
        scanf("%d", &value);

        if(value == EOF)
            break;

        PtrNode n = (PtrNode)malloc(sizeof(struct Node));
        if(!n)
        {
            printf("Malloc is failed!");
            return -1;
        }
        else
        {
            n->data = value;
            n->next = NULL;
        }

        if(head)
        {
            for(PtrNode ptr = head; ptr != NULL; ptr = ptr->next)
            {
                if(!ptr->next)
                {
                    ptr->next = n;
                    break;
                }
            }
        }
        else
            head = n;
    }

    system("pause");
    return 0;       
}