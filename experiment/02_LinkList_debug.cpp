/*
**此程序用于Debug**
数据结构 实验2 - 链表
有头结点的单向链表，头指针L
*/
#include<iostream>
#include<cstdlib>
using namespace std;
#define TRUE            1
#define FALSE           0
#define OK              1
#define ERROR           0
//类型定义
typedef int ElemType;
typedef int Status;
//链表结构体
typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode,*LinkList;
//初始化链表L
Status InitList(LinkList &L)
{
    LinkList newbase = (LinkList)malloc(sizeof(LNode));
    if(!newbase)//分配空间失败,返回错误
        return ERROR;
    newbase->next=NULL;
    L=newbase;
    // L->data=1;
    return OK;
}
//在链表L中插入元素e,mod表示插入模式(0为尾插,1为头插,默认为0)
Status InsertList(LinkList &L,ElemType e,int mod=0)
{
    LinkList p=L;//p为第一个结点(若没有第一个结点则为NULL)
    if(mod==0)
    {
        while(p->next)//把p移动到最后一个结点
        {
            p=p->next;
        }
        LinkList newbase=(LinkList)malloc(sizeof(LNode));
        newbase->data=e;        //新结点data域
        newbase->next=p->next;  //新结点指向p的next域
        p->next=newbase;        //p的next域指向新结点
        return OK; 
    }
    else if(mod==1)
    {
        LinkList newbase=(LinkList)malloc(sizeof(LNode));
        newbase->data=e;        //新结点data域
        newbase->next=p->next;  //新结点指向p的next域
        p->next=newbase;        //p的next域指向新结点  
        return OK;      
    }
    return ERROR;
}
void visit(ElemType c)
{
    cout<<c<<" ";
}
//输出链表元素
void PrintList(LinkList &L,void(*vi)(ElemType))
{
    LinkList p=L;
    while(p->next)//把p移动到最后一个结点
    {
        p=p->next;
        vi(p->data);
    }
    cout<<endl;
}
void CreateList_La(LinkList &L)
{
    ElemType a[]={1,2,3,4,5,6,8};
    for(int i=0;i<sizeof(a)/sizeof(a[0]);i++)
    {
        InsertList(L,a[i],1);//头插(倒序)将元素插入L中
    }
}
void CreateList_Lb(LinkList &L)
{
    ElemType a[]={2,4,6,8,10};
    for(int i=0;i<sizeof(a)/sizeof(a[0]);i++)
    {
        InsertList(L,a[i],0);//头插(倒序)将元素插入L中
    }
}
void CreateList_Lc(LinkList La,LinkList Lb,LinkList &Lc)
{
    LinkList pc=Lc,pa=La,pb=Lb;
    while(pa->next)//若pa指向的结点不为空,则将它的数据插入Lc
    {
        pa=pa->next;//pa后移
        InsertList(Lc,pa->data);
    }
    while(pb->next)//若pb指向的结点不为空,则将它的数据插入Lc
    {
        pb=pb->next;//pb后移
        InsertList(Lc,pb->data);
    }
}

