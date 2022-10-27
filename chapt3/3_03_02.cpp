/*
3-3-2 循环队列-队列的顺序表示和实现
循环：取模%
为了区分栈空和栈满，少用一个存储空间
栈空：Q.front == Q.rear
栈满：Q.front == (Q.rear+1)%MAX_QSIZE
输入:
1 2 3 -1
4
5
6
7
8

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
#define MAX_QSIZE       5          //最大队列长度+1,有一个不用

typedef int ElemType;
typedef ElemType QElemType;
typedef int Status;
//循环队列结构体
struct SqQueue
{
    QElemType *base;//初始化动态内存分配空间
    int front;//头指针,若队列不动,指向队列头元素
    int rear;//尾指针,若队列不空,指向队列尾元素的下一个位置
};
//构造一个空队列
void InitQueue(SqQueue &Q)
{
    Q.base=(QElemType*)malloc(MAX_QSIZE*sizeof(SqQueue));
    if(!Q.base)//存储分配失败
        exit(OVERFLOW);
    Q.front=Q.rear=0;//队列为空
}
//销毁队列Q,Q不再存在
void DestroyQueue(SqQueue &Q)
{
    if(Q.base)//队列Q存在
        free(Q.base);//释放Q.base所指的存储空间
    Q.base=NULL;//Q.base不指向任何存储单元
    Q.front=Q.rear=0;
}
//将队列Q清为空队列
void ClearQueue(SqQueue Q)
{
    Q.front=Q.rear=0;
}
//若队列Q为空队列,则返回TRUE,否则返回FALSE
Status QueueEmpty(SqQueue Q)
{
    if(Q.front==Q.rear)//队列空的标志
        return TRUE;
    else
        return FALSE;
}
//若队列Q不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR
Status GetHead(SqQueue Q,QElemType &e)
{
    if(Q.front==Q.rear)//队列为空
        return ERROR;
    e=Q.base[Q.front];
    return OK;
}
//插入元素e为队列Q的新的队尾元素
Status EnQueue(SqQueue &Q,QElemType e)
{
    if((Q.rear+1)%MAX_QSIZE==Q.front)//队列满
        return ERROR;
    Q.base[Q.rear]=e;//将e插在队尾
    Q.rear=(Q.rear+1)%MAX_QSIZE;//队列指针+1后对MAX_QSIZE取余
    return OK;
}
//返回队列Q的元素个数,即队列的长度
int QueueLength(SqQueue Q)
{
    return (Q.rear-Q.front+MAX_QSIZE)%MAX_QSIZE;
}
//若队列Q不空,则删除Q的队头元素,用e返回其值,
//并返回OK,否则返回ERROR
Status DeQueue(SqQueue &Q,QElemType &e)
{
    if(Q.front==Q.rear)//栈空
        return ERROR;
    e=Q.base[Q.front];//将队头元素的值赋给e
    Q.front=(Q.front+1)%MAX_QSIZE;//移动队头指针
    return OK;
}
void printQueue(QElemType c)
{
    printf("%d ",c);
}
//从队头到队尾依次对队列Q中每个元素调用函数visit()
void QueueTraverse(SqQueue &Q,void(*visit)(QElemType))
{
    int i=Q.front;//i最初指向队头元素
    while(i!=Q.rear)//i指向队列Q中的元素
    {
        visit(Q.base[i]);//对i所指元素调用函数visit()
        i=(i+1)%MAX_QSIZE;//i指向下一个元素
    }
    printf("\n");
}
//测试程序
void test()
{
    Status j;
    int i=0,m;
    QElemType d;//存储返回元素值
    SqQueue Q;
    InitQueue(Q);//初始化队列Q,失败则退出
    printf("初始化队列后,队列空否?%u(1:空 0:否)\n",QueueEmpty(Q));
    printf("请输入整型队列元素(不超过%d个),-1为提前结束符:",MAX_QSIZE-1);
    do
    {
        scanf("%d",&d);//由键盘输入整型队列元素
        if(d==-1)//输入的是提前结束符
            break;//退出输入数据循环
        i++;//计数器+1
        EnQueue(Q,d);//入队输入元素
    }while(i<MAX_QSIZE-1);//队列元素的个数不超过允许的范围
    printf("队列长度为%d,",QueueLength(Q));
    printf("现在队列空否?%u(1:空 0:否)\n",QueueEmpty(Q));
    printf("连续%d次由队头删除元素,队尾插入元素:\n",MAX_QSIZE);
    for(m=1;m<=MAX_QSIZE;m++)
    {
        DeQueue(Q,d);//删除队头元素,其值赋给d
        printf("删除的元素是%d,请输入待插入的元素:",d);
        scanf("%d",&d);//输入要入队的元素
        EnQueue(Q,d);//将d入队
    }
    m=QueueLength(Q);//m为队列Q的长度
    printf("现在队列中的元素为");
    QueueTraverse(Q,printQueue);//从队头到队尾依次对队列Q的每个元素调用函数printQueue()
    printf("共向队尾插入了%d个元素。",i+MAX_QSIZE);
    if(m-2>0)
        printf("现在由队头删除%d个元素,",m-2);
    while(QueueLength(Q)>2)
    {
        DeQueue(Q,d);
        printf("删除的元素值为%d,",d);
    }
    j=GetHead(Q,d);//将队头元素赋给d
    if(j)
        printf("现在队头元素为%d\n",d);
    ClearQueue(Q);//清空队列Q
    printf("清空队列后,队列空否?%u(1:空 0:否)\n",QueueEmpty(Q));
    DestroyQueue(Q);//销毁队列Q
}
int main()
{
    
    test();//测试程序
    system("pause");
    return 0;
}