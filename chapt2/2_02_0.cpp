/*
2-2-0 线性表的链式表示和实现
线性表的单链表存储结构-带头节点
特点：
顺序表存储结构容易实现随机存取线性表第i个数据元素的操作
实现插入操作时要移动大量元素，适用于相对稳定的线性表
如职工工资表，学生学籍等
和顺序表相比，链表存储结构在实现插入、删除操作时，不需要移动大量数据元素。
但不容易实现随机存取线性表的第i的数据元素的操作。所以，链表适用于经常需要
进行插入和删除操作的线性表，如飞机航班的乘客等
*/
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

//线性表结构体
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

//另一种定义线性表结构体的方法
// struct LNode
// {
//     ElemType data; //存储空间基址
//     LNode *next;
// };
// typedef LNode *LinkList;//另一种定义LinkList的方法

//构造一个空的线性表
Status InitList(LinkList &L)
{
    //产生头节点，并使L指向此头节点
    L = (LinkList)malloc(sizeof(LNode));
    if (!L) //存储分配失败
        exit(OVERFLOW);
    L->next = NULL; //指针域为空，无后继
    return OK;
}
//销毁一个线性表L
Status DestroyList(LinkList &L)
{
    LinkList q;
    while (L)
    {
        q = L->next;
        free(L);
        L = q;
    }
    return OK;
}
//将表L置为空表
Status ClearList(LinkList &L)
{
    LinkList p, q;
    p = L->next;    //把头节点之后的数据看作一个无头结点的单链表，p指向其第一个节点
    L->next = NULL; //空表头节点next域为NULL
    //把头节点之后的数据看作一个链表，将其销毁
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    return OK;
}
//判断线性表L是否为空
Status ListEmpty(LinkList L)
{
    if (L->next)
        return FALSE;
    else
        return TRUE;
}
//返回L中元素的个数-表长
int ListLength(LinkList L)
{
    int i = 0;
    LinkList p = L->next;
    while (p)
    {
        i++;
        p = p->next;
    }
    return i;
}
//当第i个元素存在时，返回L中第i个元素的值
Status GetElem(LinkList L, int i, ElemType &e)
{
    int j = 1;
    LinkList p = L->next;
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    if (!p || j > i)
        return ERROR;
    e = p->data;
    return OK;
}
Status comp(ElemType c1, ElemType c2)
{
    if (c1 == c2)
        return TRUE;
    else
        return FALSE;
}
//返回L中第一个与e满足关系compare()的数据元素的位序
//若这样的元素不存在，则返回0
int LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
    int i = 0;
    LinkList p = L->next;
    while (p)
    {
        i++;
        if (compare(p->data, e))
            return i;
        p = p->next;
    }
    return 0;
}
//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，返回OK
//否则返回INFEASIBLE
Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e)
{
    LinkList q, p = L->next;
    if (!p)
        return INFEASIBLE; //链表为空
    while (p->next)
    {
        q = p->next;
        if (q->data == cur_e)
        {
            pre_e = p->data;
            return OK;
        }
        p = q;
    }
    return INFEASIBLE;
}
//若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继
Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e)
{
    LinkList p = L->next;
    if (!p)
        return INFEASIBLE; //链表为空
    while (p->next)        // p指向的结点有后继
    {
        if (p->data == cur_e)
        {
            next_e = p->next->data;
            return OK;
        }
        p = p->next;
    }
    return INFEASIBLE;
}
//在L中第i个位置之前插入元素e
Status ListInsert(LinkList L, int i, ElemType e)
{
    int j = 0;
    LinkList p = L, s;
    //寻找第i-1个节点
    while (p && j < i - 1)
    {
        p = p->next;
        j++;
    }
    // i小于1或大于表长
    if (!p || j > i - 1)
        return ERROR;
    //生成新节点
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}
Status ListDelete(LinkList L, int i, ElemType &e)
{
    int j = 0;
    LinkList p = L, q;
    //寻找第i-1个结点
    while (p->next && j < i - 1)
    {
        p = p->next;
        j++;
    }
    //为空/超表长
    if (!p->next || j > i - 1)
        return ERROR;
    q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}
void visit(ElemType c)
{
    printf("%d ", c);
}
//依次对L的每个数据元素调用函数vi()一旦vi()失败，则操作失败
Status ListTraverse(LinkList L, void (*vi)(ElemType))
{
    LinkList p = L->next;
    while (p)
    {
        vi(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}
int main()
{
    LinkList L;
    ElemType e, e0;
    Status i;
    int j, k;
    i = InitList(L);
    for (j = 1; j <= 5; j++)
        i = ListInsert(L, 1, j);
    printf("在L的表头依次插入1~5后: L=");
    ListTraverse(L, visit);
    i = ListEmpty(L);
    printf("L是否空: i=%d(1:是 0:否)\n", i);
    i = ClearList(L);
    printf("清空L后:L=");
    ListTraverse(L, visit);
    i = ListEmpty(L);
    printf("L是否空: i=%d(1:是 0:否)\n", i);
    for (j = 1; j <= 10; j++)
        ListInsert(L, j, j);
    printf("在L的表尾依次插入1~10后: L=");
    ListTraverse(L, visit);
    GetElem(L, 5, e);
    printf("第五个元素的值为: %d\n", e);
    for (j = 0; j <= 1; j++) //查找表中有无0,1
    {
        k = LocateElem(L, j, comp);
        if (k)
            printf("第%d个元素的值为%d\n", k, j);
        else
            printf("没有值为%d的元素\n", j);
    }
    // ClearList(L);
    for (j = 1; j <= 2; j++) //测试头两个数据的前驱
    {
        GetElem(L, j, e0);
        i = PriorElem(L, e0, e);
        if (i == INFEASIBLE)
            printf("元素%d无前驱\n", e0);
        else
            printf("元素%d的前驱为: %d\n", e0, e);
    }
    for (j = ListLength(L) - 1; j <= ListLength(L); j++) //测试最后两个数据的后继
    {
        GetElem(L, j, e0);      //把第j个数据赋给e0
        i = NextElem(L, e0, e); //求e0的后继
        if (i == INFEASIBLE)
            printf("元素%d无后继\n", e0);
        else
            printf("元素%d的后继为:%d\n", e0, e);
    }
    k = ListLength(L);
    for (j = k + 1; j >= k; j--)
    {
        i = ListDelete(L, j, e);
        if (i == ERROR)
            printf("删除第%d个数据失败\n", j);
        else
            printf("删除的元素为:%d\n", e);
    }
    printf("依次输出L的元素:");
    ListTraverse(L, visit);
    DestroyList(L);
    printf("销毁L后:L=%u\n", L);

    getchar(); //程序暂停
    return 0;
}
