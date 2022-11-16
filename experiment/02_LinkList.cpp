/*
数据结构 实验2 - 链表
有头结点的单向链表，头指针L
*/
#include <iostream>
#include <cstdlib>
using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
//类型定义
typedef int ElemType;
typedef int Status;
//链表结构体
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;
//初始化链表L
Status InitList(LinkList &L)
{
    LinkList newbase = (LinkList)malloc(sizeof(LNode));
    if (!newbase) //分配空间失败,返回错误
        return ERROR;
    newbase->next = NULL;
    L = newbase;
    return OK;
}
//在链表L中插入元素e,mod表示插入模式(0为尾插,1为头插,默认为0)
Status InsertList(LinkList &L, ElemType e, int mod = 0)
{
    LinkList p = L; // p为第一个结点(若没有第一个结点则为NULL)
    if (mod == 0)
    {
        while (p->next) //把p移动到最后一个结点
        {
            p = p->next;
        }
        LinkList newbase = (LinkList)malloc(sizeof(LNode));
        newbase->data = e;       //新结点data域
        newbase->next = p->next; //新结点指向p的next域
        p->next = newbase;       // p的next域指向新结点
        return OK;
    }
    else if (mod == 1)
    {
        LinkList newbase = (LinkList)malloc(sizeof(LNode));
        newbase->data = e;       //新结点data域
        newbase->next = p->next; //新结点指向p的next域
        p->next = newbase;       // p的next域指向新结点
        return OK;
    }
    return ERROR;
}
void visit(ElemType c)
{
    cout << c << " ";
}
//输出链表元素
void PrintList(LinkList &L, void (*vi)(ElemType))
{
    LinkList p = L;
    while (p->next) //把p移动到最后一个结点
    {
        p = p->next;
        vi(p->data);
    }
    cout << endl;
}
//创建链表La
void CreateList_La(LinkList &L)
{
    ElemType a[] = {1, 2, 3, 4, 5, 6, 8};
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        InsertList(L, a[i], 1); //头插(倒序)将元素插入L中
    }
}
//创建链表Lb
void CreateList_Lb(LinkList &L)
{
    ElemType a[] = {2, 4, 6, 8, 10};
    for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
    {
        InsertList(L, a[i], 0); //尾插(正序)将元素插入L中
    }
}
//排序拼接函数
//输入:两个不带头节点的有序链表L1和L2
//输出:将L1和L2有序合并后的链表
LinkList merge(LinkList L1, LinkList L2)
{
    LinkList newbase = (LinkList)malloc(sizeof(LNode)); // newbase指向一个新建结点
    LinkList cur = newbase;                             // cur是个指针,表示等待插入元素的位置
    static int num1 = 1;
    int num2 = 1;
    while (L1 != NULL && L2 != NULL)
    {
        //将较小的数据插入新链表
        if (L1->data < L2->data)
        {
            cur->next = L1;
            L1 = L1->next;
        }
        else
        {
            cur->next = L2;
            L2 = L2->next;
        }
        cur = cur->next; //等待插入的位置后移
    }
    cur->next = L1 == NULL ? L2 : L1;
    return newbase->next;
}
//用快慢指针将链表分成两个链表
LinkList SplitList(LinkList L)
{
    LinkList slow = L;
    LinkList fast = L->next;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next;
    }
    LinkList second = slow->next;
    slow->next = NULL;
    return second;
}
//对链表L使用归并排序,将L转化为不带头节点的有序链表
//该函数的输入值和返回值都是不带头节点的链表
LinkList SortList(LinkList L)
{
    //需要排序的链表只有0或1个元素,解是已知的,排序结果就是它自己
    if (L == NULL || L->next == NULL)
    {
        return L;
        //返回链表指针,此时链表中只有一个元素
        //此时已经将n阶问题转化为1阶问题,再由1阶问题的解可递推出n阶问题的解
    }
    LinkList L1 = L;             //分割后的链表1
    LinkList L2 = SplitList(L1); //分割后的链表2
    L1 = SortList(L1);           //对分割后的链表1使用归并排序
    L2 = SortList(L2);           //对分割后的链表2使用归并排序
    return merge(L1, L2);
}
//将链表La和Lb有序（从大到小）合并进Lc
void MergeList_L(LinkList La, LinkList Lb, LinkList Lc)
{
    // La和Lb相当于已经被分割,将它们转化为有序链表再用merge有序合并
    Lc->next = merge(SortList(La->next), SortList(Lb->next));
}
//删除链表L中的重复元素，保留出现的第一个
void DeleteList(LinkList L)
{
    if (L->next == NULL)
        return;            //除了头节点，没有结点
    LinkList p = L->next;  // p指向第一个结点
    LinkList lq = p;       // lq是q的前驱
    LinkList q = lq->next; // q用来指示与p比较的结点
    while (p->next)        // p->next不为空（p为最后一个结点时不进while）
    {
        while (lq && q)
        {
            if (q->data == p->data)
            { //若q中出现与p相同的元素则将q删除
                lq->next = q->next;
                free(q);
                q = lq->next;
            }
            else
            { // lq，q后移
                q = q->next;
                lq = lq->next;
            }
        }
        p = p->next;  // p后移
        lq = p;       // lq为q的前驱
        q = lq->next; // q为p的后继
    }
}
//将链表L反序
void ReverseList(LinkList L)
{
    if (L->next == NULL)
        return; // L除了头节点，没有结点
    //新建一个链表newlist，存储逆序后的元素
    LinkList newlist;
    InitList(newlist);
    LinkList p = L->next; // p为L第一个结点
    while (p)
    {
        InsertList(newlist, p->data, 1); //头插，相当于倒过来了
        p = p->next;
    } //此时新链表就是L倒序
    //将新链表对应位置元素值赋给L
    p = L->next;
    LinkList q = newlist->next;
    while (p && q)
    {
        p->data = q->data;
        p = p->next;
        q = q->next;
    }
    //将新链表空间释放
    p = newlist;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}
void test()
{
    LinkList La, Lb, Lc; //结构体指针
    //初始化链表
    InitList(La);
    InitList(Lb);
    InitList(Lc);
    //向链表La和Lb中添加元素
    CreateList_La(La);
    CreateList_Lb(Lb);
    cout << "1--创建链表La和Lb" << endl;
    cout << "La=";
    PrintList(La, visit);
    cout << "Lb=";
    PrintList(Lb, visit);
    //将链表La和Lb有序（从小到大）合并进Lc
    cout << "2--将链表La和Lb有序（从小到大）合并进Lc" << endl;
    MergeList_L(La, Lb, Lc);
    cout << "Lc=";
    PrintList(Lc, visit);
    //删除链表Lc中的重复元素
    cout << "3--删除链表Lc中的重复元素" << endl;
    DeleteList(Lc);
    cout << "Lc=";
    PrintList(Lc, visit);
    // 4--将链表Lc元素反序
    cout << "4--将链表Lc元素反序" << endl;
    ReverseList(Lc);
    cout << "Lc=";
    PrintList(Lc, visit);
}
int main()
{
    test();          //测试程序
    system("pause"); //程序暂停
    return 0;
}