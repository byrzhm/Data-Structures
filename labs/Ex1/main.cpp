/*
��n������ɭ�����ӵĶ�ԱҪը�����˵�һ������⣬˭������ȥ��
�ӳ�����ɭ�������ֻ������İ취�������ĸ�սʿȥִ������

�������£�
���ǰһ��սʿû���������Ҫ����һ��սʿ��ȥ��
�ָ�ÿ��սʿ��һ���ţ����Χ����һȦ��
����ĳһ�����Ϊ x ��սʿ��ʼ������
������ y ʱ����Ӧ��սʿ��ȥִ�������Ҵ�սʿ���ٲμ���һ�ּ�����
�����սʿû��������ٴ���һ��սʿ��ʼ�������������� y ʱ����սʿ����ȥִ������
�Դ����ƣ�ֱ���������Ϊֹ��

����ɭ�����ǲ�Ը��ȥ�ģ��������ɭΪ1�ţ�
�������һ����Ϊ����ɭ֧�У����n,x,y�����������ʱ,
����ɭ��������������ȥִ������
*/

#include "circular_list.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// ��ʼ����ѭ������
void InitList(List *pList, int n);

int main(int argc, char const *argv[])
{
    const int N_MAX = 10;   // n �����ֵ 
    const int Y_MAX = 10;   // y �����ֵ
    const int NUMDO = 100;  // ģ��Ĵ���
    
    srand(static_cast<unsigned int>(time(0)));  // �������������
    
    /*
    ��Ա���Ϊ 1 �� n,  n = rand() % N_MAX + 1
    �ӱ��Ϊ x �Ŀ�ʼ: 1 < x <= n,  x = rand() % n + 1
    ���� y ����ִ������: y >= 1,  y = rand() % Y_MAX + 1
    */ 
    int n, x, y;    
    // n = 5;
    // x = 2;
    // y = 2;
    
    int count = 0;  // ���Ϊ 1 ����(����ɭ)���µĴ���

    for (int cnt = 1 ; cnt <= NUMDO; cnt++)
    {   
        do {
            n = rand() % N_MAX + 1;
        } while (n == 1);
        
        //y = rand() % Y_MAX + 1;
        y = rand() % n + 1;
        x = rand() % n + 1;

        List list;  // ��ѭ������ģ������һȦ�Ķ�Ա 
        InitList(&list, n);
        Pair pair = GetPointer(list, x);    // pair ��¼ɾ���ڵ��ǰ��, ����ɾ������
        while (list.size != 1)
        {
            for (int i = 0; i < y - 1; i++)
            {
                pair.parent = pair.parent->next;
                pair.child = pair.child->next;
                if (pair.child == list.head)
                {// pair.child Ϊ list.head ʱ, ��Ҫ������ǰ�ƶ� pair
                    pair.parent = pair.parent->next;
                    pair.child = pair.child->next;
                }
            }
            // cout << "Remove: " << pair.child->data << endl;
            DeletePointer(&list, pair); // ɾ��pair.child��ָ�Ľڵ�
            
            // pair.child��ָ����free()��, ά��pair�Ľṹ�ı�child
            pair.child = pair.parent->next; 
            if (pair.child == list.head)
            {// pair.child Ϊ list.head ʱ, ��Ҫ������ǰ�ƶ� pair
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

// ��ʼ����ѭ������
void InitList(List* pList, int n)
{
    BuildList(pList);
    for (int i = 1; i <= n; i++)
    {
        InsertEnd(i, pList);
    }
}