/*
2-3-1 静态链表
用顺序存储结构实现链式存储的功能
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
#define DestroyList     ClearList   //插入和清空操作一样

typedef int Status;
typedef int ElemType;
//线性表结构体
typedef struct 
{
    ElemType data;  //数据域
    int cur;        //指针域
}component,SLinkList[MAX_SIZE];

int Malloc(SLinkList space)
{
    int i=space[0].cur;             //备用链表第1个结点的位置
    if(i)                           //备用链表非空
        space[0].cur=space[i].cur;  //备用链表的头节点指向备用链表的第二个结点
    //cout<<i;
    return i;                       //返回新开辟结点的坐标
}
//将下标为k的空闲结点回收到备用链表中（成为第一个结点
void Free(SLinkList space,int k)
{
    //注意操作的次序，不能换
    space[k].cur=space[0].cur;  //被回收结点的后继为第一个结点
    space[0].cur=k;             //备用链表的头头节点指向新结点
}
//构造一个空的链表L,表头为L的最后一个单元L[MAX_SIZE-1], 
//其余单元链组成一个备用链表,表头为L的第一个单元
void InitList(SLinkList L)
{
    int i;//for循环要用
    L[MAX_SIZE-1].cur=0;        //最后一个结点为头节点,无后继(cur=0)
    for(i=0;i<MAX_SIZE-2;i++)   //
        L[i].cur=i+1;//0~MAX_SIZE-3(倒数第三个结点)为备用结点,都指向它们后面的结点
    L[MAX_SIZE-2].cur=0;        //倒数第二个结点为备用链表的末尾,无后继(cur=0)
}
//将线性表L置为空表
void ClearList(SLinkList L)
{
    int j,k,i=L[MAX_SIZE-1].cur;    //i为链表第一个结点
    L[MAX_SIZE-1].cur=0;            //链表置空
    k=L[0].cur;                     //k为备用链表第一个结点
    L[0].cur=i;                     //把链表的结点连接到备用链表的表头
    //找到链表(此时已变为备用链表的后继)的最后一个结点,用j储存
    while(i)                        
    {
        j=i;                        //若i不为0,将i的值赋给i
        i=L[i].cur;                 //i为链表下标(指针),i后移
    }
    L[j].cur=k;                     //在链表(此时已变为备用链表的后继)尾部 接上 备用链表第一个结点

}
//判断表L是否为空
Status ListEmpty(SLinkList L)
{
    if(L[MAX_SIZE-1].cur==0)
        return TRUE;
    else
        return FALSE;
}
//返回表长
int ListLength(SLinkList L)
{
    int j=0,i=L[MAX_SIZE-1].cur;
    while(i)
    {
        i=L[i].cur;
        j++;
    }
    return j;
}
//用e返回L中第i个元素的值
Status GetElem(SLinkList L,int i,ElemType &e)
{
    int m,k=MAX_SIZE-1;         //k为头节点
    if(i<1 || i>ListLength(L))  //i值异常
        return ERROR;
    for(m=1;m<=i;m++)           //k为第i个结点的下标
        k=L[k].cur;
    e=L[k].data;
    cout<<"e="<<e;
    return OK;
}
//在静态链表L中查找第一个值为e的元素,返回它的位序(在数组中的，而不是在链表中的)，否则返回0
int LocateElem(SLinkList L,ElemType e)
{
    int i=L[MAX_SIZE-1].cur;
    while(i && L[i].data!=e)
        i=L[i].cur;
    return i;
}
//若cur_e是L的数据元素,且不是第一个,则用pre_e返回它的前驱
//否则操作失败,pre_e无定义
Status PriorElem(SLinkList L,ElemType cur_e,ElemType &pre_e)
{
    // //自己写的
    // int i=L[MAX_SIZE-1].cur,j=L[i].cur;
    // while(i)
    // {
    //     if(L[j].data==cur_e)
    //         pre_e=L[i].data;
    //         return OK;
    //     i=L[i].cur;
    //     j=L[i].cur;
    //     //此时j是i的后继
    // }
    // return ERROR;
    int j,i=L[MAX_SIZE-1].cur;//i是第一个结点下标
    do
    {
        j=i;
        i=L[i].cur;
        //此时j是i的前驱
    }while(i && cur_e!=L[i].data);
    if(i)                   //i不为0(i不为最后一个结点),说明找到前驱了
    {
        pre_e=L[j].data;    //返回下标j的数据元素
        return OK;          //成功返回OK
    }
    return ERROR;           //未找到前驱,返回ERROR
}
//若cue_e是L中的数据元素,且不是最后一个,则用next_e返回它(第一个)的后继
//否则操作失败
Status NextElem(SLinkList L,ElemType cur_e,ElemType &next_e)
{
    int j,i=LocateElem(L,cur_e);//i为表中第一个值为cur_e的下标
    if(i)//L中存在cur_e
    {   
        j=L[i].cur;             //j为i的后继下标
        if(j)                   //j不为空
        {
            next_e=L[j].data;   //返回j的数据元素
            return OK;          //成功返回OK
        }
    }
    return ERROR;               //失败返回错误
}
//在L中第i个元素之前插入新的数据元素e
Status ListInsert(SLinkList L,int i,ElemType e)
{
    int m,j,k=MAX_SIZE-1;
    if(i<1 || i>ListLength(L)+1)//i值不合法
        return ERROR;
    j=Malloc(L);    //为新结点分配空间,返回下标
    if(j)
    {
        L[j].data=e;            //新结点数据域赋值
        for(m=1;m<i;m++)        //k指向第i-1个结点
            k=L[k].cur;
        L[j].cur=L[k].cur;      //新结点的后继为第i个结点
        L[k].cur=j;             //第i-1个结点的后继为新结点
        return OK;
    }
    return ERROR;
}
//删除在L中的第i个数据元素
Status ListDelete(SLinkList L,int i,ElemType &e)
{
    int j,k=MAX_SIZE-1;         //k为头结点下标
    if(i<1 || i>ListLength(L))  //i非法
        return ERROR;
    for(j=1;j<i;j++)            //k为第i-1个结点的下标
        k=L[k].cur;
    j=L[k].cur;         //j为第i个结点的下标
    L[k].cur=L[j].cur;  //第i-1个结点的后继为第i+1个结点
    Free(L,j);          //释放第i个结点(放入备用链表)
    return OK;
}
void visit(ElemType c)
{
    printf("%d ",c);
}
//依次对L的每个数据元素调用visit()
void ListTraverse(SLinkList L,void(*visit)(ElemType))
{
    int i=L[MAX_SIZE-1].cur;    //i为第一个结点的下标
    while(i)                    //未到静态链表表尾
    {
        visit(L[i].data);       //对元素执行visit()
        i=L[i].cur;             //i后移
    }
    printf("\n");
}
int main()
{
    SLinkList L;
    ElemType e,e0;
    Status i;
    int j,k;
    InitList(L);
    for(j=1;j<=5;j++)
        {i=ListInsert(L,1,j);/*cout<<i<<"-";*/}
    printf("在L的表头依次插入1~5后: L=");
    ListTraverse(L,visit);
    printf("表L的长度=%d\n",ListLength(L));
    i=ListEmpty(L);
    printf("L是否空: i=%d(1:是 0:否)\n",i);
    ClearList(L);
    printf("清空L后:L=");
    ListTraverse(L,visit);
    printf("表L的长度=%d\n",ListLength(L));
    i=ListEmpty(L);
    printf("L是否空: i=%d(1:是 0:否)\n",i);
    for(j=1;j<=10;j++)
        ListInsert(L,j,j);
    printf("在L的表尾依次插入1~10后: L=");
    ListTraverse(L,visit);
    GetElem(L,5,e);
    printf("第5个元素的值为: %d\n",e);
    for(j=0;j<=1;j++)//查找表中有无0,1
    {
        k=LocateElem(L,j);
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
    for(j=k+1;j>=k;j--)//删除最后两个数据
    {
        i=ListDelete(L,j,e);
        if(i==ERROR)
            printf("删除第%d个数据失败(不存在此元素)\n",j);
        else
            printf("删除的元素为:%d\n",e);
    }
    printf("依次输出L的元素:");
    ListTraverse(L,visit);

    getchar();//程序暂停
    return 0;
}
