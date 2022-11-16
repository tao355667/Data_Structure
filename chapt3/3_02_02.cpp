/*
3-2-2 栈的应用-行编辑程序
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

typedef char SElemType; // SElemType为char类型
typedef int Status;
struct SqStack
{
    SElemType *base;
    SElemType *top;
    int stacksize;
};
FILE *fp; //文件指针
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
void copy(SElemType c)
{
    fputc(c, fp); //将字符c送至fp所指的文件中
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
//利用字符栈s，从终端接收一行并送到调用过程的数据区
void LineEdit()
{
    SqStack s;
    char ch;
    InitStack(s); //初始化栈s
    printf("请输入一个文本文件，^Z结束输入（Windows下Ctrl+z）：\n");
    printf("（#:删除上一个字符,@:删除这一行@之前的所有字符）\n");
    ch = getchar();   //接收字符到ch
    while (ch != EOF) //当全文未结束
    {
        while (ch != EOF && ch != '\n') //当全文未结束且未到行末
        {
            switch (ch) //对当前字符ch，分情况处理
            {
            case '#':
                if (!StackEmpty(s)) //仅当栈非空时弹出栈顶元素
                    Pop(s, ch);
                break;
            case '@':
                ClaerStack(s); //重置s为空栈
                break;
            default:
                Push(s, ch); //其他字符进栈
            }
            ch = getchar(); //从终端接收下一个字符
        }
        StackTraverse(s, copy); //将从栈底到栈顶的栈内字符依次传送至文件
        fputc('\n', fp);        //向文件输入一个换行符
        ClaerStack(s);          //重置s为空栈
        if (ch != EOF)          //全文未结束
            ch = getchar();     //从终端接收下一个字符到ch
    }
    DestroyStack(s); //销毁栈s
}

int main()
{
    //在当前目录建立ed.txt文件，用于写数据，如已有同名文件则先删除原文件
    fp = fopen("3_02_02.txt", "w");
    if (fp) //建立文件成功
    {
        LineEdit(); //行遍历
        fclose(fp); //关闭fp所指的文件
    }
    else
    {
        printf("建立文件失败！\n");
    }
    system("pause");
    return 0;
}