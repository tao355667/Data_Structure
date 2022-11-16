/*
5-1-1 变长参数表编程实例
*/
#include <cstdlib>
#include <cstdio>
#include <cstdarg> //可变参数形参

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define UNDERFLOW 4

#define MAX_ARRAY_DIM 8
typedef int ElemType; // ElemType为int类型
typedef int Status;

ElemType Max(int num, ...)
{
    va_list ap; //定义ap是变长参数表类型（c语言数据类型），在stdarg.h中
    int i;
    ElemType m, n;
    if (num < 1)
        exit(OVERFLOW);
    va_start(ap, num);        // ap指向固定参数num后面的实参表
    m = va_arg(ap, ElemType); //读取arg所指的实参，其类型为ElemType，将其赋给m，ap后移
    for (i = 1; i < num; ++i) //从第二个数到最后一个数
    {
        n = va_arg(ap, ElemType); //依次读取ap的所指的实参，将其赋给n，ap后移
        if (m < n)
            m = n;  // m中存放最大值
        va_end(ap); //与va_start()配对，结束对变长参数表的读取，ap不再指向变长参数表
        return m;   //将最大值返回
    }
}

int main()
{
    printf("1.最大值为%d\n", Max(4, 7, 9, 5, 8));
    printf("2.最大值为%d\n", Max(3, 17, 36, 25));

    system("pause");
    return 0;
}