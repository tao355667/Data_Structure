/*
数据结构课设02《通讯录的制作》
 题目02：通讯录的制作
[问题描述]
　　设计一个系统，该系统应完成以下几方面的功能：
1)输入信息——enter();
2)显示信息———display( );
3)查找以姓名作为关键字 ———search( );
4)删除信息———delete( );
5)存盘———save ( );。
[基本要求]
（1）每条信息至包含 ：姓名（NAME ）街道（STREET）城市（CITY）邮编（EIP）国家（STATE）几项；
（2）作为一个完整的系统，应具有友好的界面和较强的容错能力；
（3）上机能正常运行，并写出课程设计报告。
输入:
1
3
赵小红
中国
南京
210000
北京东路
王小明
阿根廷
北京
100000
南京西路
Bob
America
Los Angeles
500000
Green Street
2
AA BB
www
eee
rrr
ttt
5

*/
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_DATA_SIZE 30
typedef int Status;
int numOfPerson = 0; //人员总个数
typedef struct
{
    char name[MAX_DATA_SIZE];   //姓名
    char street[MAX_DATA_SIZE]; //街道
    char city[MAX_DATA_SIZE];   //城市
    char eip[MAX_DATA_SIZE];    //邮编
    char state[MAX_DATA_SIZE];  //国家
} ElemType;
//双向链表结构体
typedef struct DuLNode
{
    ElemType data;         //数据域
    DuLNode *prior, *next; //指针域
} DuLNode, *DuLinkList;
//产生空的双向循环链表
void InitList(DuLinkList &L)
{
    //产生空的双向循环链表
    L = (DuLinkList)malloc(sizeof(DuLNode));
    if (L)
        L->next = L->prior = L;
    else
        exit(OVERFLOW);
}
//创建一个结点，并读入相关信息
DuLinkList CreateNode()
{
    fflush(stdin);
    DuLinkList L = (DuLinkList)malloc(sizeof(DuLNode));
    if (!L) //存储分配失败
    {
        printf("新结点创建失败！");
        return NULL;
    }
    char buff[MAX_DATA_SIZE];
    L->prior = NULL; //新结点指针域为空
    L->next = NULL;  //新结点指针域为空
    printf("请输入姓名：");
    gets(L->data.name);
    printf("请输入国家：");
    gets(L->data.state);
    printf("请输入城市：");
    gets(L->data.city);
    printf("请输入邮编：");
    gets(L->data.eip);
    printf("请输入街道：");
    gets(L->data.street);
    return L;
}
//显示序号为i的人员p的信息
void DisplayOnePerson(DuLinkList p, int i)
{
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("%8s %16s %16s %16s %16s %16s\n", "序号", "姓名", "国家", "城市", "邮编", "街道");
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("%8d ", i);
    printf("%16s ", p->data.name);
    printf("%16s ", p->data.state);
    printf("%16s ", p->data.city);
    printf("%16s ", p->data.eip);
    printf("%16s \n", p->data.street);
    printf("---------------------------------------------------------------------------------------------------\n");
}
// 1-建立通讯录
Status CreateList(DuLinkList &L, int num)
{
    int i = 1;       //记录当前插入的是第几个人员
    while (i <= num) //插入num个结点
    {
        printf("请输入第%d位人员的信息：\n", i);
        DuLinkList e = CreateNode(); // e指向新结点
        e->next = L->next;           //新结点的后继为第一个结点
        L->next->prior = e;          //第一个结点的前驱为新结点
        L->next = e;                 //头结点的后继为新结点
        e->prior = L;                //新结点的前驱为头结点
        i++;
        numOfPerson++; //总人数+1
    }
    return OK;
}
// 3-查找人员
Status SearchPerson(DuLinkList L)
{
    int i = 1;                      //查找到的人员序号
    char searchName[MAX_DATA_SIZE]; //要查找的人员的姓名
    printf("请输入要查找人员的姓名:\n");
    gets(searchName);
    DuLinkList p = L->prior; // p指向最后一个结点
    DuLinkList q = p;

    while (p->prior != q) //遍历从最后一个结点到第一个结点
    {
        if (strcmp(p->data.name, searchName) == 0)
        {
            printf("已找到人员 %s ,该成员信息如下:\n", searchName);
            DisplayOnePerson(p, i); //显示找到的人员信息
            return OK;
        }
        i++;
        p = p->prior;
    }
    printf("未找到人员 %s !\n", searchName);
    return ERROR;
}
// 4-删除人员信息(1-根据序号删除,2-根据姓名删除)
Status DeletePerson(DuLinkList &L, int s)
{
    DuLinkList p = L->prior; // p指向最后一个结点
    DuLinkList q = p;
    if (s == 2) // 2-根据姓名删除
    {
        int i = 1;                      //计算要删除的人员的序号
        char searchName[MAX_DATA_SIZE]; //要删除的人员的姓名
        printf("请输入要删除的人员的姓名: ");
        gets(searchName);
        while (p->prior != q) //遍历从最后一个结点到第一个结点
        {
            if (strcmp(p->data.name, searchName) == 0)
            {
                printf("已找到人员 %s ,该成员信息如下:\n", searchName);
                DisplayOnePerson(p, i); //显示找到的人员信息
                p->prior->next = p->next;
                p->next->prior = p->prior;
                free(p);
                printf("已将该人员的信息删除!\n");
                numOfPerson--; //总人数-1
                return OK;
            }
            i++;
            p = p->prior;
        }
        printf("人员 %s 的信息不存在!\n", searchName);
    }
    else if (s == 1) // 1-根据序号删除
    {
        int i = 1; //计算要删除的人员的序号
        int num;   //要删除的人员的序号
        printf("请输入要删除的人员的序号: ");
        scanf("%d", &num);
        getchar(); //消除'\n'
        if (num > numOfPerson || num <= 0)
        {
            printf("该序号不存在!\n");
            return ERROR;
        }
        while (p->prior != q) //遍历从最后一个结点到第一个结点
        {
            if (i == num)
            {
                printf("已找到序号为 %d 的人员,该人员信息如下:\n", num);
                DisplayOnePerson(p, i); //显示找到的人员信息
                p->prior->next = p->next;
                p->next->prior = p->prior;
                free(p);
                numOfPerson--; //总人数-1
                printf("已将该人员的信息删除!\n");
                return OK;
            }
            i++;
            p = p->prior;
        }
    }
    return ERROR;
}
// 5-显示全部人员信息
Status PrintList(DuLinkList L)
{
    if (L->next == L)
    {
        printf("通讯录为空,无法读取!\n");
        return ERROR;
    }

    int i = 1;               //记录当前是第几个人员
    DuLinkList p = L->prior; // p指向最后一个结点
    DuLinkList q = p;
    printf("通讯录所有人员信息如下:\n");
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("%8s %16s %16s %16s %16s %16s\n", "序号", "姓名", "国家", "城市", "邮编", "街道");
    printf("---------------------------------------------------------------------------------------------------\n");
    while (p->prior != q) //遍历从最后一个结点到第一个结点
    {
        printf("%8d ", i++);
        printf("%16s ", p->data.name);
        printf("%16s ", p->data.state);
        printf("%16s ", p->data.city);
        printf("%16s ", p->data.eip);
        printf("%16s \n", p->data.street);
        p = p->prior;
    }
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("总人数: %d\n", numOfPerson);
    return OK;
}
// 6-将通讯录的信息存盘
Status PrintList2File(DuLinkList &L)
{
    FILE *f = NULL;
    //打开文件
    f = fopen("MyAddressBook.txt", "w");
    if (f == NULL)
    {
        printf("文件打开失败！\n");
        return ERROR;
    }
    //打开文件成功，开始处理
    DuLinkList p = L->prior; // p指向最后一个结点
    DuLinkList q = p;
    int i = 1; //人员序号
    // fputs("序号\t\t姓名\t\t国家\t\t城市\t\t邮编\t\t街道\n", f);
    fprintf(f, "%s|%s|%s|%s|%s|%s|\n", "序号", "姓名", "国家", "城市", "邮编", "街道");
    while (p->prior != q) //遍历从最后一个结点到第一个结点
    {
        fprintf(f, "%d|", i++);
        fprintf(f, "%s|", p->data.name);
        fprintf(f, "%s|", p->data.state);
        fprintf(f, "%s|", p->data.city);
        fprintf(f, "%s|", p->data.eip);
        fprintf(f, "%s|", p->data.street);
        if (p->prior != L) // p不是第一个结点（最后一个人员）
            fprintf(f, "\n");
        p = p->prior;
    }
    fclose(f); //关闭文件
    printf("通讯录已存盘为MyAddressBook.txt\n");
    return OK;
}
//将文件指针移动到下一行
Status moveToNextLine(FILE *fp)
{
    int c;
    if (fp == NULL)
        return ERROR; //文件指针非法
    while (1)
    {
        c = fgetc(fp);
        if (c == EOF)
            return EOF; //到文件尾，不存在下一行
        if (c == '\n')
        {
            // printf("//读到需要的换行符。");
            return OK;
        }
    }
}
//从文件中读取一行数据
Status ReadOneDataFromFile(FILE *f, DuLinkList &e)
{
    char buff[MAX_DATA_SIZE];
    char bfc;
    int i;
    for (i = 1; i <= 6; i++) //共接收6次数据
    {
        int j = 0;
        bfc = fgetc(f);
        if (bfc == EOF)
        { //第二行开头为空，说明无人员信息
            return ERROR;
        }

        while (bfc != '|') //读取信息，到|停止
        {

            buff[j] = bfc;
            j++;
            bfc = fgetc(f);
        }
        buff[j] = '\0';
        switch (i)
        {
        case 1:
            break;
        case 2:
            strcpy(e->data.name, buff);
            break;
        case 3:
            strcpy(e->data.state, buff);
            break;
        case 4:
            strcpy(e->data.city, buff);
            break;
        case 5:
            strcpy(e->data.eip, buff);
            break;
        case 6:
            strcpy(e->data.street, buff);
            break;
        }
        memset(buff, 0, MAX_DATA_SIZE); // buff清零
    }
    return OK;
}
// 7-从存盘文件中添加人员信息
Status CreateListFromFile(DuLinkList &L)
{
    int num = 0; //记录添加了几个人员的信息
    FILE *f = NULL;
    f = fopen("MyAddressBook.txt", "r");
    if (f == NULL)
    {
        printf("文件打开失败！\n");
        return ERROR;
    }
    char buff[MAX_DATA_SIZE];       //读入数据缓存
    while (moveToNextLine(f) == OK) //将文件指针移动到下一行
    {
        //建立一个新结点
        DuLinkList e = (DuLinkList)malloc(sizeof(DuLNode));
        if (!e) //存储分配失败
        {
            printf("新结点创建失败！");
            return ERROR;
        }
        e->prior = NULL;                //新结点指针域为空
        e->next = NULL;                 //新结点指针域为空
        char n[MAX_DATA_SIZE];          //接收读入的序号，但不使用
        if (!ReadOneDataFromFile(f, e)) //第一行存在且此行为空说明文件第一行之后为空
        {
            free(e); //将没用到的结点空间释放
            break;   //此行为空，说明文件中无人员信息
        }

        //将新结点插入链表
        e->next = L->next;  //新结点的后继为第一个结点
        L->next->prior = e; //第一个结点的前驱为新结点
        L->next = e;        //头结点的后继为新结点
        e->prior = L;       //新结点的前驱为头结点
        numOfPerson++;      //总人数+1
        num++;
    }
    fclose(f);
    if (num)
        printf("从存盘文件添加了 %d 个人员信息！\n", num);
    else
        printf("添加人员信息失败！\n");
    return OK;
}
//主菜单
void showStart()
{
    printf("\n******************^-^欢迎使用通讯录系统****************\n");
    printf("*               1 建立通讯录(添加多个人员信息)        *\n");
    printf("*               2 添加单个人员信息                    *\n");
    printf("*               3 查找人员信息                        *\n");
    printf("*               4 删除人员信息                        *\n");
    printf("*               5 显示所有人员信息                    *\n");
    printf("*               6 将通讯录信息存盘                    *\n");
    printf("*               7 从存盘文件添加人员信息              *\n");
    printf("*               0 退出通讯录系统                      *\n");
    printf("******************^-^欢迎使用通讯录系统****************\n");
}
//提示用户输入信息
void InputMessage()
{
    printf("请输入0-7(输入99查看命令): ");
}
//读取指令，此函数只接收一个整数
int MyScanf(int mode = 0)
{
    int a;
    while (1)
    {
        if (scanf("%d", &a)) //正确匹配
        {
            fflush(stdin); //清空标准输入缓存区
            return a;      //返回接收到的整数（指令）
        }
        else
        {
            fflush(stdin); //清除标准输入缓存区
            switch (mode)
            {
            case 0:
                InputMessage(); //提示用户输入信息
                break;
            case 1:
                printf("请选择删除模式(1-根据序号删除 2-根据姓名删除 0-回到主菜单): ");
                break;
            }
        }
    }
}
int main()
{
    system("color 1f"); //设置界面颜色
    DuLinkList L;       //带头结点的双向链表
    InitList(L);
    showStart();    //显示主界面
    InputMessage(); //提示用户输入信息
    int menu;       //菜单
    menu = MyScanf();
    while (menu) // menu为0退出通讯录程序
    {
        switch (menu)
        {
        case 1:
            int num;
            printf("请输入要添加的人员个数：");
            scanf("%d", &num);
            CreateList(L, num);
            printf("您向通讯录中添加了%d位人员!\n", num);
            break;
        case 2:
            printf("向通讯录中添加一位人员：");
            CreateList(L, 1);
            printf("您向通讯录中添加了1位人员!\n");
            break;
        case 3:
            SearchPerson(L); //根据姓名查找人员
            break;
        case 4:
            int deleteNum;
            printf("请选择删除模式(1-根据序号删除 2-根据姓名删除 0-回到主菜单): ");
            deleteNum = MyScanf(1);
            switch (deleteNum)
            {
            case 0: //什么也不做，回到主菜单
                break;
            case 1:
            case 2:
                DeletePerson(L, deleteNum); //删除人员
                break;
            default:
                fflush(stdin);                 //清除标准输入缓冲区
                printf("请输入正确的指令!\n"); //提示用户输入信息
                break;
            }
            break;
        case 5:
            PrintList(L); //以表格形式显示通讯录信息
            break;
        case 6:
            PrintList2File(L); //以表格形式将通讯录存盘
            break;
        case 7:
            CreateListFromFile(L); //从文件添加通讯录成员
            break;
        case 99:
            showStart();
            break;
        default:
            printf("指令 %d 不存在！\n", menu);
        }
        InputMessage();   //提示用户输入信息
        fflush(stdin);    //清空标准输入缓存区
        menu = MyScanf(); //接收新指令
    }

    return 0;
}