/*
实习07_哈希表的创建与查找
1
23 5 17 12 26 31 13 4 6 -1
2
4
3
23
3
17
3
26
3
31
3
99

*/
#include <cstdio>
#include <cstring>
#include <cstdlib>
//元素结构体
typedef struct Elem
{
    int key;          //元素的值
    int compareTimes; //查找到该元素需要的比较次数
    int flag;         //用来标识该位置是否已经有存有别的数据
} Elem;
//哈希表结构体
typedef struct HashList
{
    Elem *base;
    int length;
} HashList;
int Nil = -1; // Elem中数据为空的标志
//除留取余法计算插入地址
int Hash(int k);
int HI(int Hk);
//初始化哈希表
void InitHashList(HashList &HL);
//建立哈希表
void CreateHashList(HashList &HL);
//显示哈希表
void PrintHashList(HashList HL);
//查找,返回查找到元素a的下标
int IndexHashList(HashList HL, int a);
//计算平均查找长度
void CalcuASL(HashList H);
// MyScanf只接收整数
int MyScanf()
{
    int a;
    while (1)
    {
        if (scanf("%d", &a))
        {
            fflush(stdin);
            return a;
        }
        else
        {
            fflush(stdin);
            printf("请输入正确的指令(0-4)！");
        }
    }
}
void start()
{
    printf("------------------------哈希表的建立和查找----------------------");
    printf("\n========================\n");
    printf("1. 创建哈希表\n");
    printf("2. 显示哈希表\n");
    printf("3. 查找\n");
    printf("4. 计算哈希表平均查找长度：\n");
    printf("0. 退出\n");
    printf("\n========================\n");
    printf("\nSELECT(0-4):");
}
int main()
{
    HashList H;
    InitHashList(H); //初始化哈希表
    start();         //显示菜单
    int menu;        //菜单选项
    menu = MyScanf();
    while (menu)
    {
        switch (menu)
        {
        case 1:
            CreateHashList(H); //创建哈希表
            break;
        case 2:
            PrintHashList(H);
            break;
        case 3:
            int searchNum;
            printf("请输入你要查找的元素值：");
            scanf("%d", &searchNum);
            IndexHashList(H, searchNum);
            break;
        case 4:
            CalcuASL(H);
        }
        printf("\nSELECT(0-4):");
        menu = MyScanf();
    }
    return 0;
}
void InitHashList(HashList &HL)
{
    int i;
    //初始化哈希表
    HL.length = 13;
    HL.base = (Elem *)malloc(HL.length * sizeof(Elem));
    for (i = 0; i < HL.length; i++)
    { //元素值为空
        HL.base[i].key = Nil;
        HL.base[i].flag = 0;
        HL.base[i].compareTimes = 0;
    }
}
//除留取余法
int Hash(int k)
{
    return (k % 13);
}
//建立哈希表
void CreateHashList(HashList &HL)
{
    int num; //存储入表元素
    printf("请输入要入表的元素（输入-1表示结束）：");
    scanf("%d", &num); //接收要入表的元素
    while (num != -1)
    {
        //将元素插入哈希表
        int di = 1;             //线性探测
        int h = Hash(num);      //计算要插入的地址
        while (HL.base[h].flag) //要插入的地址有数据
        {
            ++HL.base[h].compareTimes; //该地址的探测次数+1
            h = Hash(num + di++);      //计算新地址
            if (di == HL.length)       //哈希表被占满了
            {
                printf("哈希表满！");
                return;
            }
        }
        ++HL.base[h].compareTimes; //该地址的探测次数+1
        HL.base[h].key = num;      //将元素存入哈希表
        HL.base[h].flag = 1;       //该地址有数据
        scanf("%d", &num);         //接收要入表的元素
    }
    printf("哈希表创建成功！\n");
}
//显示哈希表
void PrintHashList(HashList HL)
{
    int i;
    printf("\n%16s", "散列地址");
    for (i = 0; i < HL.length; i++)
        printf("%6d", i);
    printf("\n", i);
    printf("%16s", "关键字");
    for (i = 0; i < HL.length; i++)
    {
        if (HL.base[i].key != Nil)
            printf("%6d", HL.base[i].key);
        else
            printf("%6s", " ");
    }

    printf("\n", i);
    printf("%16s", "探测次数");
    for (i = 0; i < HL.length; i++)
    {
        if (HL.base[i].compareTimes)
            printf("%6d", HL.base[i].compareTimes);
        else
            printf("%6s", " ");
    }
    printf("\n", i);
    printf("%16s", "该地址是否有数据");
    for (i = 0; i < HL.length; i++)
    {
        if (HL.base[i].flag)
            printf("%6d", HL.base[i].flag);
        else
            printf("%6s", " ");
    }

    printf("\n", i);
}
//查找-在哈希表HL中查找整数a
int IndexHashList(HashList HL, int a)
{
    int di = 1;             //线性探测累加器
    int h = Hash(a);        //计算元素a在哈希表中的地址
    while (HL.base[h].flag) //要查找的地址有数据
    {
        //找到a
        if (HL.base[h].key == a)
        {
            printf("找到元素%d，其下标为%d\n", a, h);
            return h;
        }
        //未找到a
        h = Hash(a + di++);  //计算新地址
        if (di == HL.length) //哈希表被遍历或遍历到空元素
        {
            printf("未找到元素%d！\n", a);
            return -1;
        }
    }
    printf("未找到元素%d！\n", a);
    return -1;
}
//计算平均查找长度
void CalcuASL(HashList H)
{
    int i;
    int sum = 0; //所有元素查找次数的和
    int num = 0; //表中元素个数
    for (i = 0; i < H.length; i++)
    {
        if (H.base[i].flag) //数据存在
        {
            num++;
            sum += H.base[i].compareTimes;
        }
    }
    printf("该哈希表平均查找长度：%f\n", 1.0 * sum / num);
}