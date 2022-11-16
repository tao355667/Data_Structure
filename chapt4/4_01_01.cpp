/*
4-1-1 串-堆分配存储表示

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

#define DestroyString ClearString // DestroyString()与ClearString()作用相同

typedef int Status;
//串的堆分配存储结构
struct HString
{
    char *ch;   //若是非空串，则按串长分配存储区；否则ch为NULL
    int length; //串长度
};
typedef HString String;
//初始化(产生空串)字符串S
void InitString(HString &S)
{
    S.length = 0; //串长为0
    S.ch = NULL;  //串指针指向空
}
//将S清为空串
void ClearString(HString &S)
{
    free(S.ch);    //释放S.ch所指的空间
    InitString(S); //初始化串S
}
//生成一个其值等于串常量chars的串T
void StrAssign(HString &T, char *chars)
{
    int i, j;
    if (T.ch)          // T指向某存储空间
        free(T.ch);    //释放T原有存储空间
    i = strlen(chars); //求chars的长度i
    if (!i)            // chars的长度为0
        InitString(T); //生成空串
    else
    {
        T.ch = (char *)malloc(i * sizeof(char)); //分配串存储空间
        if (!T.ch)                               //分配串存储空间失败
            exit(OVERFLOW);
        for (j = 0; j < i; j++) //分配串存储空间成功后,复制串chars[]到串T
            T.ch[j] = chars[j];
        T.length = i; //更新串T的长度
    }
}
//初始条件:串S存在
//操作结果:由串S复制得串T
void StrCopy(HString &T, HString &S)
{
    int i;
    if (T.ch)                                       //串T不空
        free(T.ch);                                 //释放串T原有存储空间
    T.ch = (char *)malloc(S.length * sizeof(char)); //分配串存储空间
    if (!T.ch)                                      //分配串存储空间失败
        exit(OVERFLOW);
    for (i = 0; i < S.length; i++) //从第一个字符到最后一个字符
        T.ch[i] = S.ch[i];         //逐一复制字符
    T.length = S.length;           //复制串长
}
//初始条件:串S存在.
//操作结果:若串S为空,则返回TRUE,否则返回FALSE
Status StrEmpty(HString S)
{
    if (S.ch == NULL && S.length == 0)
        return TRUE;
    else
        return FALSE;
}
//若串S>串T,则返回值>0;若串S=串T,则返回值=0;若串S<串T,则返回值<0;
int StrCompare(HString S, HString T)
{
    int i;
    for (i = 0; i < S.length && i < T.length; ++i)
        if (S.ch[i] != T.ch[i])
            return S.ch[i] - T.ch[i];
    return S.length - T.length;
}
//返回串S的元素个数,称为串的长度
int StrLength(HString S)
{
    return S.length;
}
//用串T返回由串S1和串S2连接而成的新串
void Concat(HString &T, HString S1, HString S2)
{
    int i;
    if (T.ch)                                       //串T不空
        free(T.ch);                                 //释放串T原有存储空间
    T.length = S1.length + S2.length;               //串T长度=串S1长度+串S2长度
    T.ch = (char *)malloc(T.length * sizeof(char)); //分配串T的存储空间
    if (!T.ch)
        exit(OVERFLOW);
    for (i = 0; i < S1.length; i++) //将串S1的字符逐一复制给串T
        T.ch[i] = S1.ch[i];
    for (i = 0; i < S2.length; i++) //将串S1的字符逐一复制给串T
        T.ch[S1.length + i] = S2.ch[i];
}
//用Sub返回串S的第pos个字符起长度为len的子串
//其中1<=pos<=StrLength(S)且0<=len<=StrLength(S)-pos+1
Status SubString(HString &Sub, HString S, int pos, int len)
{
    int i;
    if (pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1)
        return ERROR;
    if (Sub.ch)       //串Sub不空
        free(Sub.ch); //释放串Sub原有存储空间
    if (!len)         //空子串
        InitString(Sub);
    else
    {
        Sub.ch = (char *)malloc(len * sizeof(char)); //分配串存储空间
        if (!Sub.ch)                                 //分配串存储空间失败
            exit(OVERFLOW);
        for (i = 0; i <= len - 1; i++)
            Sub.ch[i] = S.ch[pos - 1 + i];
        Sub.length = len; //串Sub的长度
    }
    return OK;
}
// 1<=pos<=StrLength(S)+1
//在串S的第pos个字符之前插入串T
Status StrInsert(HString &S, int pos, HString T)
{
    int i;
    if (pos < 1 || pos > S.length + 1) // pos值不合法
        return ERROR;
    if (T.length)
    {
        //扩大S的存储空间
        S.ch = (char *)realloc(S.ch, (S.length + T.length) * sizeof(char));
        if (!S.ch) //存储空间分配失败
            return ERROR;
        for (i = S.length - 1; i >= pos - 1; --i) //为插入T而腾出位置
            S.ch[i + T.length] = S.ch[i];
        for (i = 0; i < T.length; i++) //插入T,S的下标从pos-1开始,共T.length个
            S.ch[pos - 1 + i] = T.ch[i];
        S.length += T.length;
    }
    return OK;
}
//从串S中删除第pos个字符起长度为len的字符chuan
Status StrDelete(HString &S, int pos, int len)
{
    int i;
    if (S.length - (pos - 1) < len) // pos和len值超出范围
        return ERROR;
    // for(i=pos-1;i<=pos-1+len-1;i++)
    for (i = pos - 1; i <= S.length - 1 - len; i++) //将待删除子串之后的字符逐一前移
        S.ch[i] = S.ch[i + len];
    S.length -= len;                                       //更新串S的长度
    S.ch = (char *)realloc(S.ch, S.length * sizeof(char)); //重新分配串S的存储空间(减少)
    return OK;
}
//输出字符串S
void StrPrint(HString S)
{
    int i;
    for (i = 0; i < S.length; i++)
        printf("%c", S.ch[i]);
    printf("\n");
}
// T为非空串.若主串S中第pos个字符之后存在与T相等的子串
//则返回第一个这样的子串在S中的位置;否则返回0
int Index(String S, String T, int pos)
{
    int n, m, i;
    String sub;      //用于接收长为len的字符串
    InitString(sub); //初始化sub
    if (pos > 0)
    {
        n = StrLength(S); //主串S的长度
        m = StrLength(T); //模式串T的长度
        i = pos;
        while (i <= n - m + 1) // i从串S的pos到倒数第m个
        {
            SubString(sub, S, i, m); //子串sub是从主串S的第i个字符起，长度为m的子串
            // printf("子串sub = ");StrPrint(sub);
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
Status Replace(String &S, String T, String V)
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
            // printf("插入后S = ");StrPrint(S);
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
    int i;
    char c, *p = "God bye!", *q = "God luck!";
    HString t, s, r;
    // HString类型必须初始化
    InitString(t);
    InitString(s);
    InitString(r);
    StrAssign(t, p); //将字符串p的内容转成HString类型,赋给t
    printf("串t为");
    StrPrint(t);
    printf("串长为%d,串空否?%d(1:是 0:否)\n", StrLength(t), StrEmpty(t));
    StrAssign(s, q);
    printf("串s为");
    StrPrint(s);

    i = StrCompare(s, t); //比较串s和串t的大小
    if (i < 0)
        c = '<';
    else if (i == 0)
        c = '=';
    else
        c = '>';
    printf("串s%c串t\n", c);
    Concat(r, t, s);
    printf("串t连接串s产生的串r为");
    StrPrint(r); //输出串r

    StrAssign(s, "oo");
    printf("串s为");
    StrPrint(s); //输出串s
    StrAssign(t, "o");
    printf("串t为");
    StrPrint(t); //输出串t

    Replace(r, t, s); //把串r中和串t相同的子串用串s代替
    printf("把串r中和串t相同的子串用串s代替后,串r为");
    StrPrint(r); //输出串r

    ClearString(s); //清空串s
    printf("串s清空后,串长为%d,空否?%d(1:空 0:否)\n", StrLength(s), StrEmpty(s));
    SubString(s, r, 6, 4); //生成的串s为从串r的第6个字符起的4个字符
    printf("串s为从串r的第6个字符起的4个字符,长度为%d,串s为", s.length);
    StrPrint(s); //输出串s
    StrCopy(t, r);
    printf("由串r复制得串t,串t为");
    StrPrint(t);        //输出串t
    StrInsert(t, 6, s); //在串t的第6个字符前插入串s
    printf("在串t的第6个字符前插入串s后,串t为");
    StrPrint(t);        //输出串t
    StrDelete(t, 1, 5); //在串t的第6个字符前插入串s
    printf("从串t的第1个字符起删除5个字符后,串t为");
    StrPrint(t); //输出串t
    printf("%d是从串t的第1个字符起,和串s相同的第1个子串的位置\n", Index(t, s, 1));
    printf("%d是从串t的第2个字符起,和串s相同的第1个子串的位置\n", Index(t, s, 2));
    DestroyString(t); //销毁操作同清空
}
int main()
{
    test(); //测试程序
    system("pause");
    return 0;
}