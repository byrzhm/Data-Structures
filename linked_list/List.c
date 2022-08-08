#include<stdio.h>
#include<stdlib.h>

#define ElemType int
struct Node{
	ElemType data;
	struct Node *next; 
};

typedef struct Node * PtrNode;

/*��ʼ��һ�����սڵ�Ŀ�����*/
PtrNode initEmptyList ();
/*�����½ڵ㵽����β��*/
void insertEnd(PtrNode , ElemType );
/*���������β�ڵ㣬������ָ��β�ڵ��βָ��*/
PtrNode getEnd(PtrNode);
/*�����½ڵ㵽����ͷ��*/
void insertBegin(PtrNode , ElemType );
/*�����½ڵ㵽���������ʵ�λ��*/
void insertUp(PtrNode , ElemType );
/*ɾ�������ͷ�ڵ�*/
void deleteBegin(PtrNode);
/*ɾ�������β�ڵ�*/
void deleteEnd(PtrNode);
/*�ж������Ƿ�Ϊ�գ�����1�����򷵻�0*/
int isEmpty(PtrNode);
/*ɾ��ָ��ֵ�ĵ�һ���ڵ㣬�ɹ��򷵻�1�����򷵻�0��*/
int deleteNode(PtrNode head,ElemType x);
/*ɾ��ָ��ֵ�����нڵ㣬�ɹ��򷵻�ɾ�����������򷵻�0*/
int deleteVal(PtrNode head,ElemType x);
/*����������ӡÿ���ڵ�����*/
void printList(PtrNode);
/*��������ָ���ʼ״̬*/
void clearList(PtrNode); 
/*�ͷ��������������սڵ㣬����ͷָ��Ϊ��*/
void destroyList(PtrNode *); 
/*����������Ч�ڵ���������*/
int getSize (PtrNode);
/*����ֵΪx�ĵ�һ���ڵ㣬����ָ�룬ʧ�ܷ���NULL*/
PtrNode find(PtrNode, ElemType x);
/*���������е�n���ڵ㣬���ؽڵ�ָ�룬ʧ�ܷ���NULL*/
PtrNode findNth(PtrNode head, int n);

/*���ȥ�غ������ɹ��򷵻�ɾ�����������򷵻�0*/
int unique(PtrNode head);
/*���������и���ֵ�ĳ��ִ���*/
int countVal( PtrNode head, ElemType x );

/*����ֵΪx�ĵ�һ���ڵ㣬���ؽڵ��ǰ��ָ�룬ʧ�ܷ���NULL*/
PtrNode findPre(PtrNode head, ElemType x); 
/*ɾ��ָ��ָ��λ�õĺ�̽ڵ㣬�ɹ�����1��ʧ�ܷ���0*/
int eraseByPre(PtrNode pre);


/*������Ԫ��ֵ������������ʹ��ѡ�������㷨*/
void selectSortList(PtrNode head);
/*���������нڵ�����*/
void reverseList(PtrNode head);
/*����(����)����Ĺ鲢����*/
void sortedMerge(PtrNode head1, PtrNode head2);

/*����һ�����սڵ�ĳ�ʼѭ��������*/
PtrNode  initCirList();
/*����ѭ����������ӡ�ڵ�*/
void printCirList(PtrNode head);
/*����ѭ���������β�ڵ㣬������ָ��β�ڵ��βָ��*/
PtrNode getCirEnd(PtrNode head);
/*��һ���½ڵ���뵽ѭ������β��*/
void insertCirEnd(PtrNode head, ElemType x);
/*Լɪ��������n/m��⣬ֻʣһ���ڵ�*/
void doneJosephCir(PtrNode head, int n, int m);

void destroyCirList(PtrNode * headPtr);


int main(void)
{
	PtrNode head = NULL;
	head=initCirList();
	printCirList(head);
	destroyCirList(&head);
	return 0;

}


/*����һ�����սڵ�ĳ�ʼ����*/
PtrNode initEmptyList ()
{
    PtrNode head = ( PtrNode )malloc( sizeof( struct Node ) );
    if( !head )
    {
        printf("No memory avaliable.\n");
        return NULL;
    }   
    else
    {
        head->next = NULL;
        return head;
    }
}


/*�ж������Ƿ�Ϊ�գ�����1�����򷵻�0*/
int isEmpty(PtrNode head)
{
    return head->next == NULL;
}


/*����������ӡÿ���ڵ�����*/
void printList(PtrNode head)
{
    if( head->next == NULL )
        printf("List is empty!");
    else
    {
        printf("The list is:\n");
        /*�����սڵ�*/
        for( PtrNode cur = head->next; cur; cur = cur->next)
            printf("%d-->",cur->data);
        printf("NULL\n\n");
    }
}


/*���������β�ڵ㣬������ָ��β�ڵ��βָ��*/
PtrNode getEnd(PtrNode head)
{
    PtrNode cur, tmp;
    tmp = head;
    cur = head->next;   /*�����սڵ�*/
    while ( cur )
    {
        tmp = cur;
        cur = cur->next;
    }
    return tmp;
}


