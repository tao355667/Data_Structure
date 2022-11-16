/*
4-1-0 串-定长顺序存储表示
输入:
ABCD
123456
3,7
4,4

*/
#include <cstdlib>
#include <cstdio>
#include <cstring> //strlen()

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAX_STR_LEN 40            //用户可在255内定义最大串长
#define DestroyString ClearString // DestroyString()与ClearString()作用相同
#define InitString ClearString    // InitString()与ClearString()作用相同

typedef unsigned char SString[MAX_STR_LEN + 1]; // 0号单元存放串的长度
typedef int Status;

//生成一个其值等于char的串T
Status StrAssign(SString T, char *chars)
{
    int i;
    if (strlen(chars) > MAX_STR_LEN)
        return ERROR;
    else
    {
        T[0] = strlen(chars);       // 0号单元存放串的长度
        for (i = 1; i <= T[0]; i++) //从1号单元起,赋值串的内容
            T[i] = *(chars + i - 1);
        return OK;
    }
}
//由串S复制得串T
void StrCopy(SString T, SString S)
{
    int i;
    for (i = 0; i <= S[0]; i++)
    {
        T[i] = S[i];
    }
}
//若S为空串,则返回TRUE,否则返回FALSE
Status StrEmpty(SString S)
{
    if (S[0] == 0)
        return TRUE;
    else
        return FALSE;
}
//初始条件:串S和串T存在
//操作结果:若S>T,则返回值>0;若S=T,则返回值=0;若S<T,则返回值<0
int StrCompare(SString S, SString T)
{
    int i;
    for (i = 1; i <= S[0] && i <= T[0]; ++i) //先比较字符
        if (S[i] != T[i])
            return S[i] - T[i];
    return S[0] - T[0]; //若字符都相同，则比较长短
}
//返回串S的元素个数
int StrLength(SString S)
{
    return S[0];
}
//初始条件:串S存在
//操作结果:将S清为空串
void ClearString(SString S)
{
    S[0] = 0; //令串长为0
}
//用T返回S1和S2连接而成的新串.
//若未截断,则返回TRUE,否则返回FALSE
Status Concat(SString T, SString S1, SString S2)
{
    int i;
    if (S1[0] + S2[0] <= MAX_STR_LEN) //未截断
    {
        for (i = 1; i <= S1[0]; i++) // S1先进T
            T[i] = S1[i];
        for (i = 1; i <= S2[0]; i++)
            T[S1[0] + i] = S2[i];
        T[0] = S1[0] + S2[0];
        return TRUE;
    }
    else //截断S2(S1长度超过T会出问题)
    {
        for (i = 1; i <= S1[0]; i++) // S1先进T
            T[i] = S1[i];
        for (i = 1; i <= MAX_STR_LEN - S1[0]; i++) //到串长为止
            T[S1[0] + i] = S2[i];
        T[0] = MAX_STR_LEN;
        return FALSE;
    }
}
//用sub返回串S的自pos个字符起长度为len的子串
int SubString(SString Sub, SString S, int pos, int len)
{
    int i, j;
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1) // pos和len值超出范围
        return ERROR;
    for (i = 1; i <= len; i++)
        Sub[i] = S[pos + i - 1];
    Sub[0] = len;
    return OK;
}
//返回子串T在主串S中第pos的字符之后的位置.若不存在,则函数值为0
//其中,T非空,1<=pos<=StrLength(S)
int Index1(SString S, SString T, int pos)
{
    int i, j;                    //指示主串S和子串T的当前比较字符
    if (1 <= pos && pos <= S[0]) // pos的范围合适
    {
        i = pos; //从主串S的第pos个字符开始和子串T的第一个字符比较
        j = 1;
        while (i <= S[0] && j <= T[0])
        {
            if (S[i] == T[j]) //当前两字符相等
            {
                ++i; //继续计较后继字符
                ++j;
            }
            else //当前两字符不相等
            {
                i = i - j + 2; //两指针后退重新开始匹配
                j = 1;
            }
        }
        if (j > T[0]) //主串S中存在子串T
            return i - T[0];
        else //主串中不存在子串T
            return 0;
    }
    else
    {
        return 0; // pos范围不合适
    }
}
//初始条件:串S和T存在,1<=pos<=StrLength(S)+1
//操作结果:在串S和第pos个字符之前插入串T.完全插入返回TRUE,部分插入返回FALSE
Status StrInsert(SString S, int pos, SString T)
{
    int i;
    if (pos < 1 || pos > S[0] + 1) // pos超出范围
        return ERROR;
    if (S[0] + T[0] <= MAX_STR_LEN) //完全插入
    {
        for (i = S[0]; i >= pos; i--) // pos及之后的字符后移T[0]位,为串T腾空间
            S[i + T[0]] = S[i];
        for (i = pos; i < pos + T[0]; i++) //在刚才S腾开的位置中插入串T
            S[i] = T[i - pos + 1];
        S[0] += T[0]; //串S的长度为串的最大长度
        return TRUE;  //完全插入的标记
    }
    else //部分插入
    {
        for (i = MAX_STR_LEN; i >= pos + T[0]; i--)            //移动串S中位于pos之后的字符
            S[i] = S[i - T[0]];                                //串S向后移串T的长度,为插入串T准备空间
        for (i = pos; i < pos + T[0] && i <= MAX_STR_LEN; i++) //在串S中插入串T
            S[i] = T[i - pos + 1];
        S[0] = MAX_STR_LEN; //串S的长度为串的最大长度
        return FALSE;       //部分插入的标记
    }
}
//初始条件:串S存在,1<=pos<=StrLength(S)-len+1
//操作结果:从串S中删除自第pos个字符起长度为len的子串
Status StrDelete(SString S, int pos, int len)
{
    int i; //计数器
    // pos>S[0]-len+1: 数组中要有足够的长度用于删除
    if (pos < 1 || pos > S[0] - len + 1 || len < 0) // pos和len的值超出范围
        return ERROR;
    for (i = pos + len; i <= S[0]; i++) //对于删除的子串之后的所有字符
        S[i - len] = S[i];              //将第i个元素前移len个单位
    S[0] -= len;                        //更新串S的长度
    return OK;                          //删除成功
}
//输出字符串S
void StrPrint(SString S)
{
    int i;
    for (i = 1; i <= S[0]; i++)
        printf("%c", S[i]);
    printf("\n");
}
// T为非空串.若主串S中第pos个字符之后存在与T相等的子串
//则返回第一个这样的子串在S中的位置;否则返回0
int Index(SString S, SString T, int pos)
{
    int n, m, i;
    SString sub;     //用于接收长为len的字符串
    InitString(sub); //初始化sub
    if (pos > 0)
    {
        n = StrLength(S); //主串S的长度
        m = StrLength(T); //模式串T的长度
        i = pos;
        while (i <= n - m + 1) // i从串S的pos到倒数第m个
        {
            SubString(sub, S, i, m); //子串sub是从主串S的第i个字符起，长度为m的子串
            printf("子串sub = ");
            StrPrint(sub);
            if (StrCompare(sub, T) != 0) //子串sub不等于模式串T
                ++i;                     //继续向后比较
            else
                return i; //返回模式串T的第一个字符在主串S中的位置
        }
    }
    return 0;
}
//初始条件:串S,T和V存在,串T是非空串
//操作结果:用串V替换主串S中出现的所有与串T相等的不重叠的子串
Status Replace(SString S, SString T, SString V)
{
    int i = 1;
    Status k;
    if (StrEmpty(T)) // T是空串
        return ERROR;
    while (i)
    {
        i = Index(S, T, i); //从上个i开始找到的子串T的位置
        if (i)
        {
            StrDelete(S, i, StrLength(T));
            k = StrInsert(S, i, V); //在原串T的位置插入串V
            printf("插入后S = ");
            StrPrint(S);
            if (!k)
                return ERROR;
            i += StrLength(V); //在插入的串v后面继续查找串T
        }
    }
    return OK;
}
//测试程序
void test()
{
    int i, j;
    Status k;
    char s, c[MAX_STR_LEN + 1]; // c中包括串结束符
    SString t, s1, s2;
    printf("请输入串s1: ");
    gets(c);              //由键盘输入字符串给c
    k = StrAssign(s1, c); //将字符串c转为SString类型,存入s1
    if (!k)               //本例中由于c的长度所限,串长超过MAX_STR_LEN的现象不会发生
    {
        printf("串长超过MAX_STR_LEN(=%d)\n", MAX_STR_LEN);
        exit(OVERFLOW);
    }
    printf("串长为%d,串空否?%d(1:是 0:否)\n", StrLength(s1), StrEmpty(s1));
    StrCopy(s2, s1); //复制串s1生成串s2
    printf("复制s1生成的串为");
    StrPrint(s2); //输出串s2
    printf("请输入串s2: ");
    gets(c);                //由键盘输入字符串给c
    StrAssign(s2, c);       //将字符串c转化为类型,存入s1,可不要返回值
    i = StrCompare(s1, s2); //比较串s1和串s2
    if (i < 0)
        s = '<';
    else if (i == 0)
        s = '=';
    else
        s = '>';
    printf("串s1%c串s2\n", s);
    k = Concat(t, s1, s2); //用s1和s2连接得到新串t
    printf("串s1连接串s2得到的串t为");
    StrPrint(t); //输出串t
    if (k == FALSE)
        printf("串t有截断\n");
    ClearString(s1); //清空串s1
    printf("清为空串后,串s1为");
    StrPrint(s1); //输出串s1
    printf("串长为%d,串空否?%d(1:是 0:否)\n", StrLength(s1), StrEmpty(s1));
    printf("求串t的子串,请输入子串的起始位置,子串长度:");
    scanf("%d,%d", &i, &j);
    k = SubString(s2, t, i, j); //将字符串c转为SString类型,存入s1
    if (k)                      //串s2存在
    {
        printf("子串s2为");
        StrPrint(s2); //输出串s2
    }
    printf("从串t的第pos个字符起,删除len个字符,请输入pos,len:");
    scanf("%d,%d", &i, &j);
    StrDelete(t, i, j); //将串t的第i个字符起的j个字符删除
    printf("删除后的串t为");
    StrPrint(t);           //输出串t
    i = StrLength(s2) / 2; // i为串s2长度的一半取整
    StrInsert(s2, i, t);   //在串s2的第i个字符之前插入串t
    printf("在串s2的第%d个字符之前插入串t后,串s2为", i);
    StrPrint(s2);         //输出串s2
    i = Index1(s2, t, 1); //从串s2和第i个字符起查找串t
    printf("s2的第%d个字符起和t第一次匹配\n", i);
    i = Index(s2, t, 1); //从串s2的第一个字符起查找串t(另一种方法)
    printf("s2的第%d个字符起和t第一次匹配\n", i);
    SubString(t, s2, 1, 1); //串s1为串s2的第一个字符
    printf("串t为");
    StrPrint(t); //输出串t
    printf("串s1为");
    Concat(s1, t, t); //串s1为两个串t
    StrPrint(s1);
    k = Replace(s2, t, s1); //将串s2中的所有不重叠串t用串s1替换
    if (k)                  //替换成功
    {
        printf("用串s1取代串s2中和串t相同的不重叠串后,串s2为");
        StrPrint(s2); //输出串s2
    }
    DestroyString(s2); //销毁操作与清空操作作用相同
}
int main()
{
    test(); //测试程序
    system("pause");
    return 0;
}