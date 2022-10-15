/*
2-4 循环链表-有头节点
特点:
最后一个结点的next域指向头节点，而不是“空”
优点：
由表尾很容易能找到表头。
但是若表较长，则由表头找到表尾较费时，因此单循环链表往往设立尾指针而不是头指针
（尾指针指向表尾，尾指针的后继是表头）
这在两个链表首尾相连合并成一个链表时非常方便
（尾指针的next指向新链表的头节点，新链表的尾指针next指向老链表的头结点，free（新链表的尾指针））
*/
#include<cstdlib>
#include<cstdio>
#include<iostream>
using namespace std;
#define TRUE            1
#define FALSE           0
#define OK              1
#define ERROR           0
#define INFEASIBLE      -1
#define OVERFLOW        -2
#define LIST_INIT_SIZE  10          //线性表存储空间的初始分配量
#define LISTINCREMENT   2           //线性表存储空间的分配增量

#define MAX_SIZE        100         //链表的最大长度
#define N               6           //字符串的最大长度+1
//#define DestroyList     ClearList   //插入和清空操作一样

typedef int Status;
typedef int ElemType;
//线性表结构体
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;
//构造一个空链表
void InitList(LinkList &L)
{
    L=(LinkList)malloc(sizeof(LNode));//为头节点分配空间，L指向头节点
    if(!L)
        exit(OVERFLOW);
    L->next=L;  //头节点指针域指向它自己
}
//若表L存在，将L置为空表
void ClearList(LinkList &L)
{
    LinkList p,q;
    //注意L开始时是尾指针
    L=L->next;//L指向头结点
    p=L->next;//p指向第一个节点
    while(p!=L)//p没有到头节点
    {
        q=p->next;  //q为p的后继
        free(p);    //释放p的空间
        p=q;        //p后移
    }
    //此时只剩一个头节点，L和p都指向头节点
    L->next=L;//头节点指针域指向它自己
}
//销毁线性表L
void DestroyList(LinkList &L)
{
    ClearList(L);
    free(L);
    L=NULL;
}
//判断表L是否为空
Status ListEmpty(LinkList L)
{
    if(L->next==L)//若尾指针的next域是尾指针（尾指针指向头节点）
        return TRUE;
    else 
        return FALSE;
}
//返回L中的元素个数
int ListLength(LinkList L)
{
    // int j=0;
    // LinkList p;
    // L=L->next;      //L为头节点
    // p=L->next;      //p为第一个结点
    // while(p!=L)
    // {
    //     p=p->next;
    //     j++;
    // }
    // return j;
    int i=0;//计数器初值为0
    LinkList p=L->next;//p指向头结点
    while(p!=L)//未到表尾
    {
        i++;//计数器+1
        p=p->next;//p后移(指向下一个结点)
    }
    return i;
}
//当第i个元素存在时,用e返回其值,否则返回ERROR
Status GetElem(LinkList L,int i,ElemType &e)
{
    int j=1;//计数器初值
    LinkList p=L->next->next;//p指向头节点
    if(i<=0 && i>ListLength(L))//i值非法
        return ERROR;
    while(j<i)//p向后移动i-1次,最后指向第i个元素
    {
        p=p->next;
        j++;
    }
    e=p->data;//用e返回第i个元素值
    return OK;
}
Status comp(ElemType c1,ElemType c2)
{
    if(c1==c2)
        return TRUE;
    else
        return FALSE;
}
//返回L中第一个与e满足compare()的元素
int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    int i=0;//计数器初值
    LinkList p=L->next->next;//p指向第一个结点
    while(p!=L->next)//p不为头节点时
    {
        i++;
        if(compare(p->data,e))
            return i;//找到对应元素,返回其位序
        p=p->next;
    }
    return ERROR;
}
//若cur_e是L的数据元素且不是第一个,则用pre_e返回它的前驱,返回OK
//否则操作失败,pre_e无定义,返回ERROR
Status PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e)
{
    LinkList q,p=L->next->next;//p为第一个节点
    q=p->next;//q为p(第一个节点)的后继
    while(q!=L->next)//当p未到表尾(q未到头节点)
    {
        if(q->data==cur_e)//q(p的后继)数据元素为cur_e
        {
            pre_e=p->data;//用pre_e返回p的数据元素
            return OK;//操作成功,返回OK
        }
        p=q;//p后移
        q=q->next;//q后移
    }
    return ERROR;//操作失败,返回ERROR
}
//若cur_e是L中的数据元素且不是最后一个,则用next_e返回它的后继,返回OK
//否则操作失败,next_e无定义,返回ERROR
Status NextElem(LinkList L,ElemType cur_e,ElemType &next_e)
{
    LinkList p=L->next->next;//p指向第一个结点
    while(p!=L)//当p不指向最后一个结点时
    {
        if(p->data==cur_e)//p指向的结点的数据域为
        {
            next_e=p->next->data;//将p的后继结点的数据元素赋给next_e
            return OK;
        }
        p=p->next;//p后移
    }
    return ERROR;
}
//在L的第i个元素之前插入元素e(改变L)
Status ListInsert(LinkList &L,int i,ElemType e)
{
    LinkList s,p=L->next;//p指向头节点
    int j=0;
    if(i<=0 || i>ListLength(L)+1)
        return ERROR;
    while(j<i-1)//p后移i-1次,最终指向第i-1个结点
    {
        j++;
        p=p->next;
    }
    s=(LinkList)malloc(sizeof(LNode));//为新节点分配空间
    s->data=e;//新结点的数据域
    s->next=p->next;//新节点next域指向第i个结点
    p->next=s;//第i-1个结点的next域指向新结点
    if(p==L)//如果插在表尾
        L=s;
    return OK;
}
//删除表的第i个元素,用e返回其值
Status ListDelete(LinkList &L,int i,ElemType &e)
{
    LinkList q,p=L->next;//p指向头结点
    int j=0;
    if(i<=0 || i>ListLength(L))
        return ERROR;
    while(j<i-1)//p后移到第i-1个结点
    {
        j++;
        p=p->next;
    }
    q=p->next;//q指向待删除的结点(第i个)
    p->next=q->next;//待删结点的前驱指向待删结点的后继
    e=q->data;//用e返回删除的数据元素值
    if(L==q)//删除的是最后一个结点,尾指针要变
        L=p;
    free(q);
    return OK;
}
void visit(ElemType c)
{
    printf("%d ",c);
}
//依次对L的每个数据元素调用函数vi()
void ListTraverse(LinkList L,void(*vi)(ElemType))
{
    LinkList p=L->next->next;//p为第一个结点
    while(p!=L->next)//若p不为头结点
    {
        vi(p->data);//对p的数据元素执行操作
        p=p->next;//p后移
    }
    printf("\n");
}
int main()
{
    LinkList L;
    ElemType e,e0;
    Status i;
    int j,k;
    InitList(L);
    for(j=1;j<=5;j++)
        i=ListInsert(L,1,j);
    printf("在L的表头依次插入1~5后: L=");
    ListTraverse(L,visit);
    i=ListEmpty(L);
    printf("L是否空: i=%d(1:是 0:否)\n",i);
    ClearList(L);
    printf("清空L后:L=");
    ListTraverse(L,visit);
    i=ListEmpty(L);
    printf("L是否空: i=%d(1:是 0:否)\n",i);
    for(j=1;j<=10;j++)
        ListInsert(L,j,j);
    printf("在L的表尾依次插入1~10后: L=");
    ListTraverse(L,visit);
    GetElem(L,5,e);
    printf("第五个元素的值为: %d\n",e);
    for(j=0;j<=1;j++)//查找表中有无0,1
    {
        k=LocateElem(L,j,comp);
        if(k)
            printf("第%d个元素的值为%d\n",k,j);
        else
            printf("没有值为%d的元素\n",j);
    }
    
    for(j=1;j<=2;j++)//测试头两个数据的前驱
    {
        GetElem(L,j,e0);
        i=PriorElem(L,e0,e);
        if(i==ERROR)
            printf("元素%d无前驱\n",e0);
        else
            printf("元素%d的前驱为: %d\n",e0,e);
    }
    for(j=ListLength(L)-1;j<=ListLength(L);j++)//测试最后两个数据的后继
    {
        GetElem(L,j,e0);    //把第j个数据赋给e0
        i=NextElem(L,e0,e); //求e0的后继
        if(i==ERROR)
            printf("元素%d无后继\n",e0);
        else
            printf("元素%d的后继为:%d\n",e0,e);
    }
    k=ListLength(L);
    for(j=k+1;j>=k;j--)
    {
        i=ListDelete(L,j,e);
        if(i==ERROR)
            printf("删除第%d个数据失败\n",j);
        else
            printf("删除的元素为:%d\n",e);
    }
    printf("依次输出L的元素:");
    ListTraverse(L,visit);
    DestroyList(L);
    printf("销毁L后:L=%u\n",L);

    getchar();//程序暂停
    return 0;
}
