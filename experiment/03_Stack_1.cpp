#include <iostream>
#include <cstring>
#include <stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACK_INCREMENT 20  //存储空间分配增量

typedef char SElemType;
typedef int Status;
//栈结构体
struct SqStack
{
    SElemType *base; //栈底指针
    SElemType *top;  //栈顶指针
    int stacksize;   //为栈分配的存储空间
};

//构造一个空栈
void InitStack(SqStack &S)
{
    if (!(S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType))))
        exit(OVERFLOW);            //动态分配存储空间失败，则退出
    S.top = S.base;                //栈顶指向栈底部
    S.stacksize = STACK_INIT_SIZE; //栈的初始大小为STACK_INIT_SIZE
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
//判断长度为len的字符串a是否为回文串
bool huiWen(char *a, int len)
{
    SElemType e;  //存储弹出栈的返回值
    SqStack s;    //栈结构体
    int i;        //计数器
    InitStack(s); //栈初始化
    //将数组内元素压进栈
    for (i = 0; i < len; i++)
    {
        Push(s, a[i]); //把字符串的元素压进栈
    }
    //将栈内元素出-倒序
    for (i = 0; i < len; i++)
    {
        Pop(s, e);     //把字符串的元素压出栈
        if (e != a[i]) //不相等就退出
        {
            return false; //不是回文串
        }
    }
    return true; //是回文串
}
int main()
{
    char a[1000] = {}; //接收字符串的数组
    cout << "输入一个字符串: ";
    gets(a); //接收字符串,不接收回车
    if (huiWen(a, strlen(a)))
        cout << "该字符串是“回文串”" << endl;
    else
        cout << "该字符串不是“回文串”" << endl;
    return 0;
}
