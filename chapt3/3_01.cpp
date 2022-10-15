/*
3-1 顺序栈
*/

#include<cstdlib>
#include<cstdio>
#include<iostream>
using namespace std;

#define TRUE            1
#define FALSE           0
#define OK              1
#define ERROR           0
#define INFEASIBLE      -1
#define OVERFLOW        -2
#define LIST_INIT_SIZE  10          //线性表存储空间的初始分配量
#define LISTINCREMENT   2           //线性表存储空间的分配增量

#define STACK_INIT_SIZE 10          //存储空间初始分配量
#define STACK_INCREMENT 2           //存储空间分配增量

typedef int SElemType;

struct SqStack
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
int main()
{
    int j;
    SqStack s;
    SElemType e;
    InitStack(s);

    getchar();
    return 0;
}