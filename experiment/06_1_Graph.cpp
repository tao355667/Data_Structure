/*
实习06_图的深度优先遍历

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

#define MAX_VERTEX_NUM 20 //最大顶点数
#define MAX_NAME 20       //顶点名字最大长度

typedef int Status;
//顶点信息类型，只有顶点名称
struct VertexType
{
    char name[MAX_NAME];
};
enum GraphKind
{
    DG,
    DN,
    UDG,
    UDN
}; //{有向图，有向网，无向图，无向网}

struct InfoType
{
    int weight; //权值
};
struct ElemType
{
    int adjvex;     //该弧所指向的顶点的位置
    InfoType *info; //该弧的相关信息的指针（权值）
};

struct ArcNode //表结点，存弧的信息
{
    int adjvex;       //该弧所指向的顶点的位置（序号）
    InfoType *info;   //该弧的相关信息-权值
    ArcNode *nextarc; //指向下一条弧的指针
};
#define LNode ArcNode
#define next nextarc
typedef ArcNode *LinkList;
typedef struct
{
    VertexType data;   //顶点信息
    ArcNode *firstarc; //第一个表结点的地址，指向第一条依附该节点的弧的指针
} VNode, AdjList[MAX_VERTEX_NUM];

struct ALGraph
{
    AdjList vertices;   //头结点（顶点）数组
    int vexnum, arcnum; //图的当前顶点数和弧数
    GraphKind kind;     //图的种类标志
};
//若图G中存在顶点u，则返回该顶点在途中的位置（序号），否则返回-1
int LocateVex(ALGraph G, VertexType u)
{
    int i;
    for (i = 0; i < G.vexnum; ++i)                        //对所有顶点依次查找
        if (strcmp(u.name, G.vertices[i].data.name) == 0) //顶点与给定的u的顶点名称相同
            return i;                                     //返回顶点序号
    return -1;                                            //图G中不窜在与顶点u有相同名称的结点
}
//在L中第i个位置之前插入元素e
Status ListInsert(LinkList &L, int i, ElemType e)
{
    int j = 1;         //计数器初值为1
    LinkList p = L, s; // p指向第一个结点，s用于存储新节点
    if (i < 1)
        return ERROR;                    // i值不合法
    s = (LinkList)malloc(sizeof(LNode)); //生成新节点，以下将它插入L中
    s->adjvex = e.adjvex;                //该弧所指向的顶点的位置
    s->info = e.info;                    //该弧的相关信息的指针（权值）
    if (i == 1)
    {
        s->next = L; //新节点指向原第一个结点
        L = s;       // L指向新节点
    }
    else
    {
        while (p && j < i - 1) //寻找第i-1个结点
        {
            j++;         //计数器加1
            p = p->next; // p后移
        }
        if (!p) // i大于表长+1（p移到最后，为空了）
            return ERROR;
        s->next = p->next; // s的后继指向p的后继（第i个结点）
        p->next = s;       // p的后继指向s
    }
    return OK; //插入成功
}
//接收结点名称
void Input(VertexType ver)
{
    scanf("%s", ver.name);
}
//输入弧（边）的相关信息的函数
void InputArc(InfoType *&arc)
{
    arc = (InfoType *)malloc(sizeof(InfoType)); //动态生成存放弧（边）信息的空间
    scanf("%d", &arc->weight);
}
//创建图G
void CreateGraph(ALGraph &G)
{
    int i, j, k;
    VertexType v1, v2; //顶点类型
    ElemType e;        //表结点的元素类型（存储弧的信息）
    char s[3] = "边";
    printf("请输入图的顶点数 边数：");
    scanf("%d %d", &G.vexnum, &G.arcnum);
    printf("请输入%d个顶点的值（名称<%d个字符）：\n", G.vexnum, MAX_NAME);
    for (i = 0; i < G.vexnum; ++i) //构造顶点向量
    {
        Input(G.vertices[i].data);     //输入顶点信息
        G.vertices[i].firstarc = NULL; //初始化与该节点有关的出弧链表
    }
    printf("请输入%d条%s的", G.arcnum, s);
    switch (G.kind)
    {
    case DG:
        printf("弧尾 弧头：\n");
        break;
    case DN:
        printf("弧尾 弧头：\n");
        break;
    case UDG:
        printf("顶点1 顶点2：\n");
        break;
    case UDN:
        printf("顶点1 顶点2 边的信息");
    }
    for (k = 0; k < G.arcnum; ++k)
    {
        scanf("%s%s", v1.name, v2.name); //输入2顶点的名称
        i = LocateVex(G, v1);            //弧尾
        j = LocateVex(G, v2);            //弧头
        e.info = NULL;                   //给待插表结点e赋值，设图无弧（边）信息
        if (G.kind % 2)                  //网
            InputArc(e.info);            //动态生成存储空间，输入弧的相关信息
        e.adjvex = j;                    //弧头
        ListInsert(G.vertices[i].firstarc, 1, e);
        if (G.kind >= 2) //无向图或网
        {
            e.adjvex = i;                             // e.info不变，不需要再次赋值
            ListInsert(G.vertices[j].firstarc, 1, e); //插在第j个元素的表头
        }
    }
}
main()
{
    int i, j, k, n;
    char s[3] = "边";
    ALGraph g;
    VertexType v1, v2;

    return 0;
}