/*��һ���½ڵ���뵽����β��*/
void insertEnd (PtrNode head, ElemType x)
{
    PtrNode p, tmp;
    /*��̬�����½ڵ㣬����ֵ����*/
    p = ( PtrNode )malloc( sizeof( struct Node ) );

    if( !p )
        printf("Not inserted. No memory avaliable.\n");
    else
    {
        p->data = x;
        p->next = NULL;

        /*�ҵ�β�ڵ㣬��Ϊǰ��ָ��tmp*/
        tmp = getEnd( head );

        /*��β�ڵ�������½ڵ�*/
        tmp->next = p;
    }

}


/*��һ���½ڵ���뵽����ͷ��*/
void insertBegin(PtrNode head , ElemType x)
{
    PtrNode p, cur;
    /*��̬�����½ڵ㣬����ֵ����*/
    p = ( PtrNode )malloc( sizeof( struct Node ) );

    if( !p )
        printf("Not inserted. No memory avaliable.\n");
    else
    {
        p->data = x;
        /*ֱ���ڿսڵ�������½ڵ�*/
        cur = head->next;
        p->next = cur;
        head->next = p;
    }
}


/*��һ���½ڵ���뵽����������*/
void insertUp(PtrNode head, ElemType x)
{
    PtrNode p, cur, tmp;
    /*��̬�����½ڵ㣬����ֵ����*/
    p = ( PtrNode )malloc( sizeof( struct Node ) );

    if( !p )
        printf("Not inserted. No memory avaliable.\n");
    else
    {
        p->data = x;

        /* �ҵ�����λ�ú�̽ڵ㣬����¼ǰ��ָ��tmp */
        tmp = head;
        cur = head->next;
        while ( cur != NULL && x > cur->data )
        {
            tmp = cur;
            cur = cur->next;
        }
        p->next = cur;
        tmp->next = p;
    }
}


/*ɾ�������ͷ�ڵ�*/
void deleteBegin(PtrNode head)
{
    PtrNode cur = head->next;
    if( cur )
    {
        head->next = cur->next;
        free( cur );
    }
}


/*ɾ�������β�ڵ�*/
void deleteEnd(PtrNode head)
{
    PtrNode cur, tmp;
    tmp = head;
    cur = head->next;
    if( cur )
    {
        while( cur->next != NULL )
        {
            tmp = cur;
            cur = cur->next;
        }
        tmp->next = NULL;
        free( cur );
    }
}


/*ɾ��ֵΪx�ĵ�һ���ڵ㣬�ɹ��򷵻�1�����򷵻�0��*/
int deleteNode(PtrNode head, ElemType x)
{
    PtrNode cur, tmp;
    tmp = head;
    cur = head->next;

     /*���Ҵ�ɾ���ڵ㣬���ҵ�������curָ��ýڵ�*/
    while( cur != NULL && cur->data != x)
    {
        tmp = cur;
        cur = cur->next;
    }

    if( cur )   /*����ҵ�Ҫɾ���Ľڵ�*/
    {
        tmp->next = cur->next;
        free( cur );    /*�ͷŽڵ��ڴ�*/
        return 1;
    }
    else
        return 0;       //û���ҵ����������Ľڵ�

}


/*ɾ������ֵΪx�Ľڵ㣬�ɹ��򷵻ر�ɾԪ�ظ��������򷵻�0��*/
int deleteVal( PtrNode head, ElemType x )
{
    PtrNode cur, tmp;
    int count = 0;
    tmp = head;
    cur = head->next;   /*���սڵ�ĺ�̴���cur*/

    while( cur != NULL )    /*��������������ɾ�����xֵ�ڵ�*/
    {
        /*���Ҵ�ɾ���ڵ㣬���ҵ�������currentPtָ��ýڵ�*/
        while( cur != NULL && cur->data != x)
        {
            tmp = cur;
            cur = cur->next;
        }

        if( cur )   /*����ҵ�Ҫɾ���Ľڵ�*/
        {
            tmp->next = cur->next;
            free( cur );
            cur = tmp->next;
            count++;
        }
    }
    return count;
}


/*���ȥ�غ������ɹ��򷵻�ɾ�����������򷵻�0*/
int unique(PtrNode head)
{
    PtrNode cur;
    int count = 0;
    cur = head->next;

    while( cur )
    {
        count += deleteVal( cur, cur->data );
        cur = cur->next;
    }

    return count;
}


/*���������и���ֵ�ĳ��ִ���*/
int countVal( PtrNode head, ElemType x )
{
    PtrNode cur = head->next;
    int count = 0;
    while( cur )
    {
        while( cur != NULL && cur->data != x )
            cur = cur->next;
        
        if( cur )
        {
            cur = cur->next;
            count++;
        }
    }
    return count;
}


