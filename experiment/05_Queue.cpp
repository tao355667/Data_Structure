/*
实验4  循环队列

*/
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_QSIZE 8 //最大队列长度+1,有一个不用

typedef int QElemType;
typedef int Status;
//循环队列结构体
struct SqQueue
{
    QElemType *base; //初始化动态内存分配空间
    int front;       //头指针,若队列不动,指向队列头元素
    int rear;        //尾指针,若队列不空,指向队列尾元素的下一个位置
};
//构造一个空队列
void InitQueue(SqQueue &Q)
{
    Q.base = (QElemType *)malloc(MAX_QSIZE * sizeof(SqQueue));
    if (!Q.base) //存储分配失败
        exit(OVERFLOW);
    Q.front = Q.rear = 0; //队列为空
}
//插入元素e为队列Q的新的队尾元素
Status EnQueue(SqQueue &Q, QElemType e)
{
    if ((Q.rear + 1) % MAX_QSIZE == Q.front) //队列满
        return ERROR;
    Q.base[Q.rear] = e;                //将e插在队尾
    Q.rear = (Q.rear + 1) % MAX_QSIZE; //队列指针+1后对MAX_QSIZE取余
    return OK;
}
void printQueue(QElemType c)
{
    printf("%d ", c);
}
//从队头到队尾依次对队列Q中每个元素调用函数visit()
void QueueTraverse(SqQueue &Q, void (*visit)(QElemType))
{
    int i = Q.front;    // i最初指向队头元素
    while (i != Q.rear) // i指向队列Q中的元素
    {
        visit(Q.base[i]);        //对i所指元素调用函数visit()
        i = (i + 1) % MAX_QSIZE; // i指向下一个元素
    }
    printf("\n");
}
//若队列Q不空,则删除Q的队头元素,并返回OK,否则返回ERROR
Status DeQueue(SqQueue &Q, QElemType &e)
{
    if (Q.front == Q.rear) //栈空
        return ERROR;
    e = Q.base[Q.front];                 //返回被删除的元素值
    Q.front = (Q.front + 1) % MAX_QSIZE; //移动队头指针
    return OK;
}
int main()
{
    int i; //循环计数器
    QElemType e;
    SqQueue q;
    InitQueue(q);

    int a[10] = {7, 5, 3, 9, 2, 4};
    for (i = 0; i < 6; i++) //将数据{7,5,3,9,2,4}插入队列
    {
        EnQueue(q, a[i]);
        printf("元素%d入队\n", a[i]);
    }
    for (i = 0; i < 3; i++)
    {
        DeQueue(q, e); //出队列
        printf("元素%d出队\n", e);
    }
    EnQueue(q, 15); // 15入队
    printf("元素%d入队\n", 15);
    EnQueue(q, 18); // 18入队
    printf("元素%d入队\n", 18);

    printf("队列中的元素（从队头到队尾）：\n");
    QueueTraverse(q, printQueue); //从队头到队尾输出队列中的元素
    system("pause");
    return 0;
}