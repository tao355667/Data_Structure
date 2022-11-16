/*
3-1 顺序栈
*/
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define STACK_INIT_SIZE 10 //存储空间初始分配量
#define STACK_INCREMENT 2  //存储空间分配增量

typedef int SElemType;
typedef int Status;
struct SqStack
{
    SElemType *base;
    SElemType *top;
    int stacksize;
};
//构造一个空栈
void InitStack(SqStack &S)
{
    if (!(S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType))))
        exit(OVERFLOW);            //动态分配存储空间失败，则退出
    S.top = S.base;                //栈顶指向栈底部
    S.stacksize = STACK_INIT_SIZE; //栈的初始大小为STACK_INIT_SIZE
}
//销毁栈S，S不再存在
void DestroyStack(SqStack &S)
{
    free(S.base);          //释放栈空间
    S.top = S.base = NULL; //栈顶、栈底的指针为空
    S.stacksize = 0;       //栈大小为0
}
//把栈S置为空栈
void ClaerStack(SqStack &S)
{
    S.top = S.base; //栈顶指向栈底
}
//若S为空栈，则返回TRUE，否则返回FALSE
Status StackEmpty(SqStack S)
{
    if (S.top == S.base) //空栈条件
        return TRUE;
    else
        return FALSE;
}
//返回栈S的元素个数，即栈的长度
int StackLength(SqStack S)
{
    return S.top - S.base; //注意指针的加减法运算规则
}
//若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
Status GetTop(SqStack S, SElemType &e)
{
    if (S.top > S.base) //栈不为空
    {
        e = *(S.top - 1); //栈顶指向的是空，减一格才到元素
        return OK;
    }
    else
        return ERROR;
}
//插入元素e为栈S新的栈顶元素
void Push(SqStack &S, SElemType e)
{
    if (S.top - S.base == S.stacksize) //栈满
    {
        S.base = (SElemType *)realloc(S.base, (S.stacksize + STACK_INCREMENT) * sizeof(SElemType));
        if (!S.base)
            exit(OVERFLOW);
        S.top = S.base + S.stacksize; //使栈顶指针指向新的栈顶
        S.stacksize += STACK_INCREMENT;
    }
    *(S.top)++ = e; //将e入栈,成为新的栈顶元素,栈顶指针上移一个单元
}
//若栈S不空,则删除S的栈顶元素,用e返回其值,并返回OK,否则返回ERROR
Status Pop(SqStack &S, SElemType &e)
{
    if (S.top == S.base) //栈空
        return ERROR;
    e = *--S.top; //将栈顶元素赋给e,栈顶指针下移一格存储单元
    return OK;
}
void vi(SElemType e)
{
    cout << e << " ";
}
//从栈底到栈顶依次对栈S中每个元素调用函数visit()
void StackTraverse(SqStack S, void (*visit)(SElemType))
{
    while (S.top > S.base) // S.base指向栈元素
    {
        visit(*S.base++); //对栈元素调用visit()
    }
    cout << endl; //栈顶指针上移一个存储单元
}
//测试程序
void test()
{
    int j;
    SqStack s;
    SElemType e;
    InitStack(s);
    for (j = 1; j <= 12; j++)
        Push(s, j);
    cout << "栈中元素依次为";
    StackTraverse(s, vi);
    Pop(s, e);
    cout << "弹出的栈顶元素 e=" << e << endl;
    cout << "栈是否为空?" << StackEmpty(s) << "(1:空,0:否)" << endl;
    GetTop(s, e);
    cout << "栈顶元素e=" << e << ",栈的长度为" << StackLength(s) << endl;
    ClaerStack(s);
    cout << "清空栈后,栈空否?" << StackEmpty(s) << "(1:空,0:否)" << endl;
    DestroyStack(s);
    cout << "销毁栈后,s.top=" << s.top << "s.base=" << s.base << "s.stacksize=" << s.stacksize << endl;
}
int main()
{

    test();
    system("pause");
    return 0;
}