/*��������ָ���ʼ״̬*/
void clearList( PtrNode head )
{
    PtrNode cur, tmp;
    tmp = head;
    cur = head->next;

    while( cur )
    {
        tmp = cur;
        cur = cur->next;
        free( tmp );
    }

    head->next = NULL;
} 


/*�ͷ��������������սڵ㣬����ͷָ��Ϊ��*/
void destroyList(PtrNode *headPtr)
{
    PtrNode tmp, head = *headPtr;
    while( head )
    {
        tmp = head;
        head = head->next;
        free( tmp );
    }
    *headPtr = NULL;
}


/*����������Ч�ڵ���������*/
int getSize(PtrNode head)
{
    PtrNode cur = head->next;
    int count = 0;
    
    while( cur )
    {
        cur = cur->next;
        count++;
    }

    return count;
}


/*����ֵΪx�ĵ�һ���ڵ㣬���ؽڵ�ָ�룬ʧ�ܷ���NULL*/
PtrNode find(PtrNode head, ElemType x)
{
    PtrNode cur = head->next;

    while( cur !=NULL && cur->data != x )
        cur = cur->next;
    
    return cur;
}


/*���������е�n���ڵ㣬���ؽڵ�ָ�룬ʧ�ܷ���NULL*/
PtrNode findNth(PtrNode head, int n)
{
    if( n < 0 )
        return NULL;

    if( n == 0 )
        return head;

    PtrNode cur = head->next;
    for( int k = 1; cur != NULL && k < n; k++)
        cur = cur->next;
    return cur;
}


/*����ֵΪx�ĵ�һ���ڵ㣬���ؽڵ��ǰ��ָ�룬ʧ�ܷ���NULL*/
PtrNode findPre(PtrNode head, ElemType x)
{
	PtrNode tmp=head,cur = head->next;
   	while ( cur != NULL && cur->data != x ){
			tmp = cur;
        		cur = cur->next;
	}
     if (cur==NULL)	return (NULL); 
	else return (tmp);
}


/*ɾ��ָ��ָ��λ�õĺ�̽ڵ㣬�ɹ�����1��ʧ�ܷ���0*/
int eraseByPre(PtrNode pre)
{
	PtrNode cur;
	if (pre==NULL || pre->next==NULL)
		return 0;
   	else {
		cur = pre->next;
        	pre->next = cur->next;
		free(cur);
		return 1;
	}
}


/*������Ԫ��ֵ������������ʹ��ѡ�������㷨*/
void selectSortList(PtrNode head){ 
	PtrNode tmp, cur, min;
	ElemType val;
	tmp = head->next;/*�����սڵ�*/ 
	while (tmp)	{
		min = tmp;	cur = tmp->next;
		while( cur)	{
			if ( min->data > cur->data )	
				min = cur;
			cur = cur->next;
		}
		/*���������ڵ㣬ʹ�ý���������ķ���*/
		val = tmp->data;
		tmp->data = min->data;
		min->data = val;
		tmp = tmp->next;		
	}
}


void reverseList(PtrNode head) {
	PtrNode tmp,cur,next;  
	tmp=NULL; //ͷ�ڵ��β�ڵ�ʱҪ��NULL
	cur = head->next;
	while (cur) {
            // 1.Store next
            next = cur->next;
            // 2.Reverse current node's pointer
            cur->next = tmp;
            // 3.Move pointers one position ahead.
            tmp = cur;     cur = next;
  }
	head->next = tmp;//β�ڵ��Ϊͷ�ڵ�
}


void sortedMerge(PtrNode head1, PtrNode head2){
	PtrNode tmp1, cur1, cur2, next2;
	cur1 = head1->next;  cur2 = head2->next;	tmp1 = head1; 
	while ( cur1 && cur2){
      	if ( cur2->data < cur1->data){
			next2 = cur2->next;
			tmp1->next = cur2;	tmp1 = cur2;
			cur2->next = cur1;
			cur2  = next2;
		} else {
			tmp1 = cur1;	cur1 = cur1->next; 
		}
	}
	if ( cur2 ) 	tmp1->next = cur2;
	head2->next = NULL; /*��������2Ϊ������*/
}


/*����һ�����սڵ�ĳ�ʼѭ��������*/
PtrNode  initCirList(){
	PtrNode head = malloc(sizeof(struct Node));
	if ( head != NULL){
		head->next = head;
	} 
	return head;
}


void printCirList(PtrNode head)
{
	  PtrNode cur;
	   cur=head->next;
	   printf("The list is:\n");
	   while( cur != head ){
	        	printf( "%d-->",cur->data);
            	cur = cur->next;
      } 
		printf("Loop\n\n");   
}


void destroyCirList(PtrNode * headPtr)
{
	PtrNode tmp=*headPtr,head=tmp->next;
    while ( head != *headPtr ){
        tmp = head;
        head = head->next;
        free(tmp);
    } 
	  free(*headPtr);
    *headPtr = NULL;
} 
