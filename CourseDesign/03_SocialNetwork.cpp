/*
数据结构课设03《社交网络图实现》
题目03：社交网络图实现
 [问题描述]
        设计并实现一种简单的社交网络模型图。
 [基本要求]
（1） 每个人的信息是一个结点，人与人的联系构成边。个人信息里要有地理坐标信息，以便后续应用中能方便找靠近的人。
（2） 根据输入的任意两个人信息，给出他们之间的联系路径，最少经过多少人构成联系。
（3） 根据位置信息的动态变化，找寻附近能够联络的人，能够通过1次中间人能联络的人等。
（4） 可根据自己的创意添加更多的功能。
（5）作为一个完整的系统，应具有友好的界面和较强的容错能力；
（6）上机能正常运行，并写出课程设计报告。
--------------------------------------
1
14
李白
1 2
猪八戒
44 23
王道
2 20
王昭君
8 9
兰陵王
25 25
张三
10 13
唐僧
50 40
沙和尚
66 66
天勤
20 2
孙悟空
55 45
王五
99 102
线代
20 10
高数
1 1
概率
30 30
17
李白
猪八戒
李白
王道
王道
王昭君
王昭君
李白
王昭君
兰陵王
王昭君
猪八戒
兰陵王
张三
猪八戒
孙悟空
孙悟空
沙和尚
唐僧
孙悟空
唐僧
猪八戒
唐僧
沙和尚
王道
天勤
张三
王五
线代
高数
概率
线代
高数
概率
5
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
// #define OVERFLOW -2
#define MAX_DATA_SIZE 30

#define LIST_INIT_SIZE 1  //线性表存储空间的初始分配量
#define LIST_INCREMENT 20 //线性表存储空间的分配增量
typedef int ElemType;     //下标值
typedef int Status;
//个人信息，坐标结构体
typedef struct
{
    double x;
    double y;
} Position;
//个人信息结构体
typedef struct
{
    char name[MAX_DATA_SIZE]; //姓名
    Position pos;             //坐标
} VerTexType;
//边结构体
typedef struct ArcNode
{
    int adjvex;           //下标
    struct ArcNode *next; //指向下一个结点的指针
    double info;          //边的权
} ArcNode;
//顶点结构体
typedef struct VNode
{
    VerTexType data;  //图的顶点
    ArcNode *fistarc; //指向第一条依附该点的边的指针
} VNode;              // AdjList表示邻接表类型（MAX_NODE_SIZE个顶点）
//图结构体
typedef struct
{
    VNode *vertices;    // vertices--vertex的复数
    int vexnum, arcnum; //图的顶点数，弧数
    int vexsize;        //当前分配的存储容量（sizeof(ElemType)为1单位）
} ALGraph;
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
//图初始化
Status InitGraph(ALGraph &G)
{
    //为线性表分配一片空间
    G.vertices = (VNode *)malloc(LIST_INIT_SIZE * sizeof(VNode));
    if (!G.vertices) //分配空间失败，报错
    {
        printf("图初始化失败！");
        return ERROR;
    }
    G.vexnum = 0;               //初始结点数为0（因为还没有添加，相当于空表）
    G.arcnum = 0;               //初始边数为0
    G.vexsize = LIST_INIT_SIZE; //初始存储容量
    int i;
    for (i = 0; i < G.vexsize; i++)
        G.vertices[i].fistarc = NULL; //指针域置空
    return OK;
}
//将图的顶点名转换为下标
int name2num(ALGraph G, char data[MAX_DATA_SIZE])
{
    int i;
    for (i = 0; i < G.vexnum; i++)
    { //遍历图结点，找到对应的结点名
        if (!strcmp(G.vertices[i].data.name, data))
            return i;
    }
    return -1; //没找到
}
//输入图和下标，求两结点之间的距离
double distance(ALGraph G, int a, int b)
{
    double x1 = G.vertices[a].data.pos.x;
    double y1 = G.vertices[a].data.pos.y;
    double x2 = G.vertices[b].data.pos.x;
    double y2 = G.vertices[b].data.pos.y;
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
//增加一个结点
void AddOneNode(ALGraph &G)
{
    int i; //计数器
    //当前结点数目大于等于存储容量，扩容
    if (G.vexnum >= G.vexsize)
    {
        VNode *newbase = (VNode *)realloc(G.vertices, sizeof(VNode) * (G.vexsize + LIST_INCREMENT));
        G.vertices = newbase; //新分配的的空间地址
        int i;
        for (i = G.vexsize; i < G.vexsize + LIST_INCREMENT; i++)
            G.vertices[i].fistarc = NULL; //增加的空间指针域置空
        G.vexsize += LIST_INCREMENT;
    }
    printf("请输入的顶点名：");
    gets(G.vertices[G.vexnum].data.name); //姓名
    printf("请输入顶点坐标x y：");
    scanf("%lf %lf", &G.vertices[G.vexnum].data.pos.x, &G.vertices[G.vexnum].data.pos.y); //坐标
    G.vexnum++;                                                                           //结点数加一
    fflush(stdin);                                                                        //消除'\n'
}
// 2-增加多个结点
void AddMoreNode(ALGraph &G)
{
    int i;   //计数器
    int num; //要增加的结点数
    printf("请输入要增加的结点数：");
    scanf("%d", &num);
    fflush(stdin); //消除'\n'
    for (i = 1; i <= num; i++)
    {
        printf("请输入第%d个结点的信息:\n", i);
        AddOneNode(G); //增加一个结点
    }
    printf("增加了%d个结点！\n", num);
}
//增加一个边
Status AddOneEdge(ALGraph &G)
{
    //接收边
    char a[MAX_DATA_SIZE], b[MAX_DATA_SIZE]; //存储结点名
    printf("请输入图的边：\n");
    gets(a); //接收顶点名
    gets(b);
    int ax = name2num(G, a); //转换为下标
    int bx = name2num(G, b);
    if (ax == -1)
    {
        printf("结点%s不存在！", a);
        return ERROR;
    }
    if (bx == -1)
    {
        printf("结点%s不存在！", b);
        return ERROR;
    }
    //接收弧
    ArcNode *e = (ArcNode *)malloc(sizeof(ArcNode)); //建立一个弧结点
    //将顶点b插入到顶点a的链表中，头插
    e->adjvex = bx;                   //新结点存储顶点b的下标
    e->info = distance(G, ax, bx);    //求两结点之间的距离
    e->next = G.vertices[ax].fistarc; //新结点next指向结点a
    G.vertices[ax].fistarc = e;       //结点a指向新结点
    //将顶点a插入到顶点b的链表中，头插
    e = (ArcNode *)malloc(sizeof(ArcNode)); //建立一个弧结点
    //将顶点b插入到顶点a的链表中，头插
    e->adjvex = ax;                   //新结点存储顶点a的下标
    e->info = distance(G, ax, bx);    //求两结点之间的距离
    e->next = G.vertices[bx].fistarc; //新结点next指向结点b邻接表中的第一个结点
    G.vertices[bx].fistarc = e;       //结点a指向新结点
    G.arcnum++;                       //图的边数+1
    return OK;
}
// 3-增加多个边
void AddMoreEdge(ALGraph &G)
{
    int i;     //计数器
    int num;   //要增加的边数
    int j = 0; //实际增加的边数
    printf("请输入要增加的边数：");
    scanf("%d", &num);
    fflush(stdin); //消除'\n'
    for (i = 1; i <= num; i++)
    {
        printf("请输入第%d个边的信息:\n", i);
        if (AddOneEdge(G) == OK) //增加一个边
        {
            j++; //实际增加的结点数
        }
    }
    printf("增加了%d个边！\n", j);
}
//广度优先遍历图G（有距离判断）
void BFSNear(ALGraph G, int i, int *visited, LinkQueue &Q, int ax, int *vis, int dis)
{
    if (!visited[i]) //结点未被访问过
    {
        visited[i] = 1;        //标记该结点
        EnQueue(Q, i);         //结点入队
        while (!QueueEmpty(Q)) //队列不空
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
                    //访问结点
                    if (distance(G, ax, p->adjvex) < dis)
                    {
                        vis[p->adjvex] = 1;
                    }
                    //访问结点
                    visited[p->adjvex] = 1; //标记该结点
                    EnQueue(Q, p->adjvex);  //结点入队
                }
                p = p->next;
            }
        }
    }
}
//以a为起点,广度优先遍历图G（有距离判断）
void BFSNearTraverse(ALGraph G, int ax, int *vis, int dis)
{
    LinkQueue Q;  //新建一个队列
    InitQueue(Q); //队列初始化
    int i;
    // visited[i]表示下标为i的结点有没有被访问过
    int *visited = (int *)malloc(G.vexnum * sizeof(int));
    for (i = 0; i < G.vexnum; i++) //所有结点开始时未被访问
        visited[i] = 0;
    BFSNear(G, ax, visited, Q, ax, vis, dis);
    DeleteQueue(Q); //销毁队列
    free(visited);
}
//广度优先遍历图G
void BFSNear(ALGraph G, int i, int *visited, LinkQueue &Q, int *vis)
{
    if (!visited[i]) //结点未被访问过
    {
        visited[i] = 1;        //标记该结点
        EnQueue(Q, i);         //结点入队
        while (!QueueEmpty(Q)) //队列不空
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
                    //访问结点
                    vis[p->adjvex] = 1;
                    //访问结点
                    visited[p->adjvex] = 1; //标记该结点
                    EnQueue(Q, p->adjvex);  //结点入队
                }
                p = p->next;
            }
        }
    }
}
//以a为起点,广度优先遍历图G
void BFSNearTraverse(ALGraph G, int ax, int *vis)
{
    LinkQueue Q;  //新建一个队列
    InitQueue(Q); //队列初始化
    int i;
    // visited[i]表示下标为i的结点有没有被访问过
    int *visited = (int *)malloc(G.vexnum * sizeof(int));
    for (i = 0; i < G.vexnum; i++) //所有结点开始时未被访问
        visited[i] = 0;
    BFSNear(G, ax, visited, Q, vis);
    DeleteQueue(Q); //销毁队列
    free(visited);
}
// 1-创建图
void CreateGraph(ALGraph &G)
{
    int i;          //计数器
    AddMoreNode(G); //增加多个结点
    AddMoreEdge(G); //增加多个边
}
// 4-删除结点
void DeleteNode(ALGraph &G)
{
    int i;                 //循环计数器
    char a[MAX_DATA_SIZE]; //存储结点名
    printf("请输入要删除的结点名：\n");
    gets(a);                 //接收顶点名
    int ax = name2num(G, a); //转换为下标
    if (ax == -1)
    {
        printf("结点%s不存在！\n", a);
        return;
    }
    //释放结点的边占用的空间
    ArcNode *p = G.vertices[ax].fistarc;
    while (p)
    {
        ArcNode *delp = p;
        p = p->next;
        free(delp); //释放空间
    }
    G.vertices[ax].fistarc = NULL;
    //遍历所有边，删除与结点a相关的边
    for (i = 0; i < G.vexnum; i++) //遍历所有边
    {
        //下标 结点数据域
        ArcNode *q = G.vertices[i].fistarc; // q指向下标为i的结点的第一个边
        ArcNode *p;
        if (q)
            p = q->next; // q是p的前驱
        else             //该节点无邻居结点
            continue;
        while (q && q->adjvex == ax) //第一个结点需要被删除
        {
            ArcNode *del = q;
            G.vertices[i].fistarc = q->next;
            free(del);
            q = p;
            if (q)
                p = q->next;
        }
        while (p) //第一个结点不需要被删除
        {
            if (p->adjvex == ax) //删除与结点a相关的边
            {
                ArcNode *del = p;
                q->next = p->next;
                free(del); //释放空间
                p = q->next;
            }
            else
            {
                p = p->next;
                q = q->next;
            }
        }
    }
    //小于ax的结点下标不变，大于ax的结点下标-1
    for (i = 0; i < G.vexnum; i++) //遍历所有边
    {
        //下标 结点数据域
        ArcNode *p = G.vertices[i].fistarc; // p指向下标为i的结点的第一个边
        while (p)
        {
            if (p->adjvex > ax) //小于ax的结点下标不变，大于ax的结点下标-1
                p->adjvex--;
            p = p->next;
        }
    }
    //要删除的结点之后的元素前移
    for (i = ax; i < G.vexnum; i++)
    {
        G.vertices[i] = G.vertices[i + 1];
    }
    G.vexnum--; //结点数-1
}
// 5-显示图包含的信息
void PrintGraph(ALGraph G)
{
    int i;
    printf("图有%d个顶点，%d个边\n", G.vexnum, G.arcnum);
    printf("---------------------------------------\n");
    printf("%6s%10s%10s%10s\n", "下标", "姓名", "坐标x", "坐标y");
    printf("---------------------------------------\n");
    for (i = 0; i < G.vexnum; i++) //遍历结点
    {
        printf("%6d%10s%10.2f%10.2f\n", i, G.vertices[i].data.name, G.vertices[i].data.pos.x, G.vertices[i].data.pos.y);
    }
    printf("---------------------------------------\n");
    //显示图中结点的连接情况
    printf("图中结点的连接情况：\n");
    //存储矩阵，记录被访问过的边
    int *visited = (int *)malloc(G.vexnum * G.vexnum * sizeof(int));
    for (i = 0; i < G.vexnum * G.vexnum; i++) //数组所有元素置为0(未被访问过)
        visited[i] = 0;
    for (i = 0; i < G.vexnum; i++) //遍历结点
    {
        ArcNode *p = G.vertices[i].fistarc; // p指向下标为i的结点的第一个边
        while (p != NULL)
        {
            if (!visited[i * G.vexnum + p->adjvex])
            {
                printf("%10s", G.vertices[i].data.name);
                printf("--%6.2f--%s\n", p->info, G.vertices[p->adjvex].data); //输出权值和结点名
                visited[i * G.vexnum + p->adjvex] = 1;
                visited[p->adjvex * G.vexnum + i] = 1;
            }
            p = p->next;
        }
    }
    free(visited); //释放内存空间
    printf("---------------------------------------\n");
    //图的邻接表
    printf("图的邻接表：\n");
    for (i = 0; i < G.vexnum; i++) //遍历结点
    {
        //下标 结点数据域
        printf("%10s %2d", G.vertices[i].data.name, i);
        ArcNode *p = G.vertices[i].fistarc; // p指向下标为i的结点的第一个边
        while (p != NULL)
        {
            printf("->%6d,%-10.2f", p->adjvex, p->info); //输出结点下标和权值
            p = p->next;
        }
        printf("\n");
    }
    printf("---------------------------------------\n");
}
// 6-修改结点信息
void ModifyNode(ALGraph &G)
{
    int i;                 //循环计数器
    char a[MAX_DATA_SIZE]; //存储结点名
    printf("请输入要修改的结点的名称：");
    gets(a);                 //接收结点名
    int ax = name2num(G, a); //转换为下标
    if (ax == -1)
    {
        printf("结点%s不存在！\n", a);
        return;
    }
    printf("请输入新的顶点名：");
    gets(G.vertices[ax].data.name); //姓名
    printf("请输入新的顶点坐标x y：");
    if (scanf("%lf %lf", &G.vertices[ax].data.pos.x, &G.vertices[ax].data.pos.y) != 2) //坐标
    {
        printf("输入了错误信息！\n");
        return;
    }
    //更新与结点相关的边权
    for (i = 0; i < G.vexnum; i++) //遍历结点
    {
        ArcNode *p = G.vertices[i].fistarc;
        while (p)
        {
            if (p->adjvex == ax || i == ax)
                p->info = distance(G, p->adjvex, i);
            p = p->next;
        }
    }
    printf("修改结点信息成功！\n");
}
// 7-找附近能够联络的人
void PeopleNearby(ALGraph G)
{
    int i;                 //循环计数器
    char a[MAX_DATA_SIZE]; //存储结点名
    printf("请输入起点结点名称：");
    gets(a);                 //接收结点名
    int ax = name2num(G, a); //转换为下标
    if (ax == -1)
    {
        printf("结点%s不存在！\n", a);
        return;
    }
    int dist;
    printf("请输入最大距离：");
    scanf("%d", &dist);
    int *visit = (int *)malloc(G.vexnum * sizeof(int)); //用于记录可访问到的人员
    for (i = 0; i < G.vexnum; i++)
        visit[i] = 0;                    //数组初始化为0
    ArcNode *p = G.vertices[ax].fistarc; //起始结点的第一个边
    printf("------------------------------\n");
    printf("附近可直接联络的人：\n");
    printf("%8s%8s\n", "名称", "距离");
    printf("------------------------------\n");
    while (p) //遍历起点的所有邻居
    {
        if (p->info <= dist)
            printf("%8s%8.2f\n", G.vertices[p->adjvex], p->info);
        p = p->next;
    }
    printf("------------------------------\n");
    printf("附近可通过一个中间人联络的人：\n");
    printf("%8s%8s\n", "名称", "距离");
    printf("------------------------------\n");
    p = G.vertices[ax].fistarc;
    while (p) //遍历起点的所有邻居
    {
        ArcNode *q = G.vertices[p->adjvex].fistarc;
        while (q) //遍历邻居的邻居，将对应下标置1
        {
            if (distance(G, ax, q->adjvex) <= dist) //邻居的邻居在附近
                visit[q->adjvex] = 1;
            q = q->next;
        }
        p = p->next;
    }
    visit[ax] = 0;              //去除起点自身
    p = G.vertices[ax].fistarc; //起始结点的第一个边
    while (p)
    { //去除起点的邻居（可直接联络，不需要中间人）
        visit[p->adjvex] = 0;
        p = p->next;
    }
    for (i = 0; i < G.vexnum; i++)
    { //输出可通过一个中间人联系的人
        if (visit[i])
            printf("%8s%8.2f\n", G.vertices[i].data.name, distance(G, ax, i));
    }
    printf("------------------------------\n");
    printf("附近可通过一个以上中间人联络的人：\n");
    printf("%8s%8s\n", "名称", "距离");
    printf("------------------------------\n");
    for (i = 0; i < G.vexnum; i++)
        visit[i] = 0;                    //数组初始化为0
    BFSNearTraverse(G, ax, visit, dist); //找a可联络到的所有结点
    //去除a的邻居和a的邻居的邻居
    p = G.vertices[ax].fistarc;
    while (p) //遍历起点的所有邻居
    {
        ArcNode *q = G.vertices[p->adjvex].fistarc;
        while (q) //遍历邻居的邻居，将对应下标置1
        {
            visit[q->adjvex] = 0;
            q = q->next;
        }
        p = p->next;
    }
    for (i = 0; i < G.vexnum; i++)
    { //输出可通过一个以上中间人联系的人
        if (visit[i])
            printf("%8s%8.2f\n", G.vertices[i].data.name, distance(G, ax, i));
    }
    printf("------------------------------\n");
    free(visit);
}
// 8-找能够通过1个中间人联络的人
void FindThOneMid(ALGraph G)
{
    int i, j;              //循环计数器
    char a[MAX_DATA_SIZE]; //存储结点名
    printf("请输入起点结点名称：");
    gets(a);                 //接收结点名
    int ax = name2num(G, a); //转换为下标
    if (ax == -1)
    {
        printf("结点%s不存在！\n", a);
        return;
    }
    int *visit = (int *)malloc(G.vexnum * sizeof(int)); //用于记录可访问到的人员
    memset(visit, 0, G.vexnum * sizeof(int));           // visit数组初始化为0
    printf("\n-------------------------------------------------------------\n");
    printf("能直接联络的人:\n");
    ArcNode *p = G.vertices[ax].fistarc; //起始结点的第一个边
    while (p)
    { //起点的邻居（可直接联络，不需要中间人）
        visit[p->adjvex] = 1;
        p = p->next;
    }
    for (i = 0, j = 0; i < G.vexnum; i++)
    {
        if (visit[i])
        {
            if (j && j % 5 == 0) //一行输出5个结点
                printf("\n");
            printf("%10s ", G.vertices[i].data.name);
            j++;
        }
    }
    printf("\n-------------------------------------------------------------\n");
    //能通过一个中间人联络的人
    printf("能通过1个中间人联络的人:\n");
    memset(visit, 0, G.vexnum * sizeof(int)); // visit数组初始化为0
    p = G.vertices[ax].fistarc;               //起始结点的第一个边
    while (p)                                 //遍历起点的所有邻居
    {
        ArcNode *q = G.vertices[p->adjvex].fistarc;
        while (q) //遍历邻居的邻居，将对应下标置1
        {
            visit[q->adjvex] = 1;
            q = q->next;
        }
        p = p->next;
    }
    visit[ax] = 0;              //去除起点自身
    p = G.vertices[ax].fistarc; //起始结点的第一个边
    while (p)                   //去除起点的邻居（可直接联络，不需要中间人）
    {
        visit[p->adjvex] = 0;
        p = p->next;
    }
    for (i = 0, j = 0; i < G.vexnum; i++)
    {
        if (visit[i])
        {
            if (j && j % 5 == 0) //一行输出5个结点
                printf("\n");
            printf("%10s ", G.vertices[i].data.name);
            j++;
        }
    }
    printf("\n-------------------------------------------------------------\n");
    //能通过一个以上中间人联络的人
    printf("能通过1个以上中间人联络的人:\n");
    memset(visit, 0, G.vexnum * sizeof(int)); // visit数组初始化为0
    BFSNearTraverse(G, ax, visit);            //结点a能访问到的所有结点
    p = G.vertices[ax].fistarc;               //起始结点的第一个边
    //减去通过一个中间人可联络的结点及邻居结点
    while (p) //遍历起点的所有邻居
    {
        visit[p->adjvex] = 0;
        ArcNode *q = G.vertices[p->adjvex].fistarc;
        while (q) //遍历邻居的邻居，将对应下标置0
        {
            visit[q->adjvex] = 0;
            q = q->next;
        }
        p = p->next;
    }
    for (i = 0, j = 0; i < G.vexnum; i++)
    { //输出结点
        if (visit[i])
        {
            if (j && j % 5 == 0) //一行输出5个结点
                printf("\n");
            printf("%10s ", G.vertices[i].data.name);
            j++;
        }
    }
    printf("\n-------------------------------------------------------------\n");
    free(visit);
}
//主菜单
void showStart()
{
    // system("color 1f"); //设置界面颜色
    printf("\n******************^-^欢迎使用社交网络系统**************\n");
    printf("*               1 建立图                              *\n");
    printf("*               2 添加结点                            *\n");
    printf("*               3 添加边                              *\n");
    printf("*               4 删除结点及相关的边                  *\n");
    printf("*               5 显示图信息                          *\n");
    printf("*               6 修改结点信息                        *\n");
    printf("*               7 找附近能够联络的人                  *\n");
    printf("*               8 找能够通过1个中间人联络的人         *\n");
    printf("*               9 找两人间的联系路径                  *\n");
    printf("*               0 退出社交网络系统                    *\n");
    printf("******************^-^欢迎使用社交网络系统**************\n");
}
//提示用户输入信息
void InputMessage()
{
    printf("请输入0-9(输入99查看命令)>>");
}
//读取指令，此函数只接收一个整数
int MyScanf(int mode = 0)
{
    int a;
    while (1)
    {
        if (scanf("%d", &a)) //正确匹配
        {
            fflush(stdin); //清空标准输入缓存区
            return a;      //返回接收到的整数（指令）
        }
        else
        {
            fflush(stdin); //清除标准输入缓存区
            switch (mode)
            {
            case 0:
                InputMessage(); //提示用户输入信息
            }
        }
    }
}
int main()
{
    ALGraph G;
    InitGraph(G);
    showStart();    //显示主界面
    InputMessage(); //提示用户输入信息
    int menu;       //菜单
    menu = MyScanf();
    while (menu) // menu为0退出通讯录程序
    {
        switch (menu)
        {
        case 1:
            CreateGraph(G); //创建图
            break;
        case 2:
            AddMoreNode(G); //添加多个结点
            break;
        case 3:
            AddMoreEdge(G); //添加多个边
            break;
        case 4:
            DeleteNode(G); //删除结点
            break;
        case 5:
            PrintGraph(G); //显示图信息
            break;
        case 6:
            ModifyNode(G); //修改某结点的信息
            break;
        case 7:
            PeopleNearby(G); //找附近能联络的人
            break;
        case 8:
            FindThOneMid(G); //能够通过1个中间人联络的人
            break;
        case 9:
            break;
        case 99:
            showStart();
            break;
        default:
            printf("指令 %d 不存在！\n", menu);
        }
        InputMessage();   //提示用户输入信息
        fflush(stdin);    //清空标准输入缓存区
        menu = MyScanf(); //接收新指令
    }

    return 0;
}