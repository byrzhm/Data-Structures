#include<stdio.h>
#include<stdlib.h>

#define ElemType int
struct Node{
	ElemType data;
	struct Node *next; 
};

typedef struct Node * PtrNode;

/*初始化一个带空节点的空链表*/
PtrNode initEmptyList ();
/*插入新节点到链表尾部*/
void insertEnd(PtrNode , ElemType );
/*查找链表的尾节点，并返回指向尾节点的尾指针*/
PtrNode getEnd(PtrNode);
/*插入新节点到链表头部*/
void insertBegin(PtrNode , ElemType );
/*插入新节点到升序链表适当位置*/
void insertUp(PtrNode , ElemType );
/*删除链表的头节点*/
void deleteBegin(PtrNode);
/*删除链表的尾节点*/
void deleteEnd(PtrNode);
/*判断链表是否为空，返回1，否则返回0*/
int isEmpty(PtrNode);
/*删除指定值的第一个节点，成功则返回1；否则返回0。*/
int deleteNode(PtrNode head,ElemType x);
/*删除指定值的所有节点，成功则返回删除个数；否则返回0*/
int deleteVal(PtrNode head,ElemType x);
/*遍历链表，打印每个节点数据*/
void printList(PtrNode);
/*清空链表，恢复初始状态*/
void clearList(PtrNode); 
/*释放整个链表，包括空节点，修正头指针为空*/
void destroyList(PtrNode *); 
/*计算链表有效节点数并返回*/
int getSize (PtrNode);
/*查找值为x的第一个节点，返回指针，失败返回NULL*/
PtrNode find(PtrNode, ElemType x);
/*查找链表中第n个节点，返回节点指针，失败返回NULL*/
PtrNode findNth(PtrNode head, int n);

/*设计去重函数，成功则返回删除个数，否则返回0*/
int unique(PtrNode head);
/*计算链表中给定值的出现次数*/
int countVal( PtrNode head, ElemType x );

/*查找值为x的第一个节点，返回节点的前驱指针，失败返回NULL*/
PtrNode findPre(PtrNode head, ElemType x); 
/*删除指定指针位置的后继节点，成功返回1，失败返回0*/
int eraseByPre(PtrNode pre);


/*对链表按元素值进行升序排序，使用选择排序算法*/
void selectSortList(PtrNode head);
/*将链表所有节点逆序*/
void reverseList(PtrNode head);
/*有序(升序)链表的归并函数*/
void sortedMerge(PtrNode head1, PtrNode head2);

/*创建一个带空节点的初始循环单链表*/
PtrNode  initCirList();
/*遍历循环单链表，打印节点*/
void printCirList(PtrNode head);
/*查找循环单链表的尾节点，并返回指向尾节点的尾指针*/
PtrNode getCirEnd(PtrNode head);
/*把一个新节点插入到循环链表尾部*/
void insertCirEnd(PtrNode head, ElemType x);
/*约瑟夫环形链表n/m求解，只剩一个节点*/
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


/*创建一个带空节点的初始链表*/
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


/*判断链表是否为空，返回1，否则返回0*/
int isEmpty(PtrNode head)
{
    return head->next == NULL;
}


/*遍历链表，打印每个节点数据*/
void printList(PtrNode head)
{
    if( head->next == NULL )
        printf("List is empty!");
    else
    {
        printf("The list is:\n");
        /*跳过空节点*/
        for( PtrNode cur = head->next; cur; cur = cur->next)
            printf("%d-->",cur->data);
        printf("NULL\n\n");
    }
}


/*查找链表的尾节点，并返回指向尾节点的尾指针*/
PtrNode getEnd(PtrNode head)
{
    PtrNode cur, tmp;
    tmp = head;
    cur = head->next;   /*跳过空节点*/
    while ( cur )
    {
        tmp = cur;
        cur = cur->next;
    }
    return tmp;
}


/*把一个新节点插入到链表尾部*/
void insertEnd (PtrNode head, ElemType x)
{
    PtrNode p, tmp;
    /*动态分配新节点，将新值存入*/
    p = ( PtrNode )malloc( sizeof( struct Node ) );

    if( !p )
        printf("Not inserted. No memory avaliable.\n");
    else
    {
        p->data = x;
        p->next = NULL;

        /*找到尾节点，记为前驱指针tmp*/
        tmp = getEnd( head );

        /*在尾节点后链接新节点*/
        tmp->next = p;
    }

}


