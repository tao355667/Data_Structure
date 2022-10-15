/*
2-3-0 静态链表的简单示例
用顺序存储结构实现链式存储的功能
*/
#include<cstdlib>
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
#define TRUE            1
#define FALSE           0
#define OK              1
#define ERROR           0
#define INFEASIBLE      -1
#define OVERFLOW        -2
#define LIST_INIT_SIZE  10      //线性表存储空间的初始分配量
#define LISTINCREMENT   2       //线性表存储空间的分配增量

#define MAX_SIZE    100         //链表的最大长度
#define N           6           //字符串的最大长度+1

typedef  int Status;
typedef char ElemType[N];
//线性表结构体
typedef struct 
{
    ElemType data;  //数据域
    int cur;        //指针域
}component,SLinkList[MAX_SIZE];

int main()
{
    SLinkList s={{"",1},{"ZHAO",2},{"QIAN",3},{"SUN",4},{"LI",5},{"ZHOU",6},{"WU",7},{"ZHENG",8},{"WANG",0}};
    int i=s[0].cur;                 //i指示第一个结点的位置(指针)
    while(i)                        //i不为0(结点不为空)
    {
        printf("%s ",s[i].data);    //输出链表的当前值(p->data)
        i=s[i].cur;                 //i后移(指针后移)
        //s[i]相当于“指针”，i表示的是结点在数组中的下标，下标与“指针”是一一对应的，故可用下标表示指针
        //但对结点进行操作时还是要用“指针”操作
    }
    printf("\n");
    s[4].cur=9;     //第4个结点（LI）的指针域指向第9个结点（WANG）
    s[9].cur=5;     //第9个结点（WANG）的指针域指向第5个结点（ZHOU）
    //此时结点为
    //{"",1},{"ZHAO",2},{"QIAN",3},{"SUN",4},{"LI",9},{"ZHOU",6},{"WU",7},{"ZHENG",8},{"WANG",0},{,5}
    strcpy(s[9].data,"SHI");
    //此时结点为
    //{"",1},{"ZHAO",2},{"QIAN",3},{"SUN",4},{"LI",9},{"ZHOU",6},{"WU",7},{"ZHENG",8},{"WANG",0},{"SHI",5}
    s[6].cur=8;
    //此时结点为
    //{"",1},{"ZHAO",2},{"QIAN",3},{"SUN",4},{"LI",9},{"ZHOU",6},{"WU",8},{"ZHENG",8},{"WANG",0},{"SHI",5}
    i=s[0].cur;
    while(i)
    {
        printf("%s ",s[i].data);
        i=s[i].cur;
    }
    printf("\n");
    printf("按数组输出：\n");
    for(int i=0;i<=10;i++)
    {
        printf("{\"%s\",%d},",s[i].data,s[i].cur);
    }
    getchar();//程序暂停
    return 0;
}
