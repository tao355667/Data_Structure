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
    else
    {
        T = (BiTree)malloc(sizeof(BiTNode)); //生成根结点
        T->data = ch;
        CreateBiTree(T->lchild); //构造左子树（递归）
        CreateBiTree(T->rchild); //构造右子树（递归）
    }
}
//中序递归遍历二叉树T
void InOrderTraverse(BiTree T)
{
    if (T)
    {
        InOrderTraverse(T->lchild); //遍历左子树（递归）
        printf("%c ", T->data);
        InOrderTraverse(T->rchild); //遍历左子树（递归）
    }
}
int main()
{
    BiTree T;
    InitBiTree(T);
    printf("请按先序输入二叉树：");
    CreateBiTree(T); //先序创建二叉树T
    printf("中序遍历该二叉树：\n");
    InOrderTraverse(T); //中序遍历二叉树T
    return 0;
}