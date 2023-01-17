/*
实习06_图的深度优先遍历
6
1
2
3
4
5
6
1->4
1->2
2->5
3->6
3->1
4->6
4->2
6->5
-1
5
1
2
4
5
6
1->4
1->2
2->5
4->6
4->2
6->5
-1
8
1
2
3
4
5
6
7
8
1->5
1->2
2->6
2->1
3->7
3->6
3->4
4->8
4->7
4->3
5->1
6->7
6->3
6->2
7->8
7->6
7->4
7->3
8->7
8->4
-1

*/
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MVNum 10 //图的最大顶点数

typedef int Status;     //函数返回值
typedef int VerTexType; //图的顶点名
typedef int ElemType;   //下标值

//队列结点结构体
typedef struct QNode
{
    ElemType data;
    struct QNode *next;
} QNode, *QueuePtr;
//队列结构体
struct LinkQueue
{
    QueuePtr front, rear; //队头，队尾指针
};
//边结构体
typedef struct ArcNode
{
    int adjvex; //下标
    struct ArcNode *next;
} ArcNode;
//顶点结构体
typedef struct VNode
{
    VerTexType data;     //图的顶点名
    ArcNode *fistarc;    //指向第一条依附该点的边的指针
} VNode, AdjList[MVNum]; // AdjList表示邻接表类型（MVNum个顶点）
//图结构体
typedef struct
{
    AdjList vertices;   // vertices--vertex的复数
    int vexnum, arcnum; //图的顶点数，弧数
} ALGraph;
//队列初始化
void InitQueue(LinkQueue &Q)
{
    //产生头节点，并使L指向此头节点
    Q.front = (QueuePtr)malloc(sizeof(QNode));
    Q.front->next = NULL; //指针域为空，无后继
    Q.rear = Q.front;     // Q.rear与Q.front共同指向链队列的头结点
}
//队列Q为空，返回TRUE，否则返回FALSE
Status QueueEmpty(LinkQueue Q)
{ //以Q.front为头指针的链表为空,则队列Q为空,反之亦然
    if (Q.front->next)
        return FALSE;
    else
        return TRUE;
}
//入队
void EnQueue(LinkQueue &Q, ElemType e)
{
    QueuePtr newNode = (QueuePtr)malloc(sizeof(QNode));
    newNode->data = e;
    newNode->next = NULL;
    Q.rear->next = newNode;
    Q.rear = Q.rear->next;
}
//出队
void DeQueue(LinkQueue &Q, ElemType &e)
{
    if (Q.front->next)
    {                            //删除Q.front后移即可结点并释放
        QueuePtr del = Q.front;  //删除原来的Q.front
        Q.front = Q.front->next; // Q.front后移
        e = Q.front->data;       //返回出队的数据
        free(del);               //释放要删除的结点
    }
}
//遍历队列
void printQueue(LinkQueue Q)
{
    QueuePtr q = Q.front->next;
    printf("队列元素：：");
    while (q)
    {
        printf("%d ", q->data);
        q = q->next;
    }
    printf("\n");
}
//删除队列
void DeleteQueue(LinkQueue &Q)
{
    QueuePtr p = Q.front;
    while (p) //将所有结点删除
    {
        QueuePtr del = p;
        p = p->next;
        free(del);
    }
    Q.front = Q.rear = NULL;
}
//将图的顶点名转换为下标
int name2num(ALGraph G, VerTexType data)
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    { //遍历图结点，找到对应的结点名
        if (G.vertices[i].data == data)
            return i;
    }
    return -1; //没找到
}
//创建图G
void CreateGraph(ALGraph &G)
{
    int i; //计数器
    printf("请输入图的顶点数：");
    scanf("%d", &G.vexnum);
    for (i = 0; i < G.vexnum; i++)
    {
        G.vertices[i].fistarc = NULL; //指针域置空
        printf("请输入下标为 %d 的顶点名：", i);
        scanf("%d", &G.vertices[i].data); //数据域
    }
    printf("图创建成功！\n");
    //接收弧
    VerTexType a, b; //存储结点名
    G.arcnum = 0;    //初始弧数为0
    while (1)
    {
        printf("请输入图的弧（-1结束）：");
        scanf("%d->%d", &a, &b); //接收顶点名
        int ax = name2num(G, a); //转换为下标
        int bx = name2num(G, b);
        if (a == -1 || b == -1) //结束标志
            break;
        //接收弧
        ArcNode *e = (ArcNode *)malloc(sizeof(ArcNode)); //建立一个弧结点
        //将顶点b插入到顶点a的链表中，头插
        e->adjvex = bx;                   //新结点存储顶点b的下标
        e->next = G.vertices[ax].fistarc; //新结点next指向结点a
        G.vertices[ax].fistarc = e;       //结点a指向新结点
        G.arcnum++;                       //图的弧数+1
    }
}
//输出图G的邻接表
void PrintGraph(ALGraph G)
{
    printf("图有%d个顶点，%d个弧\n", G.vexnum, G.arcnum);
    printf("图的邻接表：\n");
    int i;
    for (i = 0; i < G.vexnum; i++)
    {
        printf("%2d %2d", i, G.vertices[i].data);
        ArcNode *p = G.vertices[i].fistarc; // p指向第一个结点
        while (p != NULL)
        {
            printf("->%2d", p->adjvex); //输出结点下标
            // printf("->%d", G.vertices[p->adjvex].data); //输出结点名字
            p = p->next;
        }
        printf("\n");
    }
}
//深度优先遍历图G
void DFS(ALGraph G, int i, int *visited)
{
    if (!visited[i]) //结点未被访问过
    {
        //访问该结点
        printf("%d ", G.vertices[i].data);
        visited[i] = 1; //标记该结点
        //找深度方向的下一个结点
        ArcNode *p = G.vertices[i].fistarc;
        while (p)
        {
            //访问该节点之后的结点
            DFS(G, p->adjvex, visited);
            //找广度方向的下一个结点
            p = p->next;
        }
    }
}
//以a为起点，深度优先遍历图G
void DFSTraverse(ALGraph G, VerTexType a)
{
    int i;
    // visited[i]表示下标为i的结点有没有被访问过
    int *visited;
    visited = (int *)malloc(G.vexnum * sizeof(int));
    for (i = 0; i < G.vexnum; i++) //所有结点开始时未被访问
        visited[i] = 0;
    printf("以顶点%2d为起点，深度优先遍历：", a);
    i = G.vexnum;
    int num = name2num(G, a);
    while (i--) //共执行G.vexnum次
    {
        DFS(G, num, visited);
        num = (++num) % G.vexnum;
    }
    printf("\n");
    free(visited);
}
//广度优先遍历图G
void BFS(ALGraph G, int i, int *visited, LinkQueue &Q)
{
    if (!visited[i]) //结点未被访问过
    {
        printf("%d ", G.vertices[i].data); //访问该结点
        visited[i] = 1;                    //标记该结点
        EnQueue(Q, i);                     //结点入队
        while (!QueueEmpty(Q))             //队列不空
        {
            int v;         //存储出队结点值
            DeQueue(Q, v); //结点出队
            //找广度方向的结点
            ArcNode *p = G.vertices[v].fistarc;
            while (p)
            {
                //访问邻居结点，入队，以便之后访问它的邻居结点
                if (!visited[p->adjvex]) //结点未被访问过
                {
                    printf("%d ", G.vertices[p->adjvex].data); //访问该结点
                    visited[p->adjvex] = 1;                    //标记该结点
                    EnQueue(Q, p->adjvex);                     //结点入队
                }
                p = p->next;
            }
        }
    }
}
//以a为起点,广度优先遍历图G
void BFSTraverse(ALGraph G, VerTexType a)
{
    LinkQueue Q;  //新建一个队列
    InitQueue(Q); //队列初始化
    int i;
    // visited[i]表示下标为i的结点有没有被访问过
    int *visited;
    visited = (int *)malloc(G.vexnum * sizeof(int));
    for (i = 0; i < G.vexnum; i++) //所有结点开始时未被访问
        visited[i] = 0;
    printf("以顶点%2d为起点，广度优先遍历：", a);
    // i = G.vexnum;
    int num = name2num(G, a);
    while (i--) //共执行G.vexnum次
    {
        BFS(G, num, visited, Q);
        num = (++num) % G.vexnum;
    }
    printf("\n");
    DeleteQueue(Q); //销毁队列
    free(visited);
}
void test1()
{
    printf("测试图1:\n");
    ALGraph G;
    int i;
    CreateGraph(G); //创建图G
    PrintGraph(G);  //输出图G的邻接表
    for (i = 0; i < G.vexnum; i++)
    {
        DFSTraverse(G, G.vertices[i].data); //深度优先遍历图G
    }
    for (i = 0; i < G.vexnum; i++)
    {
        BFSTraverse(G, G.vertices[i].data); //广度优先遍历图G
    }
}
void test2()
{
    printf("\n测试图2:\n");
    ALGraph G;
    int i;
    CreateGraph(G); //创建图G
    PrintGraph(G);  //输出图G的邻接表
    for (i = 0; i < G.vexnum; i++)
    {
        DFSTraverse(G, G.vertices[i].data); //深度优先遍历图G
    }
    for (i = 0; i < G.vexnum; i++)
    {
        BFSTraverse(G, G.vertices[i].data); //广度优先遍历图G
    }
}
void test3()
{
    printf("\n测试图3:\n");
    ALGraph G;
    int i;
    CreateGraph(G); //创建图G
    PrintGraph(G);  //输出图G的邻接表
    for (i = 0; i < G.vexnum; i++)
    {
        DFSTraverse(G, G.vertices[i].data); //深度优先遍历图G
    }
    for (i = 0; i < G.vexnum; i++)
    {
        BFSTraverse(G, G.vertices[i].data); //广度优先遍历图G
    }
}

main()
{
    test1(); //图1测试程序
    test2(); //图2测试程序
    test3(); //图3测试程序
    system("pause");
    return 0;
}