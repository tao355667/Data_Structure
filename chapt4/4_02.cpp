/*
4-2 串的模式匹配算法-KMP算法
关键词：字符串匹配 串
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
//---------------以下是字符串匹配算法---------------------------------------
//求模式串T的next函数值并存入数组next
void get_next(SString T, int next[])
{
    int i = 1, j = 0;
    // next数组[0]不用
    next[1] = 0; // T的第一个字符与主串“失配”时，主串的下一字符与T的第一个字符比较
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j]) //初态或两字符相等
        {
            //各加1,继续向后比较
            ++i;
            ++j;
            next[i] = j; //主串和T在第i个字符不匹配时,前j-1个字符是匹配的,只需与第j个字符比较
        }
        else             //两字符不等
            j = next[j]; // j减小到前面的字符相等之处
    }
}
//求模式串T的next函数修正值并存入数组nextval
void get_nextval(SString T, int nextval[])
{
    int i = 1, j = 0;
    nextval[1] = 0; // T的第一个字符与主串“失配”，主串的下一个字符与T的第一个字符比较
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        {
            ++i;
            ++j;
            if (T[i] != T[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        }
        else
            j = nextval[j]; // j减小到前面字符相等之处
    }
}
//利用模式串T的next数组求T在主串S中第pos个字符之后的位置的KMP算法
int Index_KMP(SString S, SString T, int pos, int next[])
{
    int i = pos, j = 1;            //初始位置
    while (i <= S[0] && j <= T[0]) // i和j分别都未超出主串S和模式串T的范围
    {
        if (j == 0 || S[i] == T[j])
        {
            ++i;
            ++j;
        }
        else
            j = next[j];
    }
    if (j > T[0]) //匹配成功
        return i - T[0];
    else
        return 0;
}
//测试程序
void test()
{
    int i, *p;
    SString s1, s2;
    StrAssign(s1, "saabasaaddxabacabab"); //由"aaabaaaab"生成主串s1
    printf("主串为");
    StrPrint(s1);
    StrAssign(s2, "ababaaababaa"); //"aaaab"
    printf("子串为");
    StrPrint(s2);
    p = (int *)malloc((StrLength(s2) + 1) * sizeof(int)); //生成s2的next数组,[0]不用
    get_next(s2, p);
    printf("子串的next数组为");
    for (i = 1; i <= StrLength(s2); i++)
        printf("%d ", *(p + i));
    printf("\n");
    i = Index_KMP(s1, s2, 1, p);
    if (i)
        printf("主串和子串在第%d个字符处首次匹配\n", i);
    else
        printf("主串和子串匹配不成功\n");
    get_nextval(s2, p);
    printf("子串的nextval数组为");
    for (i = 1; i <= StrLength(s2); i++)
        printf("%d ", *(p + i));
    printf("\n");
    printf("主串和子串在第%d个字符处首次匹配\n", Index_KMP(s1, s2, 1, p));
}
int main()
{
    test(); //测试程序
    system("pause");
    return 0;
}