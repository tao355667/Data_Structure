/*
2-1 线性表的顺序表示和实现
线性表的动态分配顺序存储结构
特点：
顺序表存储结构容易实现随机存取线性表第i个数据元素的操作
实现插入操作时要移动大量元素，适用于相对稳定的线性表
如职工工资表，学生学籍等
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
#define LIST_INIT_SIZE  10      //线性表存储空间的初始分配量
#define LIST_INCREMENT   2       //线性表存储空间的分配增量

typedef  int ElemType;
typedef  int Status;

//线性表结构体
struct Sqlist
{
    ElemType *elem; //存储空间基址
    int length;     //当前长度
    int listsize;   //当前分配的存储容量（sizeof(ElemType)为1单位）
};
//线性表初始化,构造一个空的线性表
Status InitList(Sqlist &L)
{//空表：有个基址，表长为0
    //为线性表分配一片空间
    L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem)                 //分配空间失败，报错
        exit(OVERFLOW);
    L.length=0;                 //空表长度为0
    L.listsize=LIST_INIT_SIZE;  //初始存储容量
    return OK;
}
//销毁线性表L
Status DestroyList(Sqlist &L)
{
    free(L.elem);   //释放空间
    L.elem=NULL;    //基址设0
    L.length=0;     //表长为0
    L.listsize=0;   //初始容量为0
    return OK;
}
//将表L置为空表
Status ClearList(Sqlist &L)
{//并没有改变内存中的数据，很多操作如遍历表是基于表长的，表长为0则那些操作无法进行，相当于表被置空
    L.length=0;
    return OK;
}
//L为空表，返回TRUE，否则返回FALSE
Status ListEmpty(Sqlist L)
{
    if(L.length==0)
        return TRUE;
    else
        return FALSE;
}
//返回表长
int ListLength(Sqlist L)
{
    return L.length;
}
//输入：线性表L，数据坐标，用于存储返回值的变量。
//输出：用e返回线性表L中第i个数据的值。
Status GetElem(Sqlist L,int i,ElemType &e)
{
    //输入数据异常
    if(i<1||i>L.length)
        exit(ERROR);
    //指针加1：指向该数据类型的数据的下一个存储单元
    //为什么-1？因为线性表数据下标从1开始，数组下标从0开始
    e=*(L.elem+i-1);
    return OK;
}
//比较函数，与LocatedElem()配合使用
Status comp(ElemType a,ElemType b)
{
    return a==b*b?TRUE:FALSE;
}
//输入：非空线性表L，compare()是数据元素判定函数（满足1，否则0）
//输出：L中第一个与e满足关系compare()的数据元素的位序
//用到了函数指针
int LocateElem(Sqlist L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    ElemType *p;
    int i=1;
    p=L.elem;
    //从头开始，没有符合条件的元素就一直向后遍历数据元素
    while (i<=L.length && !compare(*p++,e))
        ++i;
    //符合条件返回下标，否则返回0
    if(i<=L.length)
        return i;
    else
        return 0;
    
}
//输入：一个线性表，线性表中的一个元素（不能是第一个），存储返回值的变量
//输出：返回线性表中一个元素的前驱
Status PriorElem(Sqlist L,ElemType cur_e,ElemType &pre_e)
{
    int i=2;
    ElemType *p=L.elem+1;
    while(i<=L.length && *p!=cur_e)
    {
        p++;
        i++;
    }
    if(i>L.length)
        return INFEASIBLE;
    else
    {
        pre_e=*--p;
        return OK;
    }
}
//输入：一个线性表，线性表中的一个元素（不能是最后一个），存储返回值的变量
//输出：返回线性表中一个元素的后继
Status NextElem(Sqlist L,ElemType cur_e,ElemType &next_e)
{
    int i=1;
    ElemType *p=L.elem;
    while(i<L.length && *p!=cur_e)
    {
        i++;
        p++;
    }
    if(i==L.length)
        return INFEASIBLE;
    else
    {
        next_e=*++p;
        return OK;
    }
}
//在L中第i个位置之前插入新元素e，L的长度加1
Status ListInsert(Sqlist &L,int i,ElemType e)
{
    ElemType *newbase,*q,*p;
    //i值不合法
    if(i<1 || i>L.length+1)
        return ERROR;
    //当前存储空间已满，增加存储容量
    if(L.length>=L.listsize)
    {
        //分配一块更大的空间
        newbase=(ElemType*)realloc(L.elem,(L.listsize+LIST_INCREMENT)*sizeof(ElemType));
        //空间分配失败则退出
        if(!newbase) exit(OVERFLOW);
        //增加存储容量
        L.listsize += LIST_INCREMENT;
    }
    q=L.elem+i-1;//q为插入位置
    //元素右移
    for(p=L.elem+L.length-1;p>=q;--p)
        *(p+1)=*p;
    *q=e;//插入e
    ++L.length;//表长增1
    return OK;
}
//删除L中第i个元素，用e返回该元素的值
Status ListDelete(Sqlist L,int i,ElemType &e)
{
    ElemType *p,*q;
    //i值不合法
    if(i<1 || i>L.length)
        return ERROR;
    p=L.elem+i-1;//p为被删除元素的位置
    e=*p;//被删除的值赋给e
    q=L.elem+L.length-1;//表尾元素的位置
    for(++p;p<=q;++p)
    {
        *(p-1)=*p;
    }
    L.length--;//表长减1
    return OK;
}
//ListTraverse()调用
void visit(ElemType &a)
{
    cout<<a<<" ";
}
//ListTraverse()调用，元素值翻倍
void dbl(ElemType &a)
{
    a *= 2;
}
//对L的每个元素调用vi()，一旦vi()失败，则操作失败
//vi()形参是引用，可改变元素的值。如将表中的元素都变为2倍
Status ListTraverse(Sqlist L,void(*vi)(ElemType&))
{
    ElemType *p;
    int i;
    p=L.elem;
    for(i=1;i<=L.length;i++)
        vi(*p++);
    cout<<endl;
    return OK;
}
//遍历表中元素
void seeList(Sqlist L)
{
    int i;
    for(i=1;i<=L.length;i++)
    {
        cout<<*(L.elem+i-1)<<" ";
    }
    cout<<endl;
}
int main()
{
    //测试线性表相关函数是否正常
    Sqlist L;
    ElemType e,e0;//存储返回值
    Status i;
    int j,k;
    i=InitList(L);
    printf("初始化后：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
    for(j=1;j<=5;j++)
        i=ListInsert(L,1,j);
    printf("在表头依次插入1~5后：*L.elem=");
    seeList(L);//遍历表
    printf("L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
    i=ListEmpty(L);
    printf("L是否为空：i=%d（1是，0否）\n",i);
    i=ClearList(L);
    printf("清空L后：L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
    i=ListEmpty(L);
    printf("L是否为空：i=%d（1是，0否）\n",i);
    for(j=1;j<=10;j++)
        i=ListInsert(L,j,j);
    printf("在表尾依次插入1~10后：*L.elem=");
    seeList(L);//遍历表
    ListInsert(L,1,0);
    printf("在表头插入0后：*L.elem=");
    seeList(L);//遍历表
    printf("L.elem=%u(有可能改变) L.length=%d(改变) L.listsize=%d(改变)\n",L.elem,L.length,L.listsize);
    GetElem(L,5,e);
    printf("第五个元素的值为:%d\n",e);
    for(j=3;j<=4;j++)
    {
        k=LocateElem(L,j,comp);
        if(k)
            printf("第%d个元素的值为%d的平方\n",k,j);
        else
            printf("没有值为%d的平方的元素\n",j);
    }
    for(j=1;j<=2;j++)
    {
        GetElem(L,j,e0);
        i=PriorElem(L,e0,e);
        if(i==INFEASIBLE)
            printf("元素%d无前驱\n",e0);
        else
            printf("元素%d前驱为:%d\n",e0,e);
    }
    for(j=ListLength(L)-1;j<=ListLength(L);j++)
    {
        GetElem(L,j,e0);
        i=NextElem(L,e0,e);
        if(i==INFEASIBLE)
            printf("元素%d无后继\n",e0);
        else
            printf("元素%d后继为:%d\n",e0,e);
    }
    k=ListLength(L);
    for(j=k+1;j>=k;j--)
    {
        i=ListDelete(L,j,e);
        if(i==ERROR)
            printf("删除第%d个数据失败\n",j);
        else
            printf("删除的元素值为:%d\n",e);
    }
    printf("依次输出L的元素: ");
    ListTraverse(L,visit);
    printf("L的元素值加倍后:");
    ListTraverse(L,dbl);
    ListTraverse(L,visit);
    DestroyList(L);
    printf("销毁L后:L.elem=%u L.length=%d L.listsize=%d\n",L.elem,L.length,L.listsize);
    
    getchar();//程序暂停
    return 0;
}
