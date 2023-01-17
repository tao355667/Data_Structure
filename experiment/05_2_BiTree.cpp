/*
实习05_二叉树的遍历
abe00f00c0gh000
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef char TElemType;
//二叉树的二叉链表存储结构
typedef struct BiTNode
{
    TElemType data;           //结点的值
    BiTNode *lchild, *rchild; //左右孩子指针
} BiTNode, *BiTree;
typedef BiTree SElemType;
//链栈结构体
typedef struct SNode
{
    SElemType data; //数据
    SNode *next;    //指向下一个结点的指针
} SNode, *LinkStack;
//栈初始化
void InitStack(LinkStack &S)
{
    S = (LinkStack)malloc(sizeof(SNode));
    S->next = NULL;
}
//判断栈是否为空
Status IsStackEmpty(LinkStack S)
{
    if (S->next) //栈不为空
        return FALSE;
    else //栈为空
        return TRUE;
}
//入栈
void Push(LinkStack S, SElemType e)
{
    LinkStack newNode = (LinkStack)malloc(sizeof(SNode));
    newNode->data = e;
    newNode->next = S->next;
    S->next = newNode;
}
//出栈
void Pop(LinkStack S, SElemType &e)
{
    if (S->next) //栈不为空
    {
        LinkStack del = S->next;
        S->next = S->next->next;
        e = del->data;
        free(del);
    }
}
//销毁栈
void DestroyStack(LinkStack &S)
{
    LinkStack p = S;
    while (p)
    {
        LinkStack del = p; //记录要删除的结点地址
        p = p->next;
        free(del);
    }
}

//构造空二叉树
void InitBiTree(BiTree &T)
{
    T = NULL;
}
//按二叉树的先序遍历结果构造二叉树T
void CreateBiTree(BiTree &T)
{
    TElemType ch; //接收数据
    scanf("%c", &ch);
    if (ch == '0') // 该结点应该为空
        T = NULL;  //结点置空
    else           //结点不为空
    {
        T = (BiTree)malloc(sizeof(BiTNode)); //生成根结点
        T->data = ch;
        CreateBiTree(T->lchild); //构造左子树（递归）
        CreateBiTree(T->rchild); //构造右子树（递归）
    }
}
//中序递归遍历二叉树T（非递归）
void InOrderTraverse(BiTree T)
{
    LinkStack S;  //栈
    InitStack(S); //初始化栈
    BiTree p = T;
    //非递归中序遍历二叉树
    while (p || !IsStackEmpty(S))
    {
        if (p)
        {
            Push(S, p);
            p = p->lchild;
        }
        else
        {
            Pop(S, p);
            printf("%c ", p->data); //访问出栈结点
            p = p->rchild;
        }
    }
    printf("\n");
    DestroyStack(S); //销毁栈
}

int main()
{
    BiTree T;
    InitBiTree(T);
    printf("请按先序输入二叉树：");
    CreateBiTree(T); //先序创建二叉树T
    printf("中序遍历该二叉树：\n");
    InOrderTraverse(T); //中序遍历二叉树T(非递归)
    system("pause");
    return 0;
}