/*把一个新节点插入到链表头部*/
void insertBegin(PtrNode head , ElemType x)
{
    PtrNode p, cur;
    /*动态分配新节点，将新值存入*/
    p = ( PtrNode )malloc( sizeof( struct Node ) );

    if( !p )
        printf("Not inserted. No memory avaliable.\n");
    else
    {
        p->data = x;
        /*直接在空节点后链接新节点*/
        cur = head->next;
        p->next = cur;
        head->next = p;
    }
}


/*把一个新节点插入到升序链表中*/
void insertUp(PtrNode head, ElemType x)
{
    PtrNode p, cur, tmp;
    /*动态分配新节点，将新值存入*/
    p = ( PtrNode )malloc( sizeof( struct Node ) );

    if( !p )
        printf("Not inserted. No memory avaliable.\n");
    else
    {
        p->data = x;

        /* 找到插入位置后继节点，并记录前驱指针tmp */
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


/*删除链表的头节点*/
void deleteBegin(PtrNode head)
{
    PtrNode cur = head->next;
    if( cur )
    {
        head->next = cur->next;
        free( cur );
    }
}


/*删除链表的尾节点*/
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


/*删除值为x的第一个节点，成功则返回1；否则返回0。*/
int deleteNode(PtrNode head, ElemType x)
{
    PtrNode cur, tmp;
    tmp = head;
    cur = head->next;

     /*查找待删除节点，若找到，则由cur指向该节点*/
    while( cur != NULL && cur->data != x)
    {
        tmp = cur;
        cur = cur->next;
    }

    if( cur )   /*如果找到要删除的节点*/
    {
        tmp->next = cur->next;
        free( cur );    /*释放节点内存*/
        return 1;
    }
    else
        return 0;       //没有找到符合条件的节点

}


/*删除所有值为x的节点，成功则返回被删元素个数；否则返回0。*/
int deleteVal( PtrNode head, ElemType x )
{
    PtrNode cur, tmp;
    int count = 0;
    tmp = head;
    cur = head->next;   /*将空节点的后继传给cur*/

    while( cur != NULL )    /*遍历整个链表来删除多个x值节点*/
    {
        /*查找待删除节点，若找到，则由currentPt指向该节点*/
        while( cur != NULL && cur->data != x)
        {
            tmp = cur;
            cur = cur->next;
        }

        if( cur )   /*如果找到要删除的节点*/
        {
            tmp->next = cur->next;
            free( cur );
            cur = tmp->next;
            count++;
        }
    }
    return count;
}


/*设计去重函数，成功则返回删除个数，否则返回0*/
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


/*计算链表中给定值的出现次数*/
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


/*清空链表，恢复初始状态*/
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


/*释放整个链表，包括空节点，修正头指针为空*/
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


/*计算链表有效节点数并返回*/
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


/*查找值为x的第一个节点，返回节点指针，失败返回NULL*/
PtrNode find(PtrNode head, ElemType x)
{
    PtrNode cur = head->next;

    while( cur !=NULL && cur->data != x )
        cur = cur->next;
    
    return cur;
}


/*查找链表中第n个节点，返回节点指针，失败返回NULL*/
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


/*查找值为x的第一个节点，返回节点的前驱指针，失败返回NULL*/
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


/*删除指定指针位置的后继节点，成功返回1，失败返回0*/
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


/*对链表按元素值进行升序排序，使用选择排序算法*/
void selectSortList(PtrNode head){ 
	PtrNode tmp, cur, min;
	ElemType val;
	tmp = head->next;/*跳过空节点*/ 
	while (tmp)	{
		min = tmp;	cur = tmp->next;
		while( cur)	{
			if ( min->data > cur->data )	
				min = cur;
			cur = cur->next;
		}
		/*交换两个节点，使用交换数据域的方法*/
		val = tmp->data;
		tmp->data = min->data;
		min->data = val;
		tmp = tmp->next;		
	}
}


void reverseList(PtrNode head) {
	PtrNode tmp,cur,next;  
	tmp=NULL; //头节点变尾节点时要用NULL
	cur = head->next;
	while (cur) {
            // 1.Store next
            next = cur->next;
            // 2.Reverse current node's pointer
            cur->next = tmp;
            // 3.Move pointers one position ahead.
            tmp = cur;     cur = next;
  }
	head->next = tmp;//尾节点变为头节点
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
	head2->next = NULL; /*修正链表2为空链表*/
}


/*创建一个带空节点的初始循环单链表*/
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
