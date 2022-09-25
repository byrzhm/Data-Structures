/*
有n个加里森敢死队的队员要炸掉敌人的一个军火库，谁都不想去，
队长加里森决定用轮回数数的办法来决定哪个战士去执行任务。

规则如下：
如果前一个战士没完成任务，则要再派一个战士上去。
现给每个战士编一个号，大家围坐成一圈，
随便从某一个编号为 x 的战士开始计数，
当数到 y 时，对应的战士就去执行任务，且此战士不再参加下一轮计数。
如果此战士没完成任务，再从下一个战士开始数数，被数到第 y 时，此战士接着去执行任务。
以此类推，直到任务完成为止。

加里森本人是不愿意去的，假设加里森为1号，
请你设计一程序为加里森支招，求出n,x,y满足何种条件时,
加里森能留到最后而不用去执行任务。
*/

#include "circular_list.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// 初始化单循环链表
void InitList(List *pList, int n);

int main(int argc, char const *argv[])
{
    const int N_MAX = 10;   // n 的最大值 
    const int Y_MAX = 10;   // y 的最大值
    const int NUMDO = 100;  // 模拟的次数
    
    srand(static_cast<unsigned int>(time(0)));  // 设置随机数种子
    
    /*
    队员编号为 1 到 n,  n = rand() % N_MAX + 1
    从编号为 x 的开始: 1 < x <= n,  x = rand() % n + 1
    数到 y 的人执行任务: y >= 1,  y = rand() % Y_MAX + 1
    */ 
    int n, x, y;    
    // n = 5;
    // x = 2;
    // y = 2;
    
    int count = 0;  // 编号为 1 的人(加里森)留下的次数

    for (int cnt = 1 ; cnt <= NUMDO; cnt++)
    {   
        do {
            n = rand() % N_MAX + 1;
        } while (n == 1);
        
        //y = rand() % Y_MAX + 1;
        y = rand() % n + 1;
        x = rand() % n + 1;

        List list;  // 单循环链表模拟坐成一圈的队员 
        InitList(&list, n);
        Pair pair = GetPointer(list, x);    // pair 记录删除节点的前驱, 便于删除操作
        while (list.size != 1)
        {
            for (int i = 0; i < y - 1; i++)
            {
                pair.parent = pair.parent->next;
                pair.child = pair.child->next;
                if (pair.child == list.head)
                {// pair.child 为 list.head 时, 需要整体向前移动 pair
                    pair.parent = pair.parent->next;
                    pair.child = pair.child->next;
                }
            }
            // cout << "Remove: " << pair.child->data << endl;
            DeletePointer(&list, pair); // 删除pair.child所指的节点
            
            // pair.child所指对象被free()了, 维持pair的结构改变child
            pair.child = pair.parent->next; 
            if (pair.child == list.head)
            {// pair.child 为 list.head 时, 需要整体向前移动 pair
                pair.parent = pair.parent->next;
                pair.child = pair.child->next;
            }
        }
        // cout << "Remained: " << list.head->next->data << endl;
        if (list.head->next->data == 1)
        {
            count++;
            printf("%-2d: n = %-2d    x = %-2d    y = %-2d\n", count, n, x, y);
        }
        DestroyList(&list);
    }

    cout << "Observed probability is " << 100.0 * count / NUMDO << "%.\n";

    return 0;
}

// 初始化单循环链表
void InitList(List* pList, int n)
{
    BuildList(pList);
    for (int i = 1; i <= n; i++)
    {
        InsertEnd(i, pList);
    }
}