LinkList merge(LinkList L1,LinkList L2)
{
    LinkList newbase=(LinkList)malloc(sizeof(LNode));//newbase指向一个新建结点
    LinkList cur=newbase;//cur是个指针
    static int num1=1;int num2=1;
    cout<<"merge第"<<num1++<<"次"<<endl;
    while(L1!=NULL && L2!= NULL)
    {cout<<"while内第"<<num2++<<"次"<<endl;
    cout<<"L1->data="<<L1->data<<endl;
    cout<<"L2->data="<<L2->data<<endl;
        if(L1->data < L2->data)
        {
            cur->next=L1;
            
            if(L1)
                cout<<"合并L1："<<cur->next->data<<endl;

            L1=L1->next;
        }else{
            cur->next=L2;

            if(L2)
                cout<<"合并L2："<<cur->next->data<<endl;
            L2=L2->next;
        }
        cur=cur->next;
    }
    if(L1==NULL) cout<<"将L2中剩余元素插入\n\n";
    if(L2==NULL) cout<<"将L1中剩余元素插入\n\n";
    cur->next = L1==NULL?L2:L1;
    return newbase->next;
}
//用快慢指针将链表分成两个链表
LinkList SplitList(LinkList L)
{
    LinkList slow=L;
    LinkList fast=L->next;
    while(fast!=NULL && fast->next!=NULL)
    {
        slow=slow->next;
        fast=fast->next;
    }
    LinkList second=slow->next;
    slow->next=NULL;
    cout<<"被分割："<<second->data<<endl;
    return second;
}
//对链表h使用归并排序
LinkList SortList(LinkList L)
{
    //第一个节点为空或下一个结点为空
    if(L==NULL || L->next==NULL){
        return L;
    }
    LinkList L1=L;
    //第一次插入,把头节点去掉
    static int isfirst=1;
    if(isfirst)
    {
        L1=L1->next;
        isfirst=0;
    }
    //
    LinkList L2=SplitList(L1);
    L1=SortList(L1);
    L2=SortList(L2);
    return merge(L1,L2);
}
//将链表La和Lb有序（从大到小）合并进Lc
void MergeList_L(LinkList La,LinkList Lb,LinkList &Lc)
{
    // CreateList_Lc(La,Lb,Lc);//创建链表Lc
    InsertList(Lc,4);
    InsertList(Lc,1);
    InsertList(Lc,3);
    InsertList(Lc,2);
    cout<<"Lc=";
    PrintList(Lc,visit);
    Lc->next=SortList(Lc);//对链表Lc使用归并排序
    // LinkList pp=ll;
    // while(pp)
    // {
    //     cout<<pp->data<<" ";
    //     pp=pp->next;
    // }
    // cout<<endl;
    // LinkList Ld;
    // InitList(Ld);
    // Ld->next=ll;
    // cout<<"Ld=";
    // while(Ld)//把p移动到最后一个结点
    // {
    //     cout<<Ld->data<<" ";Ld=Ld->next;
    // }
    // cout<<endl;
}
//删除链表L中的重复元素，保留出现的第一个
void DeleteList(LinkList L)
{
    if(L->next==NULL) return;//除了头节点，没有结点
    LinkList p=L->next; //p指向第一个结点
    LinkList lq=p;      //lq是q的前驱
    LinkList q=lq->next;//q用来指示与p比较的结点
    while(p->next)//p->next不为空（p为最后一个结点时不进while）
    {
        while(lq && q)
        {
            if(q->data==p->data)
            {//若q中出现与p相同的元素则将q删除
                lq->next=q->next;
                free(q);
                q=lq->next;
            }
            else
            {//lq，q后移
                q=q->next;
                lq=lq->next;
            }
        }
        p=p->next;  //p后移
        lq=p;       //lq为q的前驱
        q=lq->next; //q为p的后继
    }    
}
//将链表L反序
void ReverseList(LinkList L)
{
    if(L->next==NULL) return;//L除了头节点，没有结点
    //新建一个链表newlist，存储逆序后的元素
    LinkList newlist;
    InitList(newlist);
    LinkList p=L->next;//p为L第一个结点
    while(p)
    {
        InsertList(newlist,p->data,1);//头插，相当于倒过来了
        p=p->next;
    }//此时新链表就是L倒序
    //将新链表对应位置元素值赋给L
    p=L->next;
    LinkList q=newlist->next;
    while(p&&q)
    {
        p->data=q->data;
        p=p->next;
        q=q->next;
    }
    //将新链表空间释放
    p=newlist;
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
}
void test()
{
    LinkList La,Lb,Lc;//结构体指针
    //初始化链表
    InitList(La);
    InitList(Lb);
    InitList(Lc);
    //向链表La和Lb中添加元素
    CreateList_La(La);
    CreateList_Lb(Lb);
    cout<<"1--创建链表La和Lb"<<endl;
    cout<<"La=";
    PrintList(La,visit);
    cout<<"Lb=";
    PrintList(Lb,visit);
    //将链表La和Lb有序（从大到小）合并进Lc
    cout<<"2--将链表La和Lb有序（从大到小）合并进Lc"<<endl;
    MergeList_L(La,Lb,Lc);
    cout<<"Lc=";
    PrintList(Lc,visit);
    //删除链表Lc中的重复元素
    cout<<"3--删除链表Lc中的重复元素"<<endl;
    DeleteList(Lc);
    cout<<"Lc=";
    PrintList(Lc,visit);
    //4--将链表Lc元素反序
    cout<<"4--将链表Lc元素反序"<<endl;
    ReverseList(Lc);
    cout<<"Lc=";
    PrintList(Lc,visit);
}
int main()
{
    test();//测试程序
    system("pause");//程序暂停
    return 0;
}