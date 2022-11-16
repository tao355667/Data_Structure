/*
5-1-0 数组的顺序表示和实现
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

struct Array
{
    ElemType *base; //数组元素基址,由InitArray分配
    int dim;        //数组维度
    int *bounds;    //数组维界基址,由InitArray分配
    int *constants; //数组映像函数常量基址,由InitArray分配
};
//若维数dim和各维长度合法,则构造相应的数组A,并返回OK
Status InitArray(Array &A, int dim, ...)
{
    int elemtotal = 1, i;               // elemtotal是数组元素总数,初值为1(累乘器)
    va_list ap;                         //变长参数表类型,在stdarg.h中
    if (dim < 1 || dim > MAX_ARRAY_DIM) //数组维数超过范围
        return ERROR;
    A.dim = dim;                                 //数组维数
    A.bounds = (int *)malloc(dim * sizeof(int)); //动态分配数组维界地址
    if (!A.bounds)
        exit(OVERFLOW);
    va_start(ap, dim); //变长参数"..."从形参dim之后开始
    for (i = 0; i < dim; ++i)
    {
        A.bounds[i] = va_arg(ap, int);
        if (A.bounds[i] < 0)
            return UNDERFLOW;     //在math.h中定义为4
        elemtotal *= A.bounds[i]; //数组元素总数=各维长度之积
    }
    va_end(ap); //结束提取变长参数

    A.base = (ElemType *)malloc(elemtotal * sizeof(ElemType)); //动态分配数组存储空间
    if (!A.base)
        exit(OVERFLOW);
    A.constants = (int *)malloc(dim * sizeof(int)); //动态分配数组偏移量基址
    if (!A.constants)
        exit(OVERFLOW);
    A.constants[dim - 1] = 1; //最后一维偏移量为1
    for (i = dim - 2; i >= 0; --i)
        A.constants[i] = A.bounds[i + 1] * A.constants[i + 1]; //每一维偏移量
    return OK;
}
//销毁数组A
void Destroyrray(Array &A)
{
    //释放空间
    if (A.base)
        free(A.base);
    if (A.bounds)
        free(A.bounds);
    if (A.constants)
        free(A.constants);
    //指针为空
    A.base = A.bounds = A.constants = NULL;
    //变量为0
    A.dim = 0;
}
//若ap指示的各下标值合法，则求出该元素在A中的相对地址off
Status Locate(Array A, va_list ap, int &off)
{ //被Value(),Assign()调用
    int i, ind;
    off = 0;
    for (i = 0; i < A.dim; i++)
    {
        ind = va_arg(ap, int);             //逐一读取各维下标值
        if (ind < 0 || ind >= A.bounds[i]) //各维下标值不合法
            return OVERFLOW;
        off += A.constants[i] * ind; //相对地址=各维下标值*本维的偏移量之和
    }
    return OK;
}
//“...”依次为各维下标值，若各下标合法，则e被赋值为A的相应元素值
Status Value(ElemType &e, Array A, ...)
{
    va_list ap; //变长参数表类型，在stdarg.h中
    int off;
    va_start(ap, A);                    //变长参数“...”从A之后开始
    if (Locate(A, ap, off) == OVERFLOW) // 注意此时调用了Locate()
        return ERROR;                   // Locate函数返回错误值
    e = *(A.base + off);
    return OK;
}
//“...”依次为各维下标值，若各下标合法，则将e的值赋给A的指定元素
Status Assign(Array A, ElemType e, ...)
{
    va_list ap; //变长参数表类型，在stdarg.h中
    int off;
    va_start(ap, e);                    //变长参数“...”从e之后开始
    if (Locate(A, ap, off) == OVERFLOW) //注意此时调用了Locate()
        return ERROR;                   // Locate函数返回错误值
    *(A.base + off) = e;
    return OK;
}
//测试程序
void test()
{
    Array A;
    int i, j, k, dim = 3, bound1 = 3, bound2 = 4, bound3 = 2; // A[3][4][2]数组
    ElemType e;
    InitArray(A, dim, bound1, bound2, bound3);
    printf("A.bounds=");
    for (i = 0; i < dim; i++) //顺序输出A.bounds
        printf("%d ", *(A.bounds + i));
    printf("\nA.constants=");
    for (i = 0; i < dim; i++) //顺序输出A.constants
        printf("%d ", *(A.constants + i));
    printf("\n%d页%d行%d列矩阵元素如下:\n", bound1, bound2, bound3);
    for (i = 0; i < bound1; i++)
    {
        for (j = 0; j < bound2; j++)
        {
            for (k = 0; k < bound3; k++)
            {
                Assign(A, i * 100 + j * 10 + k, i, j, k);
                Value(e, A, i, j, k);
                printf("A[%d][%d][%d]=%2d ", i, j, k, e);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("A.base=\n");
    for (i = 0; i < bound1 * bound2 * bound3; i++) //顺序输出A.base
    {
        printf("%4d", *(A.base + i));
        if (i % (bound2 * bound3) == bound2 * bound3 - 1) //输出的一行是一页，共3页s
            printf("\n");
    }
    printf("A,dim=%d\n", A.dim);
    Destroyrray(A);
}
int main()
{
    test(); //测试程序
    system("pause");
    return 0;
}