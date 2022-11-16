/*
数据结构 实验1-顺序表

*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define LIST_INIT_SIZE 5 //线性表存储空间的初始分配量
#define LIST_INCREMENT 2 //线性表存储空间的分配增量

typedef int ElemType;
typedef int Status;
//线性表结构体
struct Sqlist
{
	ElemType *elem; //存储空间基址
	int length;		//当前长度
	int listsize;	//当前分配的存储容量（sizeof(ElemType)为1单位）
};

//线性表初始化,构造一个空的线性表
Status InitList(struct Sqlist *L)
{ //空表：有个基址，表长为0
	//为线性表分配一片空间
	L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L->elem) //分配空间失败，报错
		exit(ERROR);
	L->length = 0;				  //空表长度为0
	L->listsize = LIST_INIT_SIZE; //初始存储容量
	return OK;
}
//在L中第i个位置之前插入新元素e，L的长度加1
Status ListInsert(struct Sqlist *L, int i, ElemType e)
{
	//判错     i范围(1,表长+1)
	if (i < 1 || i > L->length + 1)
		return ERROR;
	//补充分配空间
	if (L->length >= L->listsize)
	{
		//分配一块新空间
		ElemType *newbase = (ElemType *)realloc(L->elem, (L->listsize + LIST_INCREMENT) * sizeof(ElemType));
		if (!newbase) //分配空间失败
			exit(ERROR);
		L->elem = newbase;
		L->listsize += LIST_INCREMENT; //表长增加
	}
	//插入新元素，一些要元素后移
	ElemType *p, *q;
	ElemType ee;
	p = L->elem + i - 1;						   // p为第i个元素的地址
	for (q = L->elem + L->length - 1; q >= p; q--) // q初值为最后一个元素的地址
	{
		*(q + 1) = *(q);
	}
	*p = e;
	L->length++; //表长加一
	return OK;
}
//返回表长
int ListLength(struct Sqlist L)
{
	return L.length;
}
//遍历表中元素
void PrintList(struct Sqlist L)
{
	int i;
	for (i = 1; i <= L.length; i++)
	{ //第i个元素的地址为 L.elem+i-1
		printf("%d ", *(L.elem + i - 1));
	}
	printf("\n");
}
//对L中的元素从小到大排序 ,冒泡排序
void Sort(struct Sqlist *L)
{
	ElemType *pi, *pj, *start, *end;
	ElemType e;						  //用于交换值的中间变量
	start = L->elem;				  //第一个元素地址
	end = L->elem + L->length - 1;	  //最后一个元素地址
	for (pi = end; pi >= start; pi--) //第几趟
	{
		for (pj = start; pj < pi; pj++) //(pj从start开始)pj第一趟跑到end-1，第二趟跑到end-2，以此类推，最后一趟跑到start
		{								//从start往后，相邻元素顺序不对就交换
			if (*(pj) > *(pj + 1))
			{ //引入第三个变量 交换两个变量的值
				e = *(pj);
				*(pj) = *(pj + 1);
				*(pj + 1) = e;
			}
		}
	}
}
//合并La和Lb 到Lc
//若La和Lb都是从小到大顺序，则Lc也是从小到大的顺序
void MergeList(struct Sqlist *Lc, struct Sqlist La, struct Sqlist Lb)
{
	ElemType *pa, *pb;
	pa = La.elem; // pa指向La中未被添加的第一个元素
	pb = Lb.elem; // pb指向Lb中未被添加的第一个元素
	//将La中的元素添加进Lc
	while (pa <= La.elem + La.length - 1)
	{
		ListInsert(Lc, ListLength(*Lc) + 1, *pa);
		pa++; // pa后移
	}
	//将Lb中的元素添加进Lc
	while (pb <= Lb.elem + Lb.length - 1)
	{
		ListInsert(Lc, ListLength(*Lc) + 1, *pb);
		pb++; // pb后移
	}
	//对合并后的结果排序
	Sort(Lc);
}
//删除L中第i个元素
Status DeleteList_i(struct Sqlist *L, int i)
{
	ElemType *p, *q;
	// i值不合法
	if (i < 1 || i > L->length)
		return ERROR;
	p = L->elem + i - 1;		 // p为被删除元素的位置
	q = L->elem + L->length - 1; //表尾元素的位置
	//被删除元素之后的元素 前移
	for (++p; p <= q; ++p)
	{
		*(p - 1) = *p;
	}
	L->length--; //表长减1
	return OK;
}
//删除L中重复的元素，保留出现的第一个
void DeleteListRepe(struct Sqlist *L)
{
	ElemType *start, *end, *p, *q;
	start = L->elem;			   //第一个元素地址
	end = L->elem + L->length - 1; //最后一个元素地址
	for (p = start; p <= end - 1; p++)
	{ // p-从第一个元素到倒数第二个元素
		for (q = p + 1; q <= end; q++)
		{ //查看p之后的元素是否有和p相同的，若相同则删除
			if (*p == *q)
			{
				DeleteList_i(L, q - start + 1); //删除对应下标的元素
				end--;							//表最后一个元素的地址减"1"
				q--;							//表缩短了,q之后的元素前移了,此时不需要p++,p依然指向的是“下一个元素”
			}
		}
	}
}
//将L倒置
void ReverseList(struct Sqlist *L)
{ //倒置就是将对称位置的元素交换
	int i;
	ElemType e;
	for (i = 1; i <= L->length / 2; i++)
	{
		//与i（L->elem+i-1）对称的元素是L->elem+L->length-i
		e = *(L->elem + i - 1);
		*(L->elem + i - 1) = *(L->elem + L->length - i);
		*(L->elem + L->length - i) = e;
	}
}
//测试程序
void test()
{
	int j;
	struct Sqlist Lb, La, Lc;
	//顺序表初始化
	InitList(&La);
	InitList(&Lb);
	InitList(&Lc);
	//对La插入元素
	for (j = 1; j <= 8; j++)
	{
		if (j != 7)
			ListInsert(&La, 1, j);
	}
	printf("在La表头插入1,2,3,4,5,6,8后（逆序）: \nLa=");
	PrintList(La); //遍历表
	//对Lb插入元素
	for (j = 2; j <= 10; j += 2)
		ListInsert(&Lb, ListLength(Lb) + 1, j);
	printf("在Lb表尾依次插入2,4,6,8,10后（顺序）: \nLb=");
	PrintList(Lb); //遍历表
	//合并La和Lb 到Lc
	MergeList(&Lc, La, Lb);
	printf("有序（从小到大）合并La和Lb到Lc: \nLc=");
	PrintList(Lc); //遍历表
	//删去Lc中重复的元素
	DeleteListRepe(&Lc); //删去重复的元素
	printf("删去Lc中重复的元素后: \nLc=");
	PrintList(Lc); //遍历表
	//将Lc倒置
	ReverseList(&Lc); //将Lc倒置
	printf("将Lc倒置后: \nLc=");
	PrintList(Lc); //遍历表
}

int main()
{
	test();			 //测试程序
	system("pause"); //程序暂停
	return 0;
}
