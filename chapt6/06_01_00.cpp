/*
6-1-0 二叉树-二叉树的顺序存储
*/
#include <cstring>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAX_TREE_SIZE 100 //二叉树的最大结点数
#define CHAR 1
// CHAR为1，结点类型为字符。CHAR为0，结点类型为整型
#if CHAR
typedef char TElemType;
#else
typedef int TElemType;
#endif

#define ClearBiTree InitBiTree   //在顺序存储结构中,两函数完全一样
#define DeatroyBiTree InitBiTree //在顺序存储结构中,两函数完全一样

typedef TElemType SqBiTree[MAX_TREE_SIZE]; // 0号存储单元存储根节点

TElemType Nil = ' '; //设字符型以空格符号为空

struct position
{
    int level, order; //结点所在的层，在该层的序号(按满二叉树计算)
};
//构造空二叉树T.因为T是数组名,故不需要&
void InitBiTree(SqBiTree T)
{
    int i;
    for (i = 0; i < MAX_TREE_SIZE; i++)
        T[i] = Nil; //初值为空
}
//按层序次序输入二叉树中结点的值(字符型或整型),构造顺序存储的二叉树T
void CreateBiTree(SqBiTree T)
{
    int i = 0;
    InitBiTree(T); //构造空二叉树T
}
void test()
{
}
int main()
{
    test();
    system("pause");
    return 0;
}