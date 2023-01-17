/*
10
10 9 8 7 6 5 4 3 2 1
9
8 1 2 7 9 3 4 5 8
实习08_快速排序
4
2
3
5
3

5
3 5 4 1 2
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量

typedef int ElemType;
typedef int Status;
//线性表结构体
struct SqList
{
    ElemType *elem; //存储空间基址
    int length;     //当前长度
    int listsize;   //当前分配的存储容量（sizeof(ElemType)为1单位）
};
//线性表初始化,构造一个空的线性表
Status InitList(SqList &L)
{ //空表：有个基址，表长为0
    //为线性表分配一片空间
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem) //分配空间失败，报错
        exit(OVERFLOW);
    L.length = 0;                //空表长度为0
    L.listsize = LIST_INIT_SIZE; //初始存储容量
    return OK;
}
//在L的末尾插入元素e
Status ListInsert(SqList &L, ElemType e)
{
    ElemType *newbase, *q, *p;
    if (L.length >= LIST_INIT_SIZE)
        return ERROR;
    q = L.elem + L.length; // q为插入位置
    //元素右移
    for (p = L.elem + L.length - 1; p >= q; --p)
        *(p + 1) = *p;
    *q = e;     //插入e
    ++L.length; //表长增1
    return OK;
}
//遍历表中元素
void seeList(SqList L)
{
    int i;
    for (i = 1; i <= L.length; i++)
    {
        printf("%d ", *(L.elem + i - 1));
    }
    printf("\n");
}
//交换两数的值
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
//分割序列，返回中间的元素，
int Partiton(SqList &L, int low, int high)
{
    //下标从0开始，输入输出是“第几个”，差1
    low--;
    high--;
    //以第一个元素为基准
    int mid = low;       //基准的下标
    int m = L.elem[mid]; //基准的值
    while (low < high)
    { //退出条件：数组遍历结束，两指针相等或越位
        //从左向右找比基准小的元素
        while (low < high && L.elem[high] >= m)
        { //退出条件：数组遍历结束，找到符和条件的元素
            high--;
        }
        //从右往左找比基准大的元素
        while (low < high && L.elem[low] <= m)
        { //退出条件：数组遍历结束，找到符和条件的元素
            low++;
        }
        //找到之后交换两边的值
        if (low < high)
            swap(L.elem[low], L.elem[high]);
    }
    //若两指针相遇，则将基准放在相遇处，返回相遇处的下标
    swap(L.elem[mid], L.elem[high]); //交换基准处和相遇处的值
    return low + 1;                  //返回high+1和low+1没区别，因为此时low==high
}
//快速排序，输入参数较多，可进一步简化
void QSort(SqList &L, int low, int high)
{
    int pivotloc; //接收分割后的基准下标
    //对顺序表 L 中的子序列 L.r[low…high]作快速排序
    if (low < high)
    {
        //函数返回分割基准的下标，基准左边小于基准，基准右边大于基准
        pivotloc = Partiton(L, low, high);
        seeList(L);
        QSort(L, low, pivotloc - 1);  //基准前半部分数组
        QSort(L, pivotloc + 1, high); //基准后半部分数组
    }
}
//快速排序
void QuickSort(SqList &L)
{
    //对顺序表 L 作快速排序，以第一个元素的值作为基准
    QSort(L, 1, L.length);
}
int main()
{
    int n, numbuf;
    SqList L;
    InitList(L);
    printf("请输入需排序的数字的个数n：");
    scanf("%d", &n);
    printf("请输入数据：");
    while (n--)
    {
        scanf("%d", &numbuf);
        ListInsert(L, numbuf);
    }
    QuickSort(L); //对L进行快速排序
    printf("排序后的结果为：\n");
    seeList(L);
    system("pause");
    return 0;
}