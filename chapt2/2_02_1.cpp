/*
2-2-1 线性表的链式表示和实现
线性表的单链表存储结构-不带头节点
特点：
不带头节点的单链表在插入和删除第一个元素时要改变链表头指针的值
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

#define DestroyList ClearList
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
    L = NULL; //指针为空
    if (!L)
        return OK;
    else
        return ERROR;
}
//销毁一个线性表L
Status ClearList(LinkList &L)
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
//判断线性表L是否为空
Status ListEmpty(LinkList L)
{
    if (L)
        return FALSE;
    else
        return TRUE;
}
//返回L中元素的个数-表长
int ListLength(LinkList L)
{
    int i = 0;      //计数器初值为0
    LinkList p = L; // p指向第一个节点
    while (p)
    {
        i++;         //计数器加1
        p = p->next; // p指向下一个节点
    }
    return i;
}
//当第i个元素存在时，以e返回L中第i个元素的值
Status GetElem(LinkList L, int i, ElemType &e)
{
    int j = 1;      //计数器初值为1
    LinkList p = L; // p指向第一个节点
    if (i < 1)
        return ERROR;  // i的值不合法
    while (p && j < i) //未到表尾，也未找到第i个元素
    {
        p = p->next; // p指向下一个节点
        j++;         //计数器加1
    }
    if (j == i && p) //存在第i个元素
    {
        e = p->data; //取第i个元素的值赋给e
        return OK;   //成功，返回OK
    }
    return ERROR; //不存在第i个元素，失败返回ERROR
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
    int i = 0;      //计数器初值为0
    LinkList p = L; // p指向第一个结点
    while (p)       //未到表尾
    {
        i++;                     //计数器+1
        if (compare(p->data, e)) //找到这样的元素
            return i;            //返回位序
        p = p->next;             //没找到，p指向下一个结点
    }
    return 0; //找不到与e满足compare()的数据元素
}
//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，返回OK
//否则返回INFEASIBLE
Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e)
{
    LinkList q, p = L;
    if (!p)
        return ERROR; //链表为空
    while (p->next)   // p的后继存在
    {
        q = p->next;          // q指向p的后继
        if (q->data == cur_e) //若q的数据元素与输入的相同
        {
            pre_e = p->data; //用pre_e返回q的前驱
            return OK;       //成功返回OK
        }
        p = q; // p指向q（p后移）
    }
    return INFEASIBLE;
}
//若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继
Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e)
{
    LinkList p = L; // p指向第一个结点
    if (!p)
        return ERROR; //链表为空
    while (p->next)   // p指向的结点有后继
    {
        if (p->data == cur_e) // p的数据元素与输入的数据元素相同
        {
            next_e = p->next->data; //用next_e返回p的后继的数据元素
            return OK;              //成功返回OK
        }
        p = p->next; // p后移
    }
    return INFEASIBLE; //找不到后继
}
//在L中第i个位置之前插入元素e
Status ListInsert(LinkList &L, int i, ElemType e)
{
    int j = 1;         //计数器初值为1
    LinkList p = L, s; // p指向第一个结点，s用于存储新节点
    if (i < 1)
        return ERROR;                    // i值不合法
    s = (LinkList)malloc(sizeof(LNode)); //生成新节点，以下将它插入L中
    s->data = e;
    if (i == 1)
    {
        s->next = L; //新节点指向原第一个结点
        L = s;       // L指向新节点
    }
    else
    {
        while (p && j < i - 1) //寻找第i-1个结点
        {
            j++;         //计数器加1
            p = p->next; // p后移
        }
        if (!p) // i大于表长+1（p移到最后，为空了）
            return ERROR;
        s->next = p->next; // s的后继指向p的后继（第i个结点）
        p->next = s;       // p的后继指向s
    }
    return OK; //插入成功
}
Status ListDelete(LinkList &L, int i, ElemType &e)
{
    int j = 1;         //计数器初值为1
    LinkList q, p = L; // p指向第一个结点
    if (!L)            //表空
        return ERROR;  //删除失败
    else if (i == 1)   //删除第一个结点
    {
        L = p->next;
        e = p->data;
        free(p);
    }
    else
    {
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
    }
    return OK;
}
void visit(ElemType c)
{
    printf("%d ", c);
}
//依次对L的每个数据元素调用函数vi()一旦vi()失败，则操作失败
Status ListTraverse(LinkList L, void (*vi)(ElemType))
{
    LinkList p = L;
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
