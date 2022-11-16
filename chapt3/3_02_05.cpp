/*
3-2-5 栈的应用-递归求解汉诺塔问题
示例输入：
3
示例输出：

*/
#include <cstdlib>
#include <cstdio>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

//全局变量
int c = 0; //搬动次数
//-----------以下是汉诺塔函数-------------------------------------------------------
//移动一个盘
void move(char x, int n, char z)
{
    printf("第%i步：将%i号盘从%c移动到%c\n", ++c, n, x, z);
}
//汉诺塔求解函数
void hanoi(int n, char x, char y, char z)
{
    if (n == 1)
    {
        move(x, 1, z);
    }
    else
    {
        hanoi(n - 1, x, z, y); //将n-1个盘移到中转柱
        move(x, n, z);         //将标号为n的盘从起点移到终点
        hanoi(n - 1, y, x, z); // n-1阶问题，但起点和终点柱子不同
    }
}

int main()
{
    int n;
    printf("3个塔座为a,b,c，圆盘最初在a座，借助b座移到c座。请输入圆盘数：");
    scanf("%d", &n);
    hanoi(n, 'a', 'b', 'c');

    system("pause");
    return 0;
}