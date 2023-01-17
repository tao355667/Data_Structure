#include <stdlib.h>
#include <stdio.h>
typedef int ElemType;
//线索二叉树结构体
typedef struct ThreadNode
{
    ElemType data;                      //数据元素
    struct ThreadNode *lchild, *rchild; //左、右孩子指针
    int ltag, rtag;                     //左、右线索标志
} ThreadNode, *ThreadTree;

int main()
{

    return 0;
}