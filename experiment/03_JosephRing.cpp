/*
数据结构 实验3 - 约瑟夫回环
无头结点的单向循环链表，尾指针
*/
#include<iostream>
#include<iomanip>//setw()
#include<cstdlib>//malloc()
using namespace std;
#define TRUE            1
#define FALSE           0
#define OK              1
#define ERROR           0
//类型定义
typedef int ElemType;
typedef int Status;
//链表结构体
typedef struct LNode{
	ElemType name;		//玩家编号
	ElemType password;	//玩家密码
	struct LNode *next;	//指向结点结构体的指针
}LNode,*LinkList;
//链表初始化
Status InitList(LinkList &L)
{
	L=NULL;
	if(!L)
        return OK;
    else
        return ERROR;
}
//遍历表
void visit(ElemType c)
{
    cout<<setw(5)<<c<<" ";
}
//依次对L的每个数据元素调用函数vi()一旦vi()失败，则操作失败
Status PrintGamer(LinkList L,void(*vi)(ElemType))
{
	//显示玩家编号信息
	cout<<"玩家编号: ";
    LinkList p=L->next;
    while(p != L)//显示玩家信息
    {
        vi(p->name);//显示数据
        p=p->next;//p后移
    }
	vi(p->name);//显示最后一个数据
    cout<<endl;
	//显示玩家密码信息
	p=L->next;
	cout<<"玩家密码: ";
	while(p != L)//显示玩家持有的密码
    {
        vi(p->password);//显示数据
        p=p->next;//p后移
    }
	vi(p->password);//显示最后一个数据
    cout<<endl;
    return OK;
}
//在链表L中插入元素e
void ListInsert(LinkList &L,ElemType e1,ElemType e2)
{
	//!L表示链表为空
	if(!L)//链表插入 第一个结点 的操作与插入 非第一个结点 的操作有所不同
	{//插入第一个结点
		LinkList newbase=(LinkList)malloc(sizeof(LNode));
		newbase->name=e1;	//将新值赋给新结点的name域
		newbase->password=e2;//将新值赋给新结点的password域
		L=newbase;			//L指向新结点
		newbase->next=L;	//新结点的next域指向自己(只有一个结点)
	}
	else
	{//插入第2个及以后的结点
		LinkList newbase=(LinkList)malloc(sizeof(LNode));
		newbase->name=e1;		//将新值赋给新结点的name域
		newbase->password=e2;	//将新值赋给新结点的password域
		newbase->next=L->next;	//新结点next域指向第一个结点
		L->next=newbase;		//最后一个结点的next域指向新结点
		L=newbase;				//L指向最后一个结点(就是newbase)
	}
}
//创建大小为n的约瑟夫环
void CreateList_Ring(LinkList &L,int n)
{
	ElemType in;//要插入的元素
	int num=1;
    for(int i=0;i<n;i++)
	{
		cout<<"3--请输入玩家 "<<num<<" 的密码(正整数)"<<"(共"<<n<<"个): ";
		cin>>in;
		ListInsert(L,num,in);
		num++;
	}
}
//约瑟夫回环，返回最后剩下的一个元素
//L为环，n为环元素个数，计数到m时取出当前结点
void JosephRing(LinkList &L,int n,int m)
{
	LinkList q=L;//q为p的前驱
	LinkList p=L->next;//p为当前被数到的结点，从第一个开始
	for(int i=1;i<=n;i++)
	{	
		//一共删除n个元素
		for(int j=0;j<m-1;j++)//p和q后移m-1次
		{
			//p,q后移,指向应该删除的元素
			p=p->next;
			q=q->next;
		}
		//删除p指向的结点
		if(p==q)//如果只有一个结点,特殊处理
		{
			cout<<p->name<<ends;//输出被删除的玩家编号
			m=p->password;//更新m
			//删除p指向的结点
			free(p);
			L=NULL;
		}
		else//结点数不小于2,相同方法处理
		{
			cout<<p->name<<ends;//输出被删除的玩家编号
			m=p->password;//更新m
			//删除p指向的结点
			if(p==L) L=q;//若删除的结点恰好是尾结点,q会变成最后一个结点
			q->next=p->next;
			free(p);
			p=q->next;
		}
	}
}
//约瑟夫环
void show()
{
	int num=1;
	int n,m;
	cout<<"\n-----------------约瑟夫环------------------\n"<<endl;
	LinkList L;//建立尾指针
	InitList(L);//开始时表为空
	cout<<"1--请输入玩家个数(正整数): ";
	cin>>n;
	cout<<endl;
	cout<<"2--请输入初始报数上限值: ";
	cin>>m;
	cout<<endl;CreateList_Ring(L,n);//创建约瑟夫环
	cout<<"\n\n------------------开始-------------------\n"<<endl;
	cout<<"共有"<<n<<"个玩家,初始报数上限值为"<<m<<endl;
	PrintGamer(L,visit);//显示约瑟夫环中的玩家信息
	cout<<"\n------------------结果-------------------\n"<<endl;
	cout<<"玩家出列顺序:";
	JosephRing(L,n,m);cout<<endl;
	cout<<"\n------------------结束-------------------\n"<<endl;
}
int main()
{
	show();//约瑟夫环
    system("pause");//程序暂停
	return 0;
}
