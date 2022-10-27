/*
3-3-1 队列-链式-用单链表的操作实现
利用现有资源，减少编程工作量，可更清楚地看出队列和线性表的内在联系和共性
*/
#include<cstdlib>
#include<cstdio>

#define TRUE            1
#define FALSE           0
#define OK              1
#define ERROR           0
#define INFEASIBLE      -1
#define OVERFLOW        -2

#define LinkList        QueuePtr//单链表结点和链式队列结点一样
#define LNode           QNode//单链表结点和链式队列结点一样

typedef  int ElemType;
typedef  int Status;
typedef  ElemType QElemType;//单链表的元素类型为队列的元素类型
//线性表结构体
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,* LinkList;
//队列结构体
struct LinkQueue
{
    QueuePtr front,rear;//队头，队尾指针
};
//-------------以下为单链表函数-----------------------------------
//构造一个空的线性表
Status InitList(LinkList &L)
{
    //产生头节点，并使L指向此头节点
    L=(LinkList)malloc(sizeof(LNode));
    if(!L)//存储分配失败
        exit(OVERFLOW);
    L->next=NULL;//指针域为空，无后继
    return OK;
}
//销毁一个线性表L
Status DestroyList(LinkList &L)
{
    LinkList q;
    while(L)
    {
        q=L->next;
        free(L);
        L=q;
    }
    return OK;
}
//将表L置为空表
Status ClearList(LinkList &L)
{
    LinkList p,q;
    p=L->next;      //把头节点之后的数据看作一个无头结点的单链表，p指向其第一个节点
    L->next=NULL;   //空表头节点next域为NULL
    //把头节点之后的数据看作一个链表，将其销毁
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    return OK;
}
//判断线性表L是否为空
Status ListEmpty(LinkList L)
{
    if(L->next)
        return FALSE;
    else
        return TRUE;
}
//返回L中元素的个数-表长
int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}
//当第i个元素存在时，返回L中第i个元素的值
Status GetElem(LinkList L,int i,ElemType &e)
{
    int j=1;
    LinkList p=L->next;
    while(p && j<i)
    {
        p=p->next;
        j++;
    }
    if(!p || j>i)
        return ERROR;
    e=p->data;
    return OK;
}
Status comp(ElemType c1,ElemType c2)
{
    if(c1==c2)
        return TRUE;
    else
        return FALSE;
}
//返回L中第一个与e满足关系compare()的数据元素的位序
//若这样的元素不存在，则返回0
int LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    int i=0;
    LinkList p=L->next;
    while(p)
    {
        i++;
        if(compare(p->data,e))
            return i;
        p=p->next;
    }
    return 0;
}
//若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱，返回OK
//否则返回INFEASIBLE
Status PriorElem(LinkList L,ElemType cur_e,ElemType &pre_e)
{
    LinkList q,p=L->next;
    if(!p) return INFEASIBLE;//链表为空
    while(p->next)
    {
        q=p->next;
        if(q->data==cur_e)
        {
            pre_e=p->data;
            return OK;
        }
        p=q;
    }
    return INFEASIBLE;
}
//若cur_e是L的数据元素，且不是最后一个，则用next_e返回它的后继
Status NextElem(LinkList L,ElemType cur_e,ElemType &next_e)
{
    LinkList p=L->next;
    if(!p) return INFEASIBLE;//链表为空
    while(p->next)//p指向的结点有后继
    {
        if(p->data==cur_e)
        {
            next_e=p->next->data;
            return OK;
        }
        p=p->next;
    }
    return INFEASIBLE;
}
//在L中第i个位置之前插入元素e
Status ListInsert(LinkList L,int i,ElemType e)
{
    int j=0;
    LinkList p=L,s;
    //寻找第i-1个节点(上一个元素)
    while(p && j<i-1)
    {
        p=p->next;
        j++;
    }
    //i小于1或大于表长
    if(!p || j>i-1)
        return ERROR;
    //生成新节点
    s=(LinkList)malloc(sizeof(LNode));
    s->data=e;
    s->next=p->next;
    p->next=s;
    return OK;
}
Status ListDelete(LinkList L,int i,ElemType &e)
{
    int j=0;
    LinkList p=L,q;
    //寻找第i-1个结点
    while(p->next && j<i-1)
    {
        p=p->next;
        j++;
    }
    //为空/超表长
    if(!p->next || j>i-1)
        return ERROR;
    q=p->next;
    p->next=q->next;
    e=q->data;
    free(q);
    return OK;
}
void printQueue(ElemType c)
{
    printf("%d ",c);
}
//依次对L的每个数据元素调用函数vi()一旦vi()失败，则操作失败
Status ListTraverse(LinkList L,void(*vi)(ElemType))
{
    LinkList p=L->next;
    while(p)
    {
        vi(p->data);
        p=p->next;
    }
    printf("\n");
    return OK;
}
//-------------以下为队列函数-----------------------------------
//构造一个空队列Q
void InitQueue(LinkQueue &Q)
{
    InitList(Q.front);//以Q.front为头指针，构造空链表
    Q.rear=Q.front;//Q.rear与Q.front共同指向链队列的头结点
}
//销毁队列Q
void DestroyQueue(LinkQueue &Q)
{
    DestroyList(Q.front);
    Q.rear=Q.front;//都指向NULL
}
//将队列Q清为空队列
void ClearQueue(LinkQueue &Q)
{
    ClearList(Q.front);//清空Q.front为头指针的链表，头节点的指针域为空
    Q.rear=Q.front;//Q.rear指向空队列的头节点
}
//队列Q为空，返回TRUE，否则返回FALSE
Status QueueEmpty(LinkQueue Q)
{
    return ListEmpty(Q.front);//以Q.front为头指针的链表为空,则队列Q为空,反之亦然
}
//求队列Q的长度
int QueueLength(LinkQueue Q)
{
    return ListLength(Q.front);//以Q.front为头指针的链表长度即为队列长度
}
//若队列Q不空,用e返回Q的队头元素,并返回OK,否则返回ERROR
Status GetHead(LinkQueue &Q,QElemType &e)
{
    return GetElem(Q.front,1,e);//返回单链表第一个元素的值
}
//插入元素e为队列Q的新的队尾元素
void EnQueue(LinkQueue &Q,QElemType e)
{
    //没有利用尾指针,程序执行效率不高
    ListInsert(Q.front,ListLength(Q.front)+1,e);//在链表最后一个元素之后插入e
}
//若队列Q不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR
Status DeQueue(LinkQueue &Q,QElemType &e)
{
    if(Q.front->next==Q.rear)//队列仅有一个元素
        Q.rear=Q.front;//令队尾指针指向头节点
    return ListDelete(Q.front,1,e);
}
//从队头到队尾依次队队列Q中每个元素调用函数visit()
void QueueTraverse(LinkQueue Q,void(*visit)(QElemType))
{
    ListTraverse(Q.front,visit);
}
int main()
{
    int i;
    QElemType d;
    LinkQueue q;
    InitQueue(q);//构造空队列q，失败则程序结束（exit()）
    printf("成功构造了一个空队列后，q.front=%u,q.rear=%u\n",q.front,q.rear);
    printf("是否空队列？%d(1:空 0:否)\n",QueueEmpty(q));
    printf("队列的长度为%d\n",QueueLength(q));
    EnQueue(q,-5);
    EnQueue(q,5);
    EnQueue(q,10);
    printf("插入3个元素(-5,5,10)后，队列的长度为%d\n",QueueLength(q));
    printf("是否空队列？%d(1:空 0:否)\n",QueueEmpty(q));
    printf("队列的元素依次为");
    QueueTraverse(q,printQueue);//从队头到队尾，依次对队列q中每个元素调用函数printQueue
    i=GetHead(q,d);//将队头元素赋给d
    if(i==OK)
        printf("队头元素是%d，",d);
    DeQueue(q,d);//删除队头元素，将其值赋给d
    printf("删除了队头元素%d，",d);
    i=GetHead(q,d);//将队头元素赋给d
    if(i==OK)
        printf("新的队头元素是%d\n",d);
    ClearQueue(q);//清空队列q
    printf("清空队列后，q.front=%u,q.rear=%u,q.front->next=%u\n",q.front,q.rear,q.front->next);
    DestroyQueue(q);
    printf("销毁队列后，q.front=%u,q.rear=%u\n",q.front,q.rear);

    system("pause");
    return 0;
}