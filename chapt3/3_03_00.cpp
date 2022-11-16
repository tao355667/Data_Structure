/*
3-3-0 队列-链式
队列：操作受限的线性表,一般用链式
*/
#include <cstdlib>
#include <cstdio>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define STACK_INIT_SIZE 10 //存储空间初始分配量
#define STACK_INCREMENT 2  //存储空间分配增量

typedef int QElemType;
typedef int Status;
//链式队列结点结构体
typedef struct QNode
{
    QElemType data;
    QNode *next;
} * QueuePtr;
//队列结构体
struct LinkQueue
{
    QueuePtr front, rear; //队头，队尾指针
};
//构造一个空队列Q
void InitQueue(LinkQueue &Q)
{
    //队头，队尾都指向头结点
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front) //生成头结点失败
        exit(OVERFLOW);
    Q.front->next = NULL;
}
//销毁队列Q（无论是否为空皆可）
void DestroyQueue(LinkQueue &Q)
{
    while (Q.front) // Q.front指向要被释放的结点，从头结点开始
    {
        Q.rear = Q.front->next; // Q.rear指向Q.front的下一个结点
        free(Q.front);          //释放Q.front所指的结点
        Q.front = Q.rear;       // Q.front后移
    }
}
//将队列Q置空
void ClearQueue(LinkQueue &Q)
{
    DestroyQueue(Q); //销毁Q
    InitQueue(Q);    //重新构造Q
}
//队列Q为空，返回TRUE。否则返回FALSE
Status QueueEmpty(LinkQueue Q)
{
    if (Q.front->next == NULL)
        return TRUE;
    else
        return FALSE;
}
//返回队列Q的长度
int QueueLength(LinkQueue Q)
{
    int i = 0;            //计数器，初值为0
    QueuePtr p = Q.front; // p指向头结点
    while (p != Q.rear)   // p不为尾结点时，p后移，i++。此处计数的结点不包括尾结点
    {
        i++;         //计数器加1
        p = p->next; // p后移
    }
    return i; //返回最终计数值
}
//若队列Q不空，则用e返回Q的队头元素，并返回OK；否则返回ERROR
Status GetHead(LinkQueue Q, QElemType &e)
{
    QueuePtr p;
    if (Q.front == Q.rear) //队列为空
        return ERROR;
    p = Q.front->next; // p指向队头元素结点
    e = p->data;       //用e返回队头元素结点data域的值
    return OK;
}
//插入元素e为队列Q的新的队尾元素
void EnQueue(LinkQueue &Q, QElemType e)
{
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode)); //生成新结点
    if (!p)
        exit(OVERFLOW); //失败则退出
    p->data = e;        //将e的值赋给新结点
    p->next = NULL;     //新结点的指针域为空
    Q.rear->next = p;   //原尾结点变为倒数第二个
    Q.rear = p;         //尾指针指向新的尾结点
}
//若队列Q不空，则删除Q的队头元素，用e返回其值
Status DeQueue(LinkQueue &Q, QElemType &e)
{
    if (Q.front == Q.rear) //队列为空
        return ERROR;
    QueuePtr p;
    p = Q.front->next;       // p指向队头结点
    e = p->data;             //将队头元素值赋给e
    Q.front->next = p->next; //头结点 指向 队头结点的下一个结点
    if (p == Q.rear)         //删除的结点是队尾结点
        Q.rear = Q.front;    //修改队尾指针指向头结点（空队列）
    free(p);                 //释放队头结点
}
void printQueue(QElemType c)
{
    printf("%d ", c);
}
//从队头到队尾依次队队列Q中的每个元素调用函数visit()
void QueueTraverse(LinkQueue Q, void (*visit)(QElemType))
{
    QueuePtr p = Q.front->next; // p指向队头结点
    while (p)                   // p不为空（队尾结点的next域为空）
    {
        visit(p->data); //对p的data域调用visit()
        p = p->next;    // p后移
    }
    printf("\n");
}

int main()
{
    int i;
    QElemType d;
    LinkQueue q;
    InitQueue(q); //构造空队列q，失败则程序结束（exit()）
    printf("成功构造了一个空队列后，q.front=%u,q.rear=%u\n", q.front, q.rear);
    printf("是否空队列？%d(1:空 0:否)\n", QueueEmpty(q));
    printf("队列的长度为%d\n", QueueLength(q));
    EnQueue(q, -5);
    EnQueue(q, 5);
    EnQueue(q, 10);
    printf("插入3个元素(-5,5,10)后，队列的长度为%d\n", QueueLength(q));
    printf("是否空队列？%d(1:空 0:否)\n", QueueEmpty(q));
    printf("队列的元素依次为");
    QueueTraverse(q, printQueue); //从队头到队尾，依次对队列q中每个元素调用函数printQueue
    i = GetHead(q, d);            //将队头元素赋给d
    if (i == OK)
        printf("队头元素是%d，", d);
    DeQueue(q, d); //删除队头元素，将其值赋给d
    printf("删除了队头元素%d，", d);
    i = GetHead(q, d); //将队头元素赋给d
    if (i == OK)
        printf("新的队头元素是%d\n", d);
    ClearQueue(q); //清空队列q
    printf("清空队列后，q.front=%u,q.rear=%u,q.front->next=%u\n", q.front, q.rear, q.front->next);
    DestroyQueue(q);
    printf("销毁队列后，q.front=%u,q.rear=%u\n", q.front, q.rear);

    system("pause");
    return 0;
}