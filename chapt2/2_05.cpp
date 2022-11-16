/*
2-5 双向链表-带头结点的双向循环链表
特点:
每个结点有两个指针，一个指向前驱，一个指向后继
优点：
可容易地找到结点的前驱和后继
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
#define LIST_INIT_SIZE 10 //线性表存储空间的初始分配量
#define LISTINCREMENT 2   //线性表存储空间的分配增量

#define MAX_SIZE 100 //链表的最大长度
#define N 6          //字符串的最大长度+1
//#define DestroyList     ClearList   //插入和清空操作一样

typedef int Status;
typedef int ElemType;
//线性表结构体
typedef struct DuLNode
{
    ElemType data;
    DuLNode *prior, *next;
} DuLNode, *DuLinkList;
//产生空的双向循环链表
void InitList(DuLinkList &L)
{
    //产生空的双向循环链表
    L = (DuLinkList)malloc(sizeof(DuLNode));
    if (L)
        L->next = L->prior = L;
    else
        exit(OVERFLOW);
}
//将表L置空
void ClearList(DuLinkList L) //不改变L
{
    DuLinkList p = L->next; // p指向第一个结点
    while (p != L)
    {
        p = p->next;    // p后移
        free(p->prior); //释放p的前驱
    }
    L->next = L->prior = L; //头结点的两个指针域均指向自身
}
//销毁双向链表
void DestroyList(DuLinkList &L)
{
    ClearList(L);
    free(L);
    L = NULL;
}
//判断表L是否为空
Status ListEmpty(DuLinkList L)
{
    if (L->next == L && L->prior == L)
        return TRUE;
    else
        return FALSE;
}
//返回L中的元素个数
int ListLength(DuLinkList L)
{
    DuLinkList p = L->next; // p为第一个结点
    int i = 0;
    while (p != L) // p没有遍历到头结点,就继续遍历
    {
        i++;
        p = p->next;
    }
    return i;
}
//当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR
Status GetElem(DuLinkList L, int i, ElemType &e)
{
    int j = 1;              //计数器初值
    DuLinkList p = L->next; // p指向第一个结点
    while (p != L && j < i) // p没遍历到头结点 且 p没到第i个结点
    {
        j++;
        p = p->next; // p后移
    }
    if (p == L || j > i) // p遍历到头结点了或者遍历到超过第i个结点了
        return ERROR;    //说明第i个元素不存在,返回ERROR
    e = p->data;         //将第i个元素的值赋给e
    return OK;
}
Status comp(ElemType c1, ElemType c2)
{
    if (c1 == c2)
        return TRUE;
    else
        return FALSE;
}
//返回L中第一个与e满足compare()的数据元素的位序
int LocateElem(DuLinkList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
    int i = 0;
    DuLinkList p = L->next; // p为第一个结点
    while (p != L)          // p不为头结点就继续遍历
    {
        i++;
        if (compare(p->data, e))
            return i;
        p = p->next;
    }
    return ERROR;
}
//若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱
Status PriorElem(DuLinkList L, ElemType cur_e, ElemType &pre_e)
{
    DuLinkList p = L->next->next; // p指向第2个结点,若结点数不足两个,由于链表的循环特性,p会指向头结点
    while (p != L)
    {
        if (p->data == cur_e)
        {
            pre_e = p->prior->data; //将p的前驱结点的值赋给pre_e
            return OK;              //成功返回OK
        }
        p = p->next; // p后移
    }
    return ERROR; //操作失败,返回ERROR
}
//若cur_e是L的数据元素,且不是最后一个,则用next_e返回它的后继
Status NextElem(DuLinkList L, ElemType cur_e, ElemType &next_e)
{
    DuLinkList p = L->next->next; // p指向第二个结点
    while (p != L)
    {
        if (p->prior->data == cur_e) // p的前驱值与cur_e相同
        {
            next_e = p->data; //将p结点的数据元素值赋给e
            return OK;
        }
        p = p->next; // p后移
    }
    return ERROR;
}
//在双向链表L中返回第i个元素的地址.i为0则返回头结点地址
//若第i个元素不存在,返回NULL
DuLinkList GetElemP(DuLinkList L, int i)
{
    int j;
    DuLinkList p = L;               // p指向头结点
    if (i < 0 || i > ListLength(L)) // i值不合法
        return NULL;
    for (j = 1; j <= i; j++) // p后移i次,指向第i个结点
        p = p->next;
    return p;
}
//在带头结点的双链循环线性表L中第i个位置之前插入元素e
Status ListInsert(DuLinkList L, int i, ElemType e)
{
    DuLinkList p, s;
    if (i < 1 || i > ListLength(L) + 1) // i值异常
        return ERROR;
    p = GetElemP(L, i - 1); // p为第i-1个结点
    if (!p)
        return ERROR;
    s = (DuLinkList)malloc(sizeof(DuLNode)); //为新结点分配空间
    if (!s)                                  //生成新结点失败
        return ERROR;
    s->data = e;        //将e的值赋给新结点的数据域
    s->prior = p;       //新结点的前驱为第i-1个
    s->next = p->next;  //新结点的后继为第i个结点
    p->next->prior = s; //原第i个节点(原第i-1个结点的后继)的前驱为新结点
    p->next = s;        //原第i-1个结点的后继为新结点
    return OK;
}
//删除表L的第i个元素
Status ListDelete(DuLinkList L, int i, ElemType &e)
{
    DuLinkList p;
    if (i < 1) // i值不合法
        return ERROR;
    p = GetElemP(L, i); //找到第i个结点的地址
    if (!p)
        return ERROR;
    e = p->data;               //第i个数据元素值赋给e
    p->prior->next = p->next;  //原第i-1个结点的后继为原第i+1个结点
    p->next->prior = p->prior; //原第i+1个结点的前驱为原第i-1个结点
    free(p);                   //释放原第i个结点
    return OK;                 //删除成功
}
void visit(ElemType c)
{
    printf("%d ", c);
}
//从头节点出发,正序对每个结点的数据元素调用visit()
void ListTraverse(DuLinkList L, void (*visit)(ElemType))
{
    DuLinkList p = L->next; // p为第一个结点
    while (p != L)          // p不为头节点
    {
        visit(p->data); //对p的数据元素调用visit()
        p = p->next;    // p后移
    }
    printf("\n");
}
//从头节点出发,倒序对每个结点的数据元素调用visit()
void ListTraverseBack(DuLinkList L, void (*visit)(ElemType))
{
    DuLinkList p = L->prior; // p为第一个结点
    while (p != L)           // p不为头节点
    {
        visit(p->data); //对p的数据元素调用visit()
        p = p->prior;   // p前移
    }
    printf("\n");
}

int main()
{
    DuLinkList L;
    ElemType e, e0;
    Status i;
    int j, k;
    InitList(L);
    for (j = 1; j <= 5; j++)
        i = ListInsert(L, 1, j);
    printf("在L的表头依次插入1~5后: L=");
    ListTraverse(L, visit);
    i = ListEmpty(L);
    printf("L是否空: i=%d(1:是 0:否)\n", i);
    ClearList(L);
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
        if (i == ERROR)
            printf("元素%d无前驱\n", e0);
        else
            printf("元素%d的前驱为: %d\n", e0, e);
    }
    for (j = ListLength(L) - 1; j <= ListLength(L); j++) //测试最后两个数据的后继
    {
        GetElem(L, j, e0);      //把第j个数据赋给e0
        i = NextElem(L, e0, e); //求e0的后继
        if (i == ERROR)
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
    printf("正序依次输出L的元素:");
    ListTraverse(L, visit);
    printf("倒序依次输出L的元素:");
    ListTraverseBack(L, visit);
    DestroyList(L);
    printf("销毁L后:L=%u\n", L);

    getchar(); //程序暂停
    return 0;
}
