/*
实习06_图的深度优先遍历
图1的邻接表：
a->b->d
b->e
c->a->f
d->b->f
e
f->e
深度优先遍历图1：abedfc
广度优先遍历图1：abdefc
图2的邻接表：
a->b->c
b->d
c->b->e
d->c
e->f->d
f
深度优先遍历图2：abdcef
广度优先遍历图2：abcdef
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define OK 1
#define ERROR 0

#define NodeSize 6 //图的结点数

typedef int Status;
//图结构体
typedef struct GraphNode
{
    char label; //图的顶点
    struct GraphNode *neighbors;
} GraphNode, *GraphPoint;
//向链表中插入元素
Status PushBack(GraphPoint &g, char c)
{
    //新建一个结点
    GraphPoint n = (GraphPoint)malloc(sizeof(GraphNode));
    if (!n)
        return ERROR;
    n->neighbors = g->neighbors;
    n->label = c;
    g->neighbors = n;
    return OK;
}
//深度优先遍历，G为邻接表表示的图，g为一个顶点指针，i为g在G中的下标记，visited[]表示顶点是否被访问过的数组
void DFS(GraphPoint G[], GraphPoint g, int i, int visited[])
{
    if (visited[i] == 0) //结点未被访问过
    {
        visited[i] = 1;
        printf("%c", g->label);      //访问该结点
        GraphPoint p = g->neighbors; //用指针p遍历结点
        //结点的下一个结点不为空
        while (p)
        {
            //对结点g指向结点进行深度遍历
            DFS(G, G[p->label - 'a'], p->label - 'a', visited);
            p = p->neighbors;
        }
    }
}
//深度优先遍历，G为邻接表表示的图
void DFSTraverse(GraphPoint G[])
{
    // visited[] 表示顶点是否被访问过的数组,0为未访问过，1为已访问过
    int visited[NodeSize] = {0};
    for (int i = 0; i < NodeSize; i++)
    { //依次对各顶点调用深度优先遍历的函数，已访问过的结点不会再被访问
        if (!visited[i])
        {
            DFS(G, G[i], i, visited);
        }
    }
    printf("\n");
}
//广度优先遍历
void BFS(GraphPoint G[], GraphPoint g, int i, int visited[])
{
    int vnum = 0;     //有几个结点没有被访问过
    GraphPoint p = g; //用指针p遍历结点
    //结点的下一个结点不为空
    while (p)
    {
        vnum++; //全部结点
        //结点的下一个结点未被访问过
        if (!visited[p->label - 'a'])
        {
            visited[p->label - 'a'] = 1;
            printf("%c", p->label); //访问该结点
        }
        else
        {
            vnum--; //被访问过的结点
        }
        p = p->neighbors;
    }
    if (!vnum) //有0个结点没被访问过（没被访问过的结点=全部结点-被访问过的结点）
        return;
    GraphPoint q = g->neighbors; //用指针q遍历结点
    //结点的下一个结点不为空
    while (q)
    {
        //对结点p指向的结点进行广度遍历
        BFS(G, G[q->label - 'a'], q->label - 'a', visited);
        q = q->neighbors;
    }
}
//广度优先遍历，G为邻接表表示的图
void BFSTraverse(GraphPoint G[])
{
    // visited[] 表示顶点是否被访问过的数组,0为未访问过，1为已访问过
    int visited[NodeSize] = {0};
    for (int i = 0; i < NodeSize; i++)
    { //依次对各顶点调用广度优先遍历的函数，已访问过的结点不会再被访问
        if (!visited[i])
        {
            BFS(G, G[i], i, visited);
        }
    }
    printf("\n");
}
//输出图的邻接表
void PrintGraph(GraphPoint G[])
{
    for (int i = 0; i < NodeSize; i++)
    { //依次对各顶点调用广度优先遍历的函数，已访问过的结点不会再被访问
        GraphPoint p = G[i];
        while (p->neighbors)
        {
            printf("%c->", p->label);
            p = p->neighbors;
        }
        printf("%c", p->label);
        printf("\n");
    }
}
void test1()
{
    GraphPoint G[NodeSize];
    //给每个结点初始化
    for (int i = 0; i < NodeSize; i++)
    {
        G[i] = (GraphPoint)malloc(sizeof(GraphNode));
        G[i]->label = 'a' + i;
        G[i]->neighbors = NULL;
    }
    //建立邻接表
    // 1-2-4
    // a-b-d
    PushBack(G[0], 'd');
    PushBack(G[0], 'b');
    // 2-5
    // b-e
    PushBack(G[1], 'e');
    // 3-1-6
    // c-a-f
    PushBack(G[2], 'f');
    PushBack(G[2], 'a');
    // 4-2-6
    // d-b-f
    PushBack(G[3], 'f');
    PushBack(G[3], 'b');
    // 5
    // 6-5
    // f-e
    PushBack(G[5], 'e');
    printf("图1的邻接表：\n");
    PrintGraph(G);
    //深度优先遍历
    printf("深度优先遍历图1：");
    DFSTraverse(G); //从数组下标为0的结点(a)开始遍历
    //广度优先遍历
    printf("广度优先遍历图1：");
    BFSTraverse(G); //从数组下标为0的结点(a)开始遍历
}
void test2()
{
    GraphPoint G[NodeSize];
    //给每个结点初始化
    for (int i = 0; i < NodeSize; i++)
    {
        G[i] = (GraphPoint)malloc(sizeof(GraphNode));
        G[i]->label = 'a' + i;
        G[i]->neighbors = NULL;
    }
    //建立邻接表
    PushBack(G[0], 'c');
    PushBack(G[0], 'b');

    PushBack(G[1], 'd');

    PushBack(G[2], 'e');
    PushBack(G[2], 'b');

    PushBack(G[3], 'c');

    PushBack(G[4], 'd');
    PushBack(G[4], 'f');

    printf("图2的邻接表：\n");
    PrintGraph(G);
    //深度优先遍历
    printf("深度优先遍历图2：");
    DFSTraverse(G); //从数组下标为0的结点(a)开始遍历
    //广度优先遍历
    printf("广度优先遍历图2：");
    BFSTraverse(G); //从数组下标为0的结点(a)开始遍历
}
main()
{
    test1(); //图1
    test2(); //图2
    system("pause");
    return 0;
}