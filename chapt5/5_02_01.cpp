/*
5-2-0 矩阵的压缩存储
快速求稀疏矩阵的转置
输入:
3 2 4
1 1 1
2 1 2
3 1 3
3 2 4

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

#define MAX_SIZE 100
typedef int ElemType; // ElemType为int类型
typedef int Status;

struct Triple
{
    int i, j;   //行下标，列下标
    ElemType e; //非零元素值
};
struct TSMatrix
{
    Triple data[MAX_SIZE + 1]; //非零元三元组表，date[0]未使用
    int mu, nu, tu;            //矩阵的行数，列数，非零元个数
};
//比较c1和c2的大小关系
int comp(int c1, int c2)
{ // AddMatrix和MultSMatrix要用
    if (c1 < c2)
        return -1; // c1 < c2
    if (c1 == c2)
        return 0; // c1 == c2
    return 1;     // c1 > c2
}
//创建稀疏矩阵m
Status CreateMatrix(TSMatrix &M)
{
    int i;
    Triple T;
    Status k;
    printf("请输入矩阵的行数,列数,非零元素个数: ");
    scanf("%d %d %d", &M.mu, &M.nu, &M.tu);
    if (M.tu > MAX_SIZE)
        return ERROR;
    M.data[0].i = 0; //为以下比较顺序做准备
    for (i = 1; i <= M.tu; i++)
    {
        do
        {
            printf("请按行序顺序输入第%d个非零元素所在的行(1~%d),列(1~%d),元素值: ", i, M.mu, M.nu);
            scanf("%d %d %d", &T.i, &T.j, &T.e);
            k = 0;                                              //输入值的范围正确的标志
            if (T.i < 1 || T.i > M.mu || T.j < 1 || T.j > M.nu) //行或列超出范围
                k = 1;
            if (T.i < M.data[i - 1].i || T.i == M.data[i - 1].i && T.j <= M.data[i - 1].j)
                k = 1; //行或列的顺序有错
        } while (k);   //输入值的范围不正确则重新输入
        M.data[i] = T; //将输入正确的值赋给三元组结构体M的相应单元
    }
    return OK;
}
//求稀疏矩阵的和Q=M+N
Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q)
{
    int m = 1, n = 1, q = 0;
    if (M.mu != N.mu || M.nu != N.nu) // M,N两稀疏矩阵行或列数不同
        return ERROR;
    Q.mu = M.mu; //设置稀疏矩阵Q的行数和列数
    Q.nu = M.nu;
    while (m <= M.tu && n <= N.tu) //矩阵M和N的元素都未处理完
    {
        switch (comp(M.data[m].i, N.data[n].i)) //比较两当前元素的行值关系
        {
        case -1:
            Q.data[++q] = M.data[m++]; //矩阵M的行值小,将M的当前元素值赋给矩阵Q
            break;
        case 0: // M,N矩阵当前元素的行值相等,继续比较两当前元素的列值关系
            switch (comp(M.data[m].j, N.data[n].j))
            {
            case -1:
                Q.data[++q] = M.data[m++]; //矩阵M的列值小,将M的值赋给矩阵Q
                break;
            case 0: // M,N矩阵当前元素的行列值都相等,将两元素值求和并赋给矩阵Q
                Q.data[++q] = M.data[m++];
                Q.data[q].e += N.data[n++].e;
                if (Q.data[q].e == 0) //两元素之和为0,不存入稀疏矩阵
                    q--;
                break;
            case 1:
                Q.data[++q] = N.data[n++]; //矩阵N的列值小,将N的值赋给矩阵Q
            }
            break;
        case 1:
            Q.data[++q] = N.data[n++]; //矩阵N的行值小,将N的当前元素值赋给矩阵Q
        }                              //以下两个循环最多执行1个
    }
    while (m < M.mu) //矩阵N的元素已全部处理完毕,处理矩阵M的元素
        Q.data[++q] = M.data[m++];
    while (n <= N.tu) //矩阵M的元素已全部处理完毕,处理矩阵N的元素
        Q.data[++q] = N.data[n++];
    if (q > MAX_SIZE) //非零元素个数太多
        return ERROR;
    Q.tu = q; //矩阵Q的非零元素个数
    return OK;
}
//求稀疏矩阵M的转置矩阵T
void TransposeSMatrix(TSMatrix M, TSMatrix &T)
{
    int p, col, q = 1; // q指示转置矩阵T的当前元素,初值为1
    T.mu = M.nu;       //矩阵T的行数=矩阵M的列数
    T.nu = M.mu;       //矩阵M的行数=矩阵T的列数
    T.tu = M.tu;       //矩阵T的非零元素个数=矩阵M的非零元素个数
    if (T.tu)          //矩阵非空
    {
        for (col = 1; col <= M.nu; ++col) //从矩阵T的第一行到最后一行
        {
            for (p = 1; p <= M.tu; ++p) //对矩阵M的所有元素（三元组）
            {
                if (M.data[p].j == col) //该元素的列数=当前矩阵的行数
                {
                    T.data[q].i = M.data[p].j; //将矩阵M的值行列对调赋给T的当前元素
                    T.data[q].j = M.data[p].i;
                    T.data[q++].e = M.data[p].e; //转置矩阵T的当前元素指针+1
                }
            }
        }
    }
}
//求稀疏矩阵的乘积Q=M*N
Status MultSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q)
{
    int i, j, p, q;
    ElemType Qs;      //矩阵单元Q[i][j]的临时存放处
    TSMatrix T;       // N的转置矩阵
    if (M.nu != N.mu) //矩阵M和N无法相乘
        return ERROR;
    Q.mu = M.mu;                // Q的行数=M的行数
    Q.nu = M.nu;                // Q的列数=M的列数
    Q.tu = 0;                   // Q的非零元素个数的初值为0
    TransposeSMatrix(N, T);     // T是N的转置矩阵
    for (i = 1; i <= Q.mu; i++) //对M的每一行，求Q[i][]
    {
        q = 1;                      // q指向T的第一个非零元素
        for (j = 1; j <= T.mu; j++) //对于T的每一行（即N的每一列），求Q[i][j]
        {
            Qs = 0;                 //设置Q[i][j]的初值为0
            p = 1;                  // p指向M的第1个非零元素
            while (M.data[p].i < i) //使p指向矩阵M的第i行第1个非零元素
                p++;
            while (T.data[q].i < j) //使q指向矩阵T的第j行（即矩阵N的第j列）的第一个
                q++;
            while (p <= M.tu && q <= T.tu && M.data[p].i == i && T.data[q].i == j)
            { //[p]仍是M的第i行的非零元素且[q]仍是T的第j行(即N的第j列)的非零元素
                switch (comp(M.data[p].j, T.data[q].j))
                {        //比较M矩阵当前元素的列值和T矩阵当前元素的列值(即N矩阵当前元素的行值)
                case -1: // M矩阵当前元素的列值<T(N)矩阵当前元素的列(行)值,p向后移
                    p++;
                    break;
                case 0: // M矩阵当前元素的列值=T(N)矩阵当前元素的列(行)值,则两值相乘并累加到Qs,p,q均向后移
                    Qs += M.data[p++].e * T.data[q++].e;
                    break;
                case 1:
                    q++; // M矩阵当前元素的列值>T(N)矩阵当前元素的列(行)值，q向后移
                }
            }
            if (Qs)
            {
                if (++Q.tu > MAX_SIZE)
                    return ERROR;
                // Q.data
            }
        }
    }
    return OK;
}
//第二个求矩阵乘积的函数,求稀疏矩阵的乘积Q=M*N
Status MultSMatrix1(TSMatrix M, TSMatrix N, TSMatrix &Q)
{

    return OK;
}
//三元组稀疏矩阵的基本操作
//销毁稀疏矩阵M
void DestroySMatrix(TSMatrix &M)
{
    M.mu = M.nu = M.tu = 0;
}
//按矩阵形式输出M
void PrintSMatrix(TSMatrix M)
{
    int i, j, k = 1;            //非零元计数器，初值为1
    Triple *p = M.data + 1;     // p指向M第一个非零元素
    for (i = 1; i <= M.mu; i++) //从第一行到最后一行
    {
        for (j = 1; j <= M.nu; j++) //从第一列到最后一列
        {
            if (k <= M.tu && p->i == i && p->j == j)
            {
                printf("%3d", (p++)->e); //输出p所指的元素的值，p指向下一个元素
                k++;                     //计数器+1
            }
            else                  // p所指元素不是当前所在的处理元素
                printf("%3d", 0); //输出0
        }
        printf("\n");
    }
}
//由稀疏矩阵M复制的都T
void CopySMatrix(TSMatrix M, TSMatrix &T)
{
    T = M;
}
//求稀疏矩阵的差Q=M-N
Status SubtSMatrix(TSMatrix M, TSMatrix N, TSMatrix &Q)
{
    int i;
    if (M.mu != N.mu || M.nu != N.nu) // M,N两稀疏矩阵行数或列数不同
        return ERROR;
    for (i = 1; i <= N.tu; i++) //对于N的每一元素,其值乘以-1
        N.data[i].e *= -1;
    AddSMatrix(M, N, Q); // Q=M+(-N)
    return OK;
}
//快速求稀疏矩阵M的转置矩阵T
void FastTransposeSMatrix(TSMatrix M, TSMatrix &T)
{
    int p, q, col, *num, *cpot;
    num = (int *)malloc((M.nu + 1) * sizeof(int));  //存M每列(T每行)非零元素个数([0]不用)
    cpot = (int *)malloc((M.nu + 1) * sizeof(int)); //存T每行下一个非零元素的序号(在M中)([0]不用),初值为每行第一个非零元序号
    T.mu = M.nu;                                    // T的行数=M的列数
    T.nu = M.mu;                                    // T的列数=M的行数
    T.tu = M.tu;                                    // T的非零元素=M的非零元素
    if (T.tu)                                       // T是非零矩阵
    {
        // num计数器初值为0
        for (col = 1; col <= M.nu; ++col) //从M的第一列到最后一列
            num[col] = 0;                 //计数器初值为0
        for (p = 1; p <= M.tu; ++p)       //对于M的每一个非零元素
            ++num[M.data[p].j];           //根据他所在的列进行统计
        //至此num[]统计完成
        cpot[1] = 1;                                  // T的第1行的第1个非零元在T.data中的序号为1
        for (col = 2; col <= M.nu; ++col)             //从M(T)的第2列(行)到最后一列(行)
            cpot[col] = cpot[col - 1] + num[col - 1]; //求T的第col行第i个非零元在T.data中的序号
        for (p = 1; p <= M.tu; ++p)                   //对于M的每一个非零元素
        {
            col = M.data[p].j;         //将其在M中的列数赋给col
            q = cpot[col];             // q指示M当前的元素在T中的序号
            T.data[q].i = M.data[p].j; //将M当前的元素转置赋给T
            T.data[q].j = M.data[p].i;
            T.data[q].e = M.data[p].e;
            ++cpot[col];
        }
    }
    //释放num和cpot所指向的动态存储空间
    free(num);
    free(cpot);
}
void test()
{
    TSMatrix A, B, C;
    printf("创建矩阵A: ");
    CreateMatrix(A); //创建矩阵A
    PrintSMatrix(A); //输出矩阵A

    FastTransposeSMatrix(A, B); // B是A的转置矩阵
    printf("矩阵B(A的快速转置):\n");
    PrintSMatrix(B); //输出矩阵B
}
int main()
{
    test(); //测试程序
    system("pause");
    return 0;
}
