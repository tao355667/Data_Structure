/*
3-2-4 栈的应用-（中缀）表达式求值-原始
示例输入：
3*(7-2)
示例输出：
15
*/

#include<cstdlib>
#include<cstdio>

#define TRUE            1
#define FALSE           0
#define OK              1
#define ERROR           0
#define INFEASIBLE      -1
#define OVERFLOW        -2

#define STACK_INIT_SIZE 10          //存储空间初始分配量
#define STACK_INCREMENT 2           //存储空间分配增量


//SElemType为字符型
typedef char SElemType;         
typedef int Status;

//-----------以下是栈-------------------------------------------------------
struct SqStack  //栈结构体
{
    SElemType *base;
    SElemType *top;
    int stacksize;
};
//构造一个空栈
void InitStack(SqStack &S)
{
    if(!(S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType))))
        exit(OVERFLOW);//动态分配存储空间失败，则退出
    S.top=S.base;//栈顶指向栈底部
    S.stacksize=STACK_INIT_SIZE;//栈的初始大小为STACK_INIT_SIZE
}
//销毁栈S，S不再存在
void DestroyStack(SqStack &S)
{
    free(S.base);       //释放栈空间
    S.top=S.base=NULL;  //栈顶、栈底的指针为空
    S.stacksize=0;      //栈大小为0
}
//把栈S置为空栈
void ClaerStack(SqStack &S)
{
    S.top=S.base;//栈顶指向栈底
}
//若S为空栈，则返回TRUE，否则返回FALSE
Status StackEmpty(SqStack S)
{
    if(S.top==S.base)//空栈条件
        return TRUE;
    else
        return FALSE;
}
//返回栈S的元素个数，即栈的长度
int StackLength(SqStack S)
{
    return S.top-S.base;//注意指针的加减法运算规则
}
//若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR
Status GetTop(SqStack S,SElemType &e)
{
    if(S.top>S.base)//栈不为空
    {
        e=*(S.top-1);//栈顶指向的是空，减一格才到元素
        return OK;
    }
    else
        return ERROR;
}
//插入元素e为栈S新的栈顶元素
void Push(SqStack &S,SElemType e)
{
    if(S.top-S.base==S.stacksize)//栈满
    {
        S.base=(SElemType*)realloc(S.base,(S.stacksize+STACK_INCREMENT)*sizeof(SElemType));
        if(!S.base)
            exit(OVERFLOW);
        S.top=S.base+S.stacksize;//使栈顶指针指向新的栈顶
        S.stacksize+=STACK_INCREMENT;
    }
    *(S.top)++=e;//将e入栈,成为新的栈顶元素,栈顶指针上移一个单元
}
//若栈S不空,则删除S的栈顶元素,用e返回其值,并返回OK,否则返回ERROR
Status Pop(SqStack &S,SElemType &e)
{
    if(S.top==S.base)//栈空
        return ERROR;
    e=*--S.top;//将栈顶元素赋给e,栈顶指针下移一格存储单元
    return OK;
}
void vi(SElemType e)
{
    //cout<<e<<" ";
}
//从栈底到栈顶依次对栈S中每个元素调用函数visit()
void StackTraverse(SqStack S,void(*visit)(SElemType))
{
    while (S.top>S.base)//S.base指向栈元素
    {
        visit(*S.base++);//对栈元素调用visit()
    }
    printf("\n");//栈顶指针上移一个存储单元
}
//-----------以下是表达式求值函数-------------------------------------------------------
//返回t1和t2的优先级。t1：栈顶   t2：接收
char Precede(SElemType t1,SElemType t2)
{
    char f;
    switch(t2)
    {
        case '+'://+-优先级相同
        case '-':
            if(t1=='(' || t1=='\n')
                f='<';//t1<t2
            else
                f='>';//t1>t2
            break;
        case '*'://*/优先级相同
        case '/':
            if(t1=='*' || t1=='/' || t1==')')
                f='>';//t1>t2
            else
                f='<';//t1<t2
            break;
        case '(':
            if(t1==')')
            {
                printf("括号不匹配\n");
                exit(OVERFLOW);
            }
            else
                f='<';//t1<t2
            break;
        case ')':
            switch(t1)
            {
                case '(':
                    f='=';//t1=t2
                    break;
                case '\n':
                    printf("缺乏左括号\n");
                    exit(OVERFLOW);
                default:
                    f='>';//t1> t2
            }
            break;
        case '\n':
            switch(t1)
            {
                case '\n':
                    f='=';//t1=t2
                    break;
                case '(':
                    printf("缺乏右括号\n");
                    exit(OVERFLOW);
                default:
                    f='>';//t1>t2
            }
    }
    return f;
}
//判断c是否为7种运算符之一
Status In(SElemType c)
{
    switch(c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
        case '\n':return TRUE;
        default:return FALSE;
    }
}
//做四则运算 a theta b，返回运算结果
SElemType Operate(SElemType a,SElemType theta,SElemType b)
{
    switch(theta)
    {
        case '+':return a+b;
        case '-':return a-b;
        case '*':return a*b;
    }
    return a/b;
}

//算术表达式求值的算符优先算法。OPTR和OPND分别为运算符栈和运算数栈。
SElemType EvaluateExpression()
{
    SqStack OPTR,OPND;//符号栈，数据栈
    SElemType a,b,c,d,x;//存储信息的变量，d貌似没用
    InitStack(OPTR);//栈初始化
    InitStack(OPND);//栈初始化
    Push(OPTR,'\n');//开始时将结束符号压入符号栈
    c=getchar();//接收第一个字符
    GetTop(OPTR,x);//将运算符OPTR的栈顶元素'\n'赋给x
    while(c!='\n' || x!='\n')//结束条件：接收到的字符c和OPTR栈顶元素x都是结束符'\n'
    {
        if(In(c))//接收到的字符是7运算符之一
        {
            switch(Precede(x,c))//判断栈顶元素和接收到元素的优先级
            {
                case '<'://栈顶<接收，入栈
                    Push(OPTR,c);//将接收到的元素入栈
                    c=getchar();//接收下一个元素
                    break;
                case '='://消除括号，注意右括号不进栈
                    Pop(OPTR,x);//将左括号弹出栈
                    c=getchar();//接收下一个元素
                    break;
                case '>'://栈顶>接收，进行一次计算，结果进栈
                    Pop(OPTR,x);//符号出栈
                    Pop(OPND,b);//第二个操作数出栈
                    Pop(OPND,a);//第一个操作数出栈
                    Push(OPND,Operate(a,x,b));//将计算结果压进栈
                    //符号栈顶元素会变
                    //不用接收下一个c，下次还是用现在的c与栈顶元素比较
            }
        }
        else if(c>='0' && c<='9')//c是操作数
        {
            Push(OPND,c-48);//操作数进栈
            c=getchar();//接收下一个元素
        }
        else//c是非法字符
        {
            printf("出现非法字符\n");
            exit(OVERFLOW);
        }
        GetTop(OPTR,x);//将栈顶符号赋给x，保证下一次接收数据正常（将元素弹出时也会将值赋给x）
    }
    Pop(OPND,x);//计算完成，将数据栈最后结果弹出
    if(!StackEmpty(OPND))//正常情况下栈应为空
    {
        printf("表达式不正确\n");
        exit(OVERFLOW);
    }
    return x;
}
int main()
{
    printf("请输入算数表达式（输入的值要在0~9之间、");
    printf("中间运算值和输出结果在-128~127之间）\n");
    printf("%d\n",EvaluateExpression());

    system("pause");
    return 0;
}