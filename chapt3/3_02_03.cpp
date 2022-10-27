/*
3-2-3 栈的应用-迷宫求解
示例输入：
10,10
18
1,3
1,7
2,3
2,7
3,5
3,6
4,2
4,3
4,4
5,4
6,2
6,6
7,2
7,3
7,4
7,6
7,7
8,1
1,1
8,8



*/

#include<cstdlib>
#include<cstdio>

#define TRUE            1
#define FALSE           0
#define OK              1
#define ERROR           0
#define INFEASIBLE      -1
#define OVERFLOW        -2

#define STACK_INIT_SIZE 10          //存储空间初始分配量
#define STACK_INCREMENT 2           //存储空间分配增量
#define MAXLENGTH       25          //迷宫的最大行列
//迷宫坐标位置类型
struct PosType
{
    int x;//行值
    int y;//列值
};
//SElemType为结构体类型
typedef struct 
{
    int ord;        //通道块在路径上的“序号”
    PosType seat;   //通道块在迷宫中的“坐标位置”
    int di;         //从此通道块走向下一通道块的“方向”（0~3表示东南西北）
}SElemType;         
typedef int Status;
typedef int MazeType[MAXLENGTH][MAXLENGTH];//迷宫数组类型[行][列]
//全局变量
struct PosType begin,end;//与iostream中的属性/方法重名要修改
struct PosType direc[4]={{0,1},{1,0},{0,-1},{-1,0}};
MazeType m;     //迷宫数组
int x,y;        //迷宫的行数，列数
int curstep=1;  //当前足迹，初值（在入口处）为1
//-----------以下是栈-------------------------------------------------------
struct SqStack  //栈结构体
{
    SElemType *base;
    SElemType *top;
    int stacksize;
};
//构造一个空栈
void InitStack(SqStack &S)
{
    if(!(S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType))))
        exit(OVERFLOW);//动态分配存储空间失败，则退出
    S.top=S.base;//栈顶指向栈底部
    S.stacksize=STACK_INIT_SIZE;//栈的初始大小为STACK_INIT_SIZE
}
//销毁栈S，S不再存在
void DestroyStack(SqStack &S)
{
    free(S.base);       //释放栈空间
    S.top=S.base=NULL;  //栈顶、栈底的指针为空
    S.stacksize=0;      //栈大小为0
}
//把栈S置为空栈
void ClaerStack(SqStack &S)
{
    S.top=S.base;//栈顶指向栈底
}
//若S为空栈，则返回TRUE，否则返回FALSE
Status StackEmpty(SqStack S)
{
    if(S.top==S.base)//空栈条件
        return TRUE;
    else
        return FALSE;
}
//返回栈S的元素个数，即栈的长度
int StackLength(SqStack S)
{
    return S.top-S.base;//注意指针的加减法运算规则
}
//若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
Status GetTop(SqStack S,SElemType &e)
{
    if(S.top>S.base)//栈不为空
    {
        e=*(S.top-1);//栈顶指向的是空，减一格才到元素
        return OK;
    }
    else
        return ERROR;
}
//插入元素e为栈S新的栈顶元素
void Push(SqStack &S,SElemType e)
{
    if(S.top-S.base==S.stacksize)//栈满
    {
        S.base=(SElemType*)realloc(S.base,(S.stacksize+STACK_INCREMENT)*sizeof(SElemType));
        if(!S.base)
            exit(OVERFLOW);
        S.top=S.base+S.stacksize;//使栈顶指针指向新的栈顶
        S.stacksize+=STACK_INCREMENT;
    }
    *(S.top)++=e;//将e入栈,成为新的栈顶元素,栈顶指针上移一个单元
}
//若栈S不空,则删除S的栈顶元素,用e返回其值,并返回OK,否则返回ERROR
Status Pop(SqStack &S,SElemType &e)
{
    if(S.top==S.base)//栈空
        return ERROR;
    e=*--S.top;//将栈顶元素赋给e,栈顶指针下移一格存储单元
    return OK;
}
void vi(SElemType e)
{
    //cout<<e<<" ";
}
//从栈底到栈顶依次对栈S中每个元素调用函数visit()
void StackTraverse(SqStack S,void(*visit)(SElemType))
{
    while (S.top>S.base)//S.base指向栈元素
    {
        visit(*S.base++);//对栈元素调用visit()
    }
    printf("\n");//栈顶指针上移一个存储单元
}
//------------以下是迷宫函数--------------------------------------
//输出迷宫的解（m数组）
void Print()
{
    int i,j;
    for(i=0;i<x;i++)
    {
        for(j=0;j<y;j++)
        {
            printf("%3d",m[i][j]);
        }
        printf("\n");
    }
}
//设定迷宫布局,墙为0，通道为1
void Init()
{
    int i,j,x1,y1;
    printf("请输入迷宫的行数，列数（包括外墙）：");
    scanf("%d,%d",&x,&y);
    for(i=0;i<y;i++)
    {
        m[0][i]=0;      //上边
        m[x-1][i]=0;    //下边
    }
    for(i=1;i<x-1;i++)
    {
        m[i][0]=0;      //左边
        m[i][y-1]=0;    //右边
    }
    for(i=1;i<x-1;i++)
        for(j=1;j<y-1;j++)
            m[i][j]=1;  //除了外墙（值为0）外，其余都是通道（值为1）
    printf("请输入迷宫内墙单元数：");
    scanf("%d",&j);
    printf("请依次输入迷宫内墙每个单元的行数，列数：\n");
    for(i=1;i<=j;i++)
    {
        scanf("%d,%d",&x1,&y1);
        m[x1][y1]=0;//修改内墙的值为0
    }
    printf("迷宫结构如下：\n");
    Print();
    printf("请输入入口的行数，列数：");
    scanf("%d,%d",&begin.x,&begin.y);
    printf("请输入出口的行数，列数：");
    scanf("%d,%d",&end.x,&end.y);
}
//当迷宫m的b点的值为1，返回OK；否则返回ERROR
Status Pass(PosType b)
{
    if(m[b.x][b.y]==1)
        return OK;
    else
        return FALSE;
}
//使迷宫m的b点的值变为足迹（curstep）
void FootPrint(PosType b)
{
    m[b.x][b.y]=curstep;
}
//根据当前位置b及移动方向di，修改bi为下一位置
void NextPos(PosType &b,int di)
{
    b.x+=direc[di].x;
    b.y+=direc[di].y;
}
//使迷宫m的b点值变为-1（表示经试探该点无法到达终点）
void MarkPrint(PosType b)
{
    m[b.x][b.y]=-1;
}
//若迷宫m中存在从入口start到出口end的通道，则求得一条路径存放在栈中（从栈底到栈顶），返回TRUE
//否则返回FALSE
Status MazePath(PosType start,PosType end)
{
    PosType curpos=start;//当前位置=入口，之后根据情况变化
    SqStack S;      //顺序栈
    SElemType e;    //栈元素
    InitStack(S);   //初始化栈
    do
    {
        if(Pass(curpos))//当前位置可以通过
        {
            FootPrint(curpos);//留下足迹（矩阵m对应位置存为curpos）
            e.ord=curstep;  //栈元素的序号为当前足迹（第几步走出去了）
            e.seat=curpos;  //栈元素的位置为当前位置（x，y坐标）
            e.di=0;         //从当前位置出发，从东边开始
            Push(S,e);      //将当前点（足迹，位置，下一个走的是哪）压入栈
            curstep++;      //足迹加1
            if(curpos.x==end.x && curpos.y==end.y)//到达终点（出口）
                return TRUE;
            NextPos(curpos,e.di);//由当前位置及移动方向，算出下一个位置，赋给curpos
        }
        else//当前位置不能通过
        {
            if(!StackEmpty(S))//栈不空
            {
                Pop(S,e);   //退栈，将被弹出的元素赋值给e
                curstep--;  //足迹减一
                while(e.di==3 && !StackEmpty(S))//前一个位置处于最后一个方向（北）且栈不空
                {
                    MarkPrint(e.seat);//在前一个位置留下不能到达
                    Pop(S,e);   //再退回一步
                    curstep--;  //足迹再减1
                }
                if(e.di<3)//未到最后一个方向（北）
                {
                    e.di++;     //换下一个方向探索
                    Push(S,e);  //入栈该位置的下一个方向
                    curstep++;  //足迹加1
                    curpos=e.seat;  //确定当前位置
                    NextPos(curpos,e.di);//由当前位置和移动方向，确定下一个当前位置，仍赋给curpos
                }
            }
        }
    }while(!StackEmpty(S));
    return FALSE;
}
int main()
{
    Init();
    if(MazePath(begin,end))
    {
        printf("此迷宫从入口到出口有一条路径如下:\n");
        Print();
    }
    else
        printf("此迷宫没有从入口到出口的路径\n");
    system("pause");
    return 